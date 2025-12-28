import 'dart:io';
import 'package:flutter/material.dart';
import '../viewmodels/details_view_model.dart';

class DetailsScreen extends StatefulWidget {
  final DetailsViewModel detailsViewModel;

  const DetailsScreen({super.key, required this.detailsViewModel});

  @override
  State<DetailsScreen> createState() => _DetailsScreenState();
}

class _DetailsScreenState extends State<DetailsScreen> {
  @override
  void didChangeDependencies() {
    super.didChangeDependencies();
    final itemId = ModalRoute.of(context)!.settings.arguments as String;
    widget.detailsViewModel.onLoadItem(itemId);
  }

  @override
  void dispose() {
    widget.detailsViewModel.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return ListenableBuilder(
      listenable: widget.detailsViewModel,
      builder: (context, child) {
        final state = widget.detailsViewModel.detailsScreenState;
        if (state == null) {
          return Scaffold(
            appBar: AppBar(title: const Text("Loading...")),
            body: const Center(child: CircularProgressIndicator()),
          );
        }

        final item = state.item;
        return Scaffold(
          backgroundColor: Colors.white,
          appBar: AppBar(
            title: Text(item.name, style: const TextStyle(color: Colors.black)),
            backgroundColor: Colors.white,
            elevation: 0,
            leading: const BackButton(color: Colors.black),
          ),
          body: Padding(
            padding: const EdgeInsets.symmetric(horizontal: 16.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                _buildImageWidget(item.imageUrl),
                const SizedBox(height: 24),
                Text(item.brand.toUpperCase(),
                    style: const TextStyle(fontSize: 24, fontWeight: FontWeight.bold)),
                const SizedBox(height: 4),
                Text(item.name, style: const TextStyle(fontSize: 20)),
                const SizedBox(height: 4),
                Text('${item.season}${item.year}', style: const TextStyle(fontSize: 16)),
                const SizedBox(height: 24),
                Text('Category: ${item.category}', style: const TextStyle(fontSize: 16)),
                const SizedBox(height: 8),
                Text('Material: ${item.material}', style: const TextStyle(fontSize: 16)),
                const SizedBox(height: 24),
                if (item.notes != null && item.notes!.isNotEmpty) ...[
                  const Text('Notes:', style: TextStyle(fontSize: 16, fontWeight: FontWeight.bold)),
                  const SizedBox(height: 4),
                  Text(item.notes!, style: const TextStyle(fontSize: 16)),
                ],
                const Spacer(),
                Padding(
                  padding: const EdgeInsets.only(bottom: 16.0, top: 16.0),
                  child: SizedBox(
                    width: double.infinity,
                    child: ElevatedButton(
                      style: ElevatedButton.styleFrom(
                        backgroundColor: Colors.black,
                        foregroundColor: Colors.white,
                        padding: const EdgeInsets.symmetric(vertical: 16.0),
                        shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(0)),
                      ),
                      onPressed: () {
                        Navigator.pushNamed(context, '/edit', arguments: item);
                      },
                      child: const Text('EDIT'),
                    ),
                  ),
                ),
              ],
            ),
          ),
        );
      },
    );
  }

  Widget _buildImageWidget(String? imageUrl) {
    if (imageUrl == null || imageUrl.isEmpty) {
      return const SizedBox(height: 400, child: Icon(Icons.image, size: 200));
    }

    // Only handle local files
    return ClipRRect(
      child: SizedBox(
        height: 400,
        width: double.infinity,
        child: Image.file(
          File(imageUrl),
          fit: BoxFit.cover,
          errorBuilder: (context, error, stackTrace) => 
              const SizedBox(height: 400, child: Icon(Icons.broken_image, size: 200)),
        ),
      ),
    );
  }
}