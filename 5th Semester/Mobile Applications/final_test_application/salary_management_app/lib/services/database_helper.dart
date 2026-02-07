import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';
import '../models/payment.dart';
import 'logger_service.dart';

class DatabaseHelper {
  static final DatabaseHelper _instance = DatabaseHelper._internal();
  factory DatabaseHelper() => _instance;
  DatabaseHelper._internal();

  static Database? _database;

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDatabase();
    return _database!;
  }

  Future<Database> _initDatabase() async {
    await LoggerService().log("[DB] Initializing Database");
    String path = join(await getDatabasesPath(), 'salary_manager.db');
    return await openDatabase(
      path,
      version: 1,
      onCreate: _onCreate,
    );
  }

  Future<void> _onCreate(Database db, int version) async {
    await LoggerService().log("[DB] Creating tables");
    await db.execute('''
      CREATE TABLE payments(
        id INTEGER PRIMARY KEY,
        date TEXT,
        amount REAL,
        type TEXT,
        category TEXT,
        description TEXT
      )
    ''');
  }

  Future<void> insertPayment(Payment payment) async {
    await LoggerService().log("[DB] Inserting payment: ${payment.id}");
    final db = await database;
    await db.insert(
      'payments',
      payment.toJson(),
      conflictAlgorithm: ConflictAlgorithm.replace,
    );
  }

  Future<void> insertPayments(List<Payment> payments) async {
    await LoggerService().log("[DB] Inserting ${payments.length} payments");
    final db = await database;
    Batch batch = db.batch();
    for (var payment in payments) {
      batch.insert(
        'payments',
        payment.toJson(),
        conflictAlgorithm: ConflictAlgorithm.replace,
      );
    }
    await batch.commit(noResult: true);
  }

  Future<List<Payment>> getPayments() async {
    await LoggerService().log("[DB] Querying all payments");
    final db = await database;
    final List<Map<String, dynamic>> maps = await db.query('payments');
    await LoggerService().log("[DB] Found ${maps.length} payments");
    return List.generate(maps.length, (i) {
      return Payment.fromJson(maps[i]);
    });
  }

  Future<Payment?> getPayment(int id) async {
    await LoggerService().log("[DB] Querying payment: $id");
    final db = await database;
    List<Map<String, dynamic>> maps = await db.query(
      'payments',
      where: 'id = ?',
      whereArgs: [id],
    );
    if (maps.isNotEmpty) {
      await LoggerService().log("[DB] Found payment: $id");
      return Payment.fromJson(maps.first);
    }
    await LoggerService().log("[DB] Payment not found: $id");
    return null;
  }
  
  Future<void> deletePayment(int id) async {
    await LoggerService().log("[DB] Deleting payment: $id");
    final db = await database;
    await db.delete('payments', where: 'id = ?', whereArgs: [id]);
  }

  Future<void> deleteAllPayments() async {
    await LoggerService().log("[DB] Deleting ALL payments");
    final db = await database;
    await db.delete('payments');
  }
}
