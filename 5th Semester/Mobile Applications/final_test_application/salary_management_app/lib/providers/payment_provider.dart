import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:connectivity_plus/connectivity_plus.dart';
import 'package:web_socket_channel/web_socket_channel.dart';
import '../models/payment.dart';
import '../services/api_service.dart';
import '../services/database_helper.dart';

class PaymentProvider with ChangeNotifier {
  final ApiService _apiService = ApiService();
  final DatabaseHelper _dbHelper = DatabaseHelper();
  
  List<Payment> _payments = []; // For Main Section
  List<Payment> _allPayments = []; // For Reports/Insights
  
  bool _isLoading = false;
  String? _errorMessage;
  String? _notification;
  String? _successMessage;
  bool _isOffline = false;
  int? _lastAddedPaymentId; // Track last payment added by this client

  List<Payment> get payments => _payments;
  List<Payment> get allPayments => _allPayments;
  
  bool get isLoading => _isLoading;
  String? get errorMessage => _errorMessage;
  String? get notification => _notification;
  String? get successMessage => _successMessage;
  bool get isOffline => _isOffline;

  WebSocketChannel? _channel;

  PaymentProvider() {
    _checkConnectivity();
    _initWebSocket();
  }
  
  void _checkConnectivity() async {
     // Initial check
     var result = await (Connectivity().checkConnectivity());
     _updateConnectionStatus(result);
     
     // Listen to changes
     Connectivity().onConnectivityChanged.listen((ConnectivityResult result) {
       _updateConnectionStatus(result);
     });
  }

  void _updateConnectionStatus(ConnectivityResult result) {
    if (result == ConnectivityResult.none) {
      _isOffline = true;
    } else {
      _isOffline = false;
      // Re-connect WS if needed or sync?
    }
    notifyListeners();
  }

  void _initWebSocket() {
    try {
      _channel = _apiService.connectWebSocket();
      _channel!.stream.listen((message) {
        try {
          final data = json.decode(message);
          final payment = Payment.fromJson(data);
          
          // Don't show notification if this is the payment we just added
          if (_lastAddedPaymentId != null && payment.id == _lastAddedPaymentId) {
            _lastAddedPaymentId = null; // Reset
            return;
          }
          
          _notification = "New Payment: ${payment.amount} ${payment.type}";
          // Don't add to lists here - it will be added by the API response
          // This prevents duplicates when the current client adds a payment
          notifyListeners();
        } catch (e) {
          print("WS Parse Error: $e");
        }
      }, onError: (e) {
         print("WS Error: $e");
      });
    } catch (e) {
      print("WS Connect Error: $e");
    }
  }
  
  Future<void> fetchPayments() async {
    _setLoading(true);
    clearError();
    
    // Check connectivity again just in case
    var result = await (Connectivity().checkConnectivity());
    if (result == ConnectivityResult.none) {
        _isOffline = true;
        try {
          _payments = await _dbHelper.getPayments();
        } catch (e) {
          _setError("Offline: Failed to load local data");
        }
    } else {
        _isOffline = false;
        try {
          final data = await _apiService.getPayments();
          _payments = data;
          await _dbHelper.deleteAllPayments();
          await _dbHelper.insertPayments(data);
          _setSuccessMessage("Fetched ${data.length} payments from server");
        } catch (e) {
           _setError("Failed to fetch data: $e");
           // Fallback
           _payments = await _dbHelper.getPayments();
        }
    }
    _setLoading(false);
  }

  Future<void> fetchAllPayments() async {
    // For Reports and Insights
    _setLoading(true);
    if (_isOffline) {
       // Just use local payments as proxy for 'all' if we can't reach server
       // Or show error that reports need online?
       // Prompt says: "Using the GET /allPayments call..."
       // If offline, maybe we can't get fresh reports. 
       // But let's assume we try to use cached list of payments as "All"
       try {
         _allPayments = await _dbHelper.getPayments();
       } catch (e) {
         _setError("Offline and no data");
       }
    } else {
      try {
        final data = await _apiService.getAllPayments();
        _allPayments = data;
        // Maybe dont sync 'allPayments' to same table to avoid dupes or confusion?
        // But since the API returns same structure, we can just use same table.
      } catch (e) {
        _setError("Failed to fetch all payments: $e");
      }
    }
    _setLoading(false);
  }
  
  Future<void> addPayment(Payment payment) async {
    if (_isOffline) {
      _setError("Cannot add payment while offline");
      return;
    }
    _setLoading(true);
    try {
      final newPayment = await _apiService.addPayment(payment);
      _lastAddedPaymentId = newPayment.id; // Track this payment to ignore WS notification
      _payments.add(newPayment);
      _allPayments.add(newPayment);
      await _dbHelper.insertPayment(newPayment);
      _setSuccessMessage("Payment added successfully");
      notifyListeners();
    } catch (e) {
      _setError("Failed to add payment: $e");
      rethrow; // Rethrow so the caller knows it failed
    } finally {
      _setLoading(false);
    }
  }

  Future<void> deletePayment(int id) async {
     if (_isOffline) {
      _setError("Cannot delete payment while offline");
      return;
    }
    _setLoading(true);
    try {
      await _apiService.deletePayment(id);
      _payments.removeWhere((p) => p.id == id);
      _allPayments.removeWhere((p) => p.id == id);
      await _dbHelper.deletePayment(id);
      _setSuccessMessage("Payment deleted successfully");
      notifyListeners();
    } catch (e) {
      _setError("Failed to delete: $e");
    }
    _setLoading(false);
  }

  Future<Payment?> getPaymentDetail(int id) async {
    if (_isOffline) {
      return _dbHelper.getPayment(id);
    } else {
      try {
        final p = await _apiService.getPayment(id);
        await _dbHelper.insertPayment(p);
        return p;
      } catch (e) {
        return _dbHelper.getPayment(id);
      }
    }
  }

  Map<String, double> get monthlyAnalysis {
    Map<String, double> totals = {};
    for (var p in _allPayments) {
      if (p.date.length >= 7) {
        String month = p.date.substring(0, 7);
        totals[month] = (totals[month] ?? 0) + p.amount;
      }
    }
    var sortedKeys = totals.keys.toList()..sort((a, b) => b.compareTo(a));
    Map<String, double> sortedMap = { for (var k in sortedKeys) k: totals[k]! };
    return sortedMap;
  }

  List<MapEntry<String, double>> get topDepartments {
    Map<String, double> totals = {};
    for (var p in _allPayments) {
       totals[p.category] = (totals[p.category] ?? 0) + p.amount;
    }
    var sortedEntries = totals.entries.toList()
      ..sort((a, b) => b.value.compareTo(a.value));
    return sortedEntries.take(3).toList();
  }

  void _setLoading(bool value) {
    _isLoading = value;
    notifyListeners();
  }

  void _setError(String msg) {
    _errorMessage = msg;
    notifyListeners();
  }
  
  void clearError() {
    _errorMessage = null;
    notifyListeners();
  }
  
  void clearNotification() {
    _notification = null;
    notifyListeners();
  }
  
  void clearSuccessMessage() {
    _successMessage = null;
    notifyListeners();
  }
  
  void _setSuccessMessage(String msg) {
    _successMessage = msg;
    notifyListeners();
  }
  
  @override
  void dispose() {
    if (_channel != null) {
      _channel!.sink.close();
    }
    super.dispose();
  }
}
