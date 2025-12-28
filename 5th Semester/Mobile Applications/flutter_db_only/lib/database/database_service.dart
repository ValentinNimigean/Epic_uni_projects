import 'dart:async';
import 'package:logger/logger.dart';
import 'package:path/path.dart';
import 'package:path_provider/path_provider.dart';
import 'package:sqflite/sqflite.dart';

class DatabaseService {
  static final DatabaseService _instance = DatabaseService._internal();
  static Database? _database;
  final Logger _logger = Logger();

  factory DatabaseService() {
    return _instance;
  }

  DatabaseService._internal();

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDatabase();
    return _database!;
  }

  Future<Database> _initDatabase() async {
    try {
      final documentsDirectory = await getApplicationDocumentsDirectory();
      final path = join(documentsDirectory.path, 'clothing_archive.db');
      
      _logger.i('Initializing database at: $path');
      
      return await openDatabase(
        path,
        version: 1,
        onCreate: _onCreate,
        onUpgrade: _onUpgrade,
      );
    } catch (e) {
      _logger.e('Error initializing database: $e');
      rethrow;
    }
  }

  Future<void> _onCreate(Database db, int version) async {
    try {
      _logger.i('Creating database tables');
      
      await db.execute('''
        CREATE TABLE clothing_items (
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          name TEXT NOT NULL,
          brand TEXT NOT NULL,
          season TEXT NOT NULL,
          year INTEGER NOT NULL,
          category TEXT NOT NULL,
          material TEXT NOT NULL,
          image_url TEXT,
          notes TEXT,
          created_at TEXT DEFAULT CURRENT_TIMESTAMP,
          updated_at TEXT DEFAULT CURRENT_TIMESTAMP
        )
      ''');

      await db.execute('''
        CREATE INDEX idx_clothing_items_name ON clothing_items(name)
      ''');

      await db.execute('''
        CREATE INDEX idx_clothing_items_brand ON clothing_items(brand)
      ''');

      await db.execute('''
        CREATE INDEX idx_clothing_items_category ON clothing_items(category)
      ''');

      _logger.i('Database tables created successfully');
    } catch (e) {
      _logger.e('Error creating database tables: $e');
      rethrow;
    }
  }

  Future<void> _onUpgrade(Database db, int oldVersion, int newVersion) async {
    _logger.i('Upgrading database from version $oldVersion to $newVersion');
  }

  Future<void> close() async {
    final db = await database;
    await db.close();
    _database = null;
    _logger.i('Database closed');
  }

  Future<void> clearDatabase() async {
    try {
      final db = await database;
      await db.delete('clothing_items');
      _logger.i('Database cleared');
    } catch (e) {
      _logger.e('Error clearing database: $e');
      rethrow;
    }
  }
}