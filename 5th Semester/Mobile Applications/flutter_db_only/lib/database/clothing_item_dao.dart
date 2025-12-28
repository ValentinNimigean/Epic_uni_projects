import 'dart:async';
import 'package:logger/logger.dart';
import '../models/clothing_item.dart';
import 'database_service.dart';

class ClothingItemDao {
  static final ClothingItemDao _instance = ClothingItemDao._internal();
  final Logger _logger = Logger();

  factory ClothingItemDao() {
    return _instance;
  }

  ClothingItemDao._internal();

  Future<List<ClothingItem>> getAllItems() async {
    try {
      final db = await DatabaseService().database;
      final maps = await db.query('clothing_items', orderBy: 'name');
      
      _logger.i('Retrieved ${maps.length} clothing items from database');
      
      return maps.map((map) => ClothingItem.fromJson(map)).toList();
    } catch (e) {
      _logger.e('Error retrieving clothing items: $e');
      rethrow;
    }
  }

  Future<ClothingItem?> getItemById(int id) async {
    try {
      final db = await DatabaseService().database;
      final maps = await db.query(
        'clothing_items',
        where: 'id = ?',
        whereArgs: [id],
      );
      
      if (maps.isNotEmpty) {
        _logger.i('Retrieved clothing item with id: $id');
        return ClothingItem.fromJson(maps.first);
      }
      
      _logger.w('Clothing item with id: $id not found');
      return null;
    } catch (e) {
      _logger.e('Error retrieving clothing item with id $id: $e');
      rethrow;
    }
  }

  Future<ClothingItem> insertItem(ClothingItem item) async {
    try {
      final db = await DatabaseService().database;
      final data = Map<String, dynamic>.from(item.toJson());
      data.remove('id');
      
      final id = await db.insert('clothing_items', data);
      
      _logger.i('Inserted clothing item with id: $id');
      
      return item.copyWith(id: id.toString());
    } catch (e) {
      _logger.e('Error inserting clothing item: $e');
      rethrow;
    }
  }

  Future<ClothingItem> updateItem(ClothingItem item) async {
    try {
      final db = await DatabaseService().database;
      final count = await db.update(
        'clothing_items',
        item.toJson(),
        where: 'id = ?',
        whereArgs: [int.parse(item.id)],
      );
      
      if (count > 0) {
        _logger.i('Updated clothing item with id: ${item.id}');
        return item;
      }
      
      throw Exception('Item not found for update');
    } catch (e) {
      _logger.e('Error updating clothing item with id ${item.id}: $e');
      rethrow;
    }
  }

  Future<void> deleteItem(int id) async {
    try {
      final db = await DatabaseService().database;
      final count = await db.delete(
        'clothing_items',
        where: 'id = ?',
        whereArgs: [id],
      );
      
      if (count > 0) {
        _logger.i('Deleted clothing item with id: $id');
      } else {
        _logger.w('No clothing item found to delete with id: $id');
      }
    } catch (e) {
      _logger.e('Error deleting clothing item with id $id: $e');
      rethrow;
    }
  }

  Future<List<ClothingItem>> searchItems(String query) async {
    try {
      final db = await DatabaseService().database;
      final maps = await db.query(
        'clothing_items',
        where: 'name LIKE ? OR brand LIKE ? OR category LIKE ?',
        whereArgs: ['%$query%', '%$query%', '%$query%'],
        orderBy: 'name',
      );
      
      _logger.i('Found ${maps.length} clothing items matching query: $query');
      
      return maps.map((map) => ClothingItem.fromJson(map)).toList();
    } catch (e) {
      _logger.e('Error searching clothing items with query $query: $e');
      rethrow;
    }
  }
}