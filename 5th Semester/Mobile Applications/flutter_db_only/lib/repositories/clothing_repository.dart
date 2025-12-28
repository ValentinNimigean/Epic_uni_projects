import 'dart:async';
import 'package:flutter/foundation.dart';
import 'package:logger/logger.dart';
import '../models/clothing_item.dart';
import '../database/clothing_item_dao.dart';

class ClothingRepository extends ChangeNotifier {
  static final ClothingRepository _instance = ClothingRepository._internal();
  final Logger _logger = Logger();
  final ClothingItemDao _dao = ClothingItemDao();

  List<ClothingItem> _items = [];
  bool _isLoading = false;
  String? _error;

  factory ClothingRepository() {
    return _instance;
  }

  ClothingRepository._internal();

  List<ClothingItem> get items => List.unmodifiable(_items);
  bool get isLoading => _isLoading;
  String? get error => _error;

  Future<void> initialize() async {
    try {
      _setLoading(true);
      _setError(null);

      _logger.i('Initializing clothing repository');
      
      final items = await _loadItemsFromDatabase();
      
      _items = items;
      _logger.i('Repository initialized with ${_items.length} items');
      
      notifyListeners();
    } catch (e) {
      _logger.e('Error initializing repository: $e');
      _setError('Failed to load data: $e');
      notifyListeners();
    } finally {
      _setLoading(false);
    }
  }

  Future<List<ClothingItem>> _loadItemsFromDatabase() async {
    try {
      return await _dao.getAllItems();
    } catch (e) {
      _logger.e('Database error while loading items: $e');
      rethrow;
    }
  }

  Future<ClothingItem> add(ClothingItem item) async {
    try {
      _setError(null);
      _logger.i('Adding new clothing item: ${item.name}');

      final savedItem = await _dao.insertItem(item);

      _items = List.from(_items)..add(savedItem);
      
      _logger.i('Clothing item added successfully with ID: ${savedItem.id}');
      notifyListeners();
      
      return savedItem;
    } catch (e) {
      _logger.e('Error adding clothing item: $e');
      _setError('Failed to save item: $e');
      notifyListeners();
      rethrow;
    }
  }

  Future<ClothingItem> update(ClothingItem item) async {
    try {
      _setError(null);
      _logger.i('Updating clothing item with ID: ${item.id}');

      final updatedItem = await _dao.updateItem(item);
      
      final index = _items.indexWhere((i) => i.id == item.id);
      if (index != -1) {
        _items = List.from(_items)..[index] = updatedItem;
      }
      
      _logger.i('Clothing item updated successfully');
      notifyListeners();
      
      return updatedItem;
    } catch (e) {
      _logger.e('Error updating clothing item with ID ${item.id}: $e');
      _setError('Failed to update item: $e');
      notifyListeners();
      rethrow;
    }
  }

  Future<void> delete(String id) async {
    try {
      _setError(null);
      _logger.i('Deleting clothing item with ID: $id');

      await _dao.deleteItem(int.parse(id));

      _items = _items.where((item) => item.id != id).toList();
      
      _logger.i('Clothing item deleted successfully');
      notifyListeners();
    } catch (e) {
      _logger.e('Error deleting clothing item with ID $id: $e');
      _setError('Failed to delete item: $e');
      notifyListeners();
      rethrow;
    }
  }

  ClothingItem? getItemById(String id) {
    try {
      return _items.firstWhere((item) => item.id == id);
    } catch (e) {
      _logger.w('Item with ID $id not found');
      return null;
    }
  }

  Future<List<ClothingItem>> searchItems(String query) async {
    try {
      _setError(null);
      _logger.i('Searching items with query: $query');
      
      return await _dao.searchItems(query);
    } catch (e) {
      _logger.e('Error searching items: $e');
      _setError('Search failed: $e');
      notifyListeners();
      rethrow;
    }
  }

  void clearError() {
    _setError(null);
  }

  void _setLoading(bool loading) {
    _isLoading = loading;
  }

  void _setError(String? error) {
    _error = error;
  }

  @override
  void dispose() {
    _logger.i('Disposing clothing repository');
    super.dispose();
  }
}
