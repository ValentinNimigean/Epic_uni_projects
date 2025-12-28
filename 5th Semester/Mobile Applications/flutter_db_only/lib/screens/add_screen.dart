import 'dart:io';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/clothing_item.dart';
import '../repositories/clothing_repository.dart';
import '../utils/image_picker_util.dart';

class AddScreen extends StatefulWidget {
  @override
  _AddScreenState createState() => _AddScreenState();
}

class _AddScreenState extends State<AddScreen> {
  final _formKey = GlobalKey<FormState>();
  final _nameController = TextEditingController();
  final _brandController = TextEditingController();
  String? _selectedSeason;
  int? _selectedYear;
  String? _selectedCategory;
  String? _selectedMaterial;
  String? _imagePath;
  final _notesController = TextEditingController();

  static const List<String> _seasons = ['AW', 'SS'];
  static const List<int> _years = [2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025];
  static const List<String> _categories = ['Tops', 'Bottoms', 'Shoes', 'Accessories', 'Dresses', 'Outerwear', 'Jacket', 'Pants', 'T-shirt'];
  static const List<String> _materials = ['Cotton', 'Wool', 'Leather', 'Synthetic', 'Silk', 'Denim', 'Polyester', 'Schoeller Dryskin'];

  @override
  void dispose() {
    _nameController.dispose();
    _brandController.dispose();
    _notesController.dispose();
    super.dispose();
  }

  Future<void> _pickImage() async {
    await ImagePickerUtil().showImageSourceDialog(
      context,
      (imagePath) {
        setState(() {
          _imagePath = imagePath;
        });
      },
    );
  }

  void _clearImage() {
    setState(() {
      _imagePath = null;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Add Clothing Item'),
      ),
      body: Consumer<ClothingRepository>(
        builder: (context, repository, child) {
          return Padding(
            padding: EdgeInsets.all(16.0),
            child: Form(
              key: _formKey,
              child: ListView(
                children: [
                  // Image picker section
                  _buildImagePickerSection(),
                  
                  SizedBox(height: 16),
                  
                  TextFormField(
                    controller: _nameController,
                    decoration: InputDecoration(labelText: 'Name'),
                    validator: (value) => value!.isEmpty ? 'Required' : null,
                  ),
                  TextFormField(
                    controller: _brandController,
                    decoration: InputDecoration(labelText: 'Brand'),
                    validator: (value) => value!.isEmpty ? 'Required' : null,
                  ),
                  Row(
                    children: [
                      Expanded(
                        child: DropdownButtonFormField<String>(
                          value: _selectedSeason,
                          decoration: InputDecoration(labelText: 'Season'),
                          items: _seasons.map((String value) {
                            return DropdownMenuItem<String>(
                              value: value,
                              child: Text(value),
                            );
                          }).toList(),
                          onChanged: (newValue) {
                            setState(() {
                              _selectedSeason = newValue;
                            });
                          },
                          validator: (value) => value == null ? 'Required' : null,
                        ),
                      ),
                      SizedBox(width: 16),
                      Expanded(
                        child: DropdownButtonFormField<int>(
                          value: _selectedYear,
                          decoration: InputDecoration(labelText: 'Year'),
                          items: _years.map((int value) {
                            return DropdownMenuItem<int>(
                              value: value,
                              child: Text(value.toString()),
                            );
                          }).toList(),
                          onChanged: (newValue) {
                            setState(() {
                              _selectedYear = newValue;
                            });
                          },
                          validator: (value) => value == null ? 'Required' : null,
                        ),
                      ),
                    ],
                  ),
                  DropdownButtonFormField<String>(
                    value: _selectedCategory,
                    decoration: InputDecoration(labelText: 'Category'),
                    items: _categories.map((String value) {
                      return DropdownMenuItem<String>(
                        value: value,
                        child: Text(value),
                      );
                    }).toList(),
                    onChanged: (newValue) {
                      setState(() {
                        _selectedCategory = newValue;
                      });
                    },
                    validator: (value) => value == null ? 'Required' : null,
                  ),
                  DropdownButtonFormField<String>(
                    value: _selectedMaterial,
                    decoration: InputDecoration(labelText: 'Material'),
                    items: _materials.map((String value) {
                      return DropdownMenuItem<String>(
                        value: value,
                        child: Text(value),
                      );
                    }).toList(),
                    onChanged: (newValue) {
                      setState(() {
                        _selectedMaterial = newValue;
                      });
                    },
                    validator: (value) => value == null ? 'Required' : null,
                  ),
                  TextFormField(
                    controller: _notesController,
                    decoration: InputDecoration(labelText: 'Notes'),
                    maxLines: 3,
                  ),
                  SizedBox(height: 20),
                  
                  // Show error if any
                  if (repository.error != null)
                    Container(
                      padding: EdgeInsets.all(8),
                      color: Colors.red[100],
                      child: Text(
                        'Error: ${repository.error}',
                        style: TextStyle(color: Colors.red),
                      ),
                    ),
                  
                  SizedBox(height: 20),
                  
                  ElevatedButton(
                    onPressed: repository.isLoading ? null : () => _save(repository),
                    child: repository.isLoading 
                        ? SizedBox(
                            width: 20,
                            height: 20,
                            child: CircularProgressIndicator(strokeWidth: 2),
                          )
                        : Text('Save'),
                  ),
                ],
              ),
            ),
          );
        },
      ),
    );
  }

