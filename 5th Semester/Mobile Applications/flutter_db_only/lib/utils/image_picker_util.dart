import 'dart:io';
import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';
import 'package:logger/logger.dart';
import 'package:path/path.dart' as path;
import 'package:path_provider/path_provider.dart';
import 'package:uuid/uuid.dart';

enum ImageSourceType { camera, gallery }

class ImagePickerUtil {
  static final ImagePickerUtil _instance = ImagePickerUtil._internal();
  final Logger _logger = Logger();
  final ImagePicker _picker = ImagePicker();
  final Uuid _uuid = const Uuid();

  factory ImagePickerUtil() {
    return _instance;
  }

  ImagePickerUtil._internal();

  Future<String?> pickImage(BuildContext context, ImageSourceType sourceType) async {
    try {
      final XFile? image = await _picker.pickImage(
        source: sourceType == ImageSourceType.camera 
            ? ImageSource.camera 
            : ImageSource.gallery,
        imageQuality: 85,
        maxWidth: 1024,
        maxHeight: 1024,
      );

      if (image != null) {
        _logger.i('Image selected from ${sourceType == ImageSourceType.camera ? "camera" : "gallery"}');
        return await _saveImageLocally(image);
      }

      _logger.w('No image selected');
      return null;
    } catch (e) {
      _logger.e('Error picking image from ${sourceType == ImageSourceType.camera ? "camera" : "gallery"}: $e');
      
      if (context.mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(
            content: Text('Error selecting image: $e'),
            backgroundColor: Colors.red,
          ),
        );
      }
      return null;
    }
  }

  Future<String> _saveImageLocally(XFile image) async {
    try {
      final directory = await getApplicationDocumentsDirectory();
      final imagesDirectory = Directory('${directory.path}/images');

      if (!await imagesDirectory.exists()) {
        await imagesDirectory.create(recursive: true);
      }

      final extension = path.extension(image.name);
      final filename = '${_uuid.v4()}$extension';
      final filePath = '${imagesDirectory.path}/$filename';

      final File localImage = File(filePath);
      await localImage.writeAsBytes(await image.readAsBytes());

      _logger.i('Image saved locally at: $filePath');
      return filePath;
    } catch (e) {
      _logger.e('Error saving image locally: $e');
      rethrow;
    }
  }

  Future<void> deleteImage(String imagePath) async {
    try {
      final file = File(imagePath);
      if (await file.exists()) {
        await file.delete();
        _logger.i('Image deleted from: $imagePath');
      } else {
        _logger.w('Image not found at: $imagePath');
      }
    } catch (e) {
      _logger.e('Error deleting image from $imagePath: $e');
    }
  }

  Future<void> showImageSourceDialog(BuildContext context, Function(String) onImageSelected) async {
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          title: const Text('Select Image Source'),
          content: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              
              ListTile(
                leading: const Icon(Icons.camera_alt),
                title: const Text('Camera'),
                onTap: () async {
                  Navigator.of(context).pop();
                  final imagePath = await pickImage(context, ImageSourceType.camera);
                  if (imagePath != null) {
                    onImageSelected(imagePath);
                  }
                },
              ),
              ListTile(
                leading: const Icon(Icons.photo_library),
                title: const Text('Gallery'),
                onTap: () async {
                  Navigator.of(context).pop();
                  final imagePath = await pickImage(context, ImageSourceType.gallery);
                  if (imagePath != null) {
                    onImageSelected(imagePath);
                  }
                },
              ),
            ],
          ),
        );
      },
    );
  }
}