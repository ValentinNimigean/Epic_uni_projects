import 'dart:io';
import 'package:path_provider/path_provider.dart';

class LoggerService {
  static final LoggerService _instance = LoggerService._internal();
  factory LoggerService() => _instance;
  LoggerService._internal();

  File? _logFile;

  Future<File> get _file async {
    if (_logFile != null) return _logFile!;
    final directory = await getApplicationDocumentsDirectory();
    _logFile = File('${directory.path}/app_logs.txt');
    return _logFile!;
  }

  Future<void> log(String message) async {
    try {
      final file = await _file;
      final timestamp = DateTime.now().toIso8601String();
      final logMessage = '$timestamp: $message\n';
      
      // Print to console as well
      print(message);
      
      await file.writeAsString(logMessage, mode: FileMode.append);
    } catch (e) {
      print("Failed to write log: $e");
    }
  }
}
