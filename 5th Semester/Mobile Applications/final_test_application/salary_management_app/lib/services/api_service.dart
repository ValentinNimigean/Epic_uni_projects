import 'dart:io';
import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:web_socket_channel/web_socket_channel.dart';
import '../models/payment.dart';
import 'logger_service.dart';

class ApiService {
  static String get baseUrl {
    if (Platform.isAndroid) {
      return 'http://10.0.2.2:2627';
    }
    return 'http://localhost:2627';
  }

  static String get wsUrl {
    if (Platform.isAndroid) {
      return 'ws://10.0.2.2:2627';
    }
    return 'ws://localhost:2627';
  }

  Future<List<Payment>> getPayments() async {
    await LoggerService().log("[API] Requesting GET /payments");
    try {
      final response = await http.get(Uri.parse('$baseUrl/payments'));
      if (response.statusCode == 200) {
        await LoggerService().log("[API] Success GET /payments");
        Iterable l = json.decode(response.body);
        return l.map((model) => Payment.fromJson(model)).toList();
      } else {
        await LoggerService().log("[API] Error GET /payments: ${response.statusCode}");
        throw Exception('Failed to load payments');
      }
    } catch (e) {
      await LoggerService().log("[API] Exception GET /payments: $e");
      rethrow;
    }
  }
  
  Future<List<Payment>> getAllPayments() async {
    await LoggerService().log("[API] Requesting GET /allPayments");
    try {
      final response = await http.get(Uri.parse('$baseUrl/allPayments'));
      if (response.statusCode == 200) {
        await LoggerService().log("[API] Success GET /allPayments");
        Iterable l = json.decode(response.body);
        return l.map((model) => Payment.fromJson(model)).toList();
      } else {
         await LoggerService().log("[API] Error GET /allPayments: ${response.statusCode}");
        throw Exception('Failed to load all payments');
      }
     } catch (e) {
      await LoggerService().log("[API] Exception GET /allPayments: $e");
      rethrow;
    }
  }

  Future<Payment> getPayment(int id) async {
     await LoggerService().log("[API] Requesting GET /payment/$id");
     try {
       final response = await http.get(Uri.parse('$baseUrl/payment/$id'));
       if (response.statusCode == 200) {
         await LoggerService().log("[API] Success GET /payment/$id");
         return Payment.fromJson(json.decode(response.body));
       } else {
         await LoggerService().log("[API] Error GET /payment/$id: ${response.statusCode}");
         throw Exception('Failed to load payment details');
       }
     } catch (e) {
       await LoggerService().log("[API] Exception GET /payment/$id: $e");
       rethrow;
     }
  }

  Future<Payment> addPayment(Payment payment) async {
    await LoggerService().log("[API] Requesting POST /payment");
    try {
      final response = await http.post(
        Uri.parse('$baseUrl/payment'),
        headers: {'Content-Type': 'application/json'},
        body: json.encode({
          'date': payment.date,
          'amount': payment.amount,
          'type': payment.type,
          'category': payment.category,
          'description': payment.description,
        }),
      );
      if (response.statusCode == 201) {
        await LoggerService().log("[API] Success POST /payment");
        return Payment.fromJson(json.decode(response.body));
      } else {
        await LoggerService().log("[API] Error POST /payment: ${response.statusCode}");
        throw Exception('Failed to add payment');
      }
    } catch (e) {
      await LoggerService().log("[API] Exception POST /payment: $e");
      rethrow;
    }
  }
  
  Future<void> deletePayment(int id) async {
    await LoggerService().log("[API] Requesting DELETE /payment/$id");
    try {
      final response = await http.delete(Uri.parse('$baseUrl/payment/$id'));
      if (response.statusCode != 200) {
        await LoggerService().log("[API] Error DELETE /payment/$id: ${response.statusCode}");
        throw Exception('Failed to delete payment');
      }
      await LoggerService().log("[API] Success DELETE /payment/$id");
    } catch (e) {
      await LoggerService().log("[API] Exception DELETE /payment/$id: $e");
      rethrow;
    }
  }

  WebSocketChannel connectWebSocket() {
    LoggerService().log("[API] Connecting WebSocket to $wsUrl");
    return WebSocketChannel.connect(Uri.parse(wsUrl));
  }
}
