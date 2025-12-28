import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/clothing_item.dart';
import '../repositories/clothing_repository.dart';

class EditScreen extends StatefulWidget {
  final ClothingItem item;
  const EditScreen({Key? key, required this.item}) : super(key: key);

  @override
  State<EditScreen> createState() => _EditScreenState();
}

class _EditScreenState extends State<EditScreen> {
  final _formKey = GlobalKey<FormState>();
  late ClothingItem _item;

  late final TextEditingController _nameController;
  late final TextEditingController _brandController;
  late final TextEditingController _imageUrlController;
  late final TextEditingController _notesController;

  final List<String> _seasons = ['SS', 'AW'];
  final List<int> _years = List<int>.generate(100, (i) => DateTime.now().year - i);
  final List<String> _categories = ['T-shirt', 'Pants', 'Jacket', 'Outerwear', 'Tops', 'Bottoms', 'Shoes', 'Accessories', 'Dresses'];
  final List<String> _materials = ['Cotton', 'Denim', 'Schoeller Dryskin', 'Wool', 'Leather', 'Synthetic', 'Silk', 'Polyester'];

  @override
  void initState() {
    super.initState();
    _item = widget.item;
    _nameController = TextEditingController(text: _item.name);
    _brandController = TextEditingController(text: _item.brand);
    _imageUrlController = TextEditingController(text: _item.imageUrl);
    _notesController = TextEditingController(text: _item.notes);
  }

  @override
  void dispose() {
    _nameController.dispose();
    _brandController.dispose();
    _imageUrlController.dispose();
    _notesController.dispose();
    super.dispose();
  }

  void _saveForm() {
    if (_formKey.currentState!.validate()) {
      final updatedItem = _item.copyWith(
        name: _nameController.text,
        brand: _brandController.text,
        imageUrl: _imageUrlController.text,
        notes: _notesController.text,
      );
      context.read<ClothingRepository>().update(updatedItem);
      Navigator.of(context).pop();
    }
  }

  void _deleteItem() async {
    final shouldDelete = await showDialog<bool>(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Delete Item'),
        content: const Text('Are you sure you want to delete this item?'),
        actions: [
          TextButton(
            onPressed: () => Navigator.of(context).pop(true),
            child: const Text('Cancel'),
          ),
          TextButton(
            onPressed: () => Navigator.of(context).pop(true),
            child: const Text('Delete'),
          ),
        ],
      ),
    );
    if (shouldDelete == true) {
      context.read<ClothingRepository>().delete(_item.id);
      Navigator.of(context).pushNamedAndRemoveUntil('/', (route) => false);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Edit Item'),
      ),
      body: Form(
        key: _formKey,
        child: ListView(
          padding: const EdgeInsets.all(16.0),
          children: [
            TextFormField(
              controller: _nameController,
              decoration: const InputDecoration(labelText: 'Name', border: OutlineInputBorder()),
              validator: (value) => value!.isEmpty ? 'Required' : null,
            ),
            const SizedBox(height: 16),
            TextFormField(
              controller: _brandController,
              decoration: const InputDecoration(labelText: 'Brand', border: OutlineInputBorder()),
              validator: (value) => value!.isEmpty ? 'Required' : null,
            ),
            const SizedBox(height: 16),
            DropdownButtonFormField<String>(
              value: _item.season,
              decoration: const InputDecoration(labelText: 'Season', border: OutlineInputBorder()),
              items: _seasons.map((s) => DropdownMenuItem(value: s, child: Text(s))).toList(),
              onChanged: (value) {
                if (value != null) {
                  setState(() => _item = _item.copyWith(season: value));
                }
              },
            ),
            const SizedBox(height: 16),
            DropdownButtonFormField<int>(
              initialValue: _item.year,
              decoration: const InputDecoration(labelText: 'Year', border: OutlineInputBorder()),
              items: _years.map((y) => DropdownMenuItem(value: y, child: Text(y.toString()))).toList(),
              onChanged: (value) {
                setState(() => _item = _item.copyWith(year: value));
              },
            ),
            const SizedBox(height: 16),
            DropdownButtonFormField<String>(
              initialValue: _item.category,
              decoration: const InputDecoration(labelText: 'Category', border: OutlineInputBorder()),
              items: _categories.map((c) => DropdownMenuItem(value: c, child: Text(c))).toList(),
              onChanged: (value) {
                if (value != null) {
                  setState(() => _item = _item.copyWith(category: value));
                }
              },
            ),
            const SizedBox(height: 16),
            DropdownButtonFormField<String>(
              initialValue: _item.material,
              decoration: const InputDecoration(labelText: 'Material', border: OutlineInputBorder()),
              items: _materials.map((m) => DropdownMenuItem(value: m, child: Text(m))).toList(),
              onChanged: (value) {
                if (value != null) {
                  setState(() => _item = _item.copyWith(material: value));
                }
              },
            ),
            const SizedBox(height: 16),
            TextFormField(
              controller: _imageUrlController,
              decoration: const InputDecoration(labelText: 'Image URL', border: OutlineInputBorder()),
            ),
            const SizedBox(height: 16),
            TextFormField(
              controller: _notesController,
              decoration: const InputDecoration(labelText: 'Notes', border: OutlineInputBorder()),
              maxLines: 3,
            ),
            const SizedBox(height: 32),
            Row(
              children: [
                Expanded(
                  child: ElevatedButton(
                    style: ElevatedButton.styleFrom(
                      backgroundColor: Colors.black,
                      foregroundColor: Colors.white,
                      padding: const EdgeInsets.symmetric(vertical: 16.0),
                      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(0)),
                    ),
                    onPressed: _saveForm,
                    child: const Text('SAVE'),
                  ),
                ),
                const SizedBox(width: 16),
                Expanded(
                  child: ElevatedButton(
                    style: ElevatedButton.styleFrom(
                      backgroundColor: Colors.red,
                      foregroundColor: Colors.white,
                      padding: const EdgeInsets.symmetric(vertical: 16.0),
                      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(0)),
                    ),
                    onPressed: _deleteItem,
                    child: const Text('DELETE'),
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