  Widget _buildImagePickerSection() {
    return Column(
      children: [
        if (_imagePath != null) ...[
          Container(
            height: 200,
            width: double.infinity,
            decoration: BoxDecoration(
              border: Border.all(color: Colors.grey),
              borderRadius: BorderRadius.circular(8),
            ),
            child: ClipRRect(
              borderRadius: BorderRadius.circular(8),
              child: Image.file(
                File(_imagePath!),
                fit: BoxFit.cover,
                errorBuilder: (context, error, stackTrace) {
                  return Icon(Icons.broken_image, size: 50);
                },
              ),
            ),
          ),
          SizedBox(height: 8),
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              TextButton.icon(
                onPressed: _pickImage,
                icon: Icon(Icons.camera_alt),
                label: Text('Change Image'),
              ),
              TextButton.icon(
                onPressed: _clearImage,
                icon: Icon(Icons.delete),
                label: Text('Remove'),
              ),
            ],
          ),
        ] else ...[
          Container(
            height: 200,
            width: double.infinity,
            decoration: BoxDecoration(
              border: Border.all(color: Colors.grey),
              borderRadius: BorderRadius.circular(8),
            ),
            child: InkWell(
              onTap: _pickImage,
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Icon(Icons.add_a_photo, size: 50, color: Colors.grey),
                  SizedBox(height: 8),
                  Text('Add Photo', style: TextStyle(color: Colors.grey)),
                  SizedBox(height: 4),
                  Text('Tap to select from camera or gallery', 
                      style: TextStyle(color: Colors.grey, fontSize: 12)),
                ],
              ),
            ),
          ),
        ],
      ],
    );
  }

  Future<void> _save(ClothingRepository repository) async {
    if (_formKey.currentState!.validate()) {
      try {
        final item = ClothingItem(
          id: '0', 
          name: _nameController.text,
          brand: _brandController.text,
          season: _selectedSeason!,
          year: _selectedYear!,
          category: _selectedCategory!,
          material: _selectedMaterial!,
          imageUrl: _imagePath,
          notes: _notesController.text.isEmpty ? null : _notesController.text,
        );
        
        await repository.add(item);
        
        if (mounted) {
          Navigator.pop(context);
        }
      } catch (e) {
        if (mounted) {
          ScaffoldMessenger.of(context).showSnackBar(
            SnackBar(
              content: Text('Failed to save item: $e'),
              backgroundColor: Colors.red,
            ),
          );
        }
      }
    }
  }
}