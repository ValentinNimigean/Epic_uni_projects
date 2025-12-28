import 'dart:io';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../repositories/clothing_repository.dart';

class HomeScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Clothing Archive'),
      ),
      body: Column(
        children: [
          Expanded(
            child: Consumer<ClothingRepository>(
              builder: (context, repo, child) {
                if (repo.isLoading) {
                  return Center(child: CircularProgressIndicator());
                }

                if (repo.error != null) {
                  return Center(
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Icon(Icons.error, size: 64, color: Colors.red),
                        SizedBox(height: 16),
                        Text('Error: ${repo.error}'),
                        SizedBox(height: 16),
                        ElevatedButton(
                          onPressed: () {
                            repo.clearError();
                            repo.initialize();
                          },
                          child: Text('Retry'),
                        ),
                      ],
                    ),
                  );
                }

                if (repo.items.isEmpty) {
                  return Center(
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Icon(Icons.inventory_2, size: 64, color: Colors.grey),
                        SizedBox(height: 16),
                        Text('No clothing items yet'),
                        SizedBox(height: 8),
                        Text('Add your first item to get started'),
                      ],
                    ),
                  );
                }

                return GridView.builder(
                  padding: EdgeInsets.all(8.0),
                  gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
                    crossAxisCount: 2,
                    crossAxisSpacing: 8.0,
                    mainAxisSpacing: 8.0,
                    childAspectRatio: 0.85,
                  ),
                  itemCount: repo.items.length,
                  itemBuilder: (context, index) {
                    final item = repo.items[index];
                    return Card(
                      child: InkWell(
                        onTap: () => Navigator.pushNamed(context, '/details', arguments: item.id),
                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.stretch,
                          children: [
                            Expanded(
                              child: _buildImageWidget(item.imageUrl),
                            ),
                            Padding(
                              padding: const EdgeInsets.all(8.0),
                              child: Column(
                                crossAxisAlignment: CrossAxisAlignment.start,
                                children: [
                                  Text(item.name, style: TextStyle(fontWeight: FontWeight.bold)),
                                  Text('${item.brand} - ${item.season}${item.year}'),
                                ],
                              ),
                            ),
                          ],
                        ),
                      ),
                    );
                  },
                );
              },
            ),
          ),
          Container(
            width: double.infinity,
            padding: EdgeInsets.all(16.0),
            child: ElevatedButton(
              style: ElevatedButton.styleFrom(
                backgroundColor: Colors.black,
                foregroundColor: Colors.white,
                padding: EdgeInsets.symmetric(vertical: 16.0, horizontal: 32.0),
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(0.0)),
              ),
              onPressed: () => Navigator.pushNamed(context, '/add'),
              child: Text('Add Clothing Item'),
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildImageWidget(String? imageUrl) {
    if (imageUrl == null || imageUrl.isEmpty) {
      return Icon(Icons.image, size: 50);
    }

    return ClipRRect(
      child: Image.file(
        File(imageUrl),
        fit: BoxFit.cover,
        errorBuilder: (context, error, stackTrace) => Icon(Icons.broken_image, size: 50),
      ),
    );
  }
}