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
                              child: item.imageUrl != null
                                  ? Image.network(
                                      item.imageUrl!,
                                      fit: BoxFit.cover,
                                      errorBuilder: (context, error, stackTrace) => Icon(Icons.image, size: 50),
                                    )
                                  : Icon(Icons.image, size: 50),
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

}