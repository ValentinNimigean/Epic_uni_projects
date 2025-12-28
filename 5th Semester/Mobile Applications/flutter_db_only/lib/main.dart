import 'package:flutter/material.dart';
import 'package:flutter_ui_non_natifve/screens/details_screen.dart';
import 'package:flutter_ui_non_natifve/viewmodels/details_view_model.dart';
import 'package:provider/provider.dart';
import 'models/clothing_item.dart';
import 'repositories/clothing_repository.dart';
import 'screens/home_screen.dart';
import 'screens/add_screen.dart';
import 'screens/edit_screen.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  final ClothingRepository? repository;

  const MyApp({Key? key, this.repository}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    final repo = repository ?? ClothingRepository();
    
    return ChangeNotifierProvider<ClothingRepository>.value(
      value: repo,
      child: MaterialApp(
        title: 'Clothing Archive',
        theme: ThemeData(primarySwatch: Colors.grey),
        home: FutureBuilder(
          future: repo.initialize(),
          builder: (context, snapshot) {
            if (snapshot.connectionState == ConnectionState.waiting) {
              return Scaffold(
                body: Center(child: CircularProgressIndicator()),
              );
            }
            if (snapshot.hasError) {
              return Scaffold(
                body: Center(
                  child: Column(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Icon(Icons.error, size: 64, color: Colors.red),
                      SizedBox(height: 16),
                      Text('Error initializing app: ${snapshot.error}'),
                      SizedBox(height: 16),
                      ElevatedButton(
                        onPressed: () {
                          repo.initialize();
                        },
                        child: Text('Retry'),
                      ),
                    ],
                  ),
                ),
              );
            }
            return ArchiveApp(repository: repo);
          },
        ),
      ),
    );
  }
}

class ArchiveApp extends StatelessWidget {
  final ClothingRepository repository;

  const ArchiveApp({Key? key, required this.repository}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Clothing Archive',
      theme: ThemeData(primarySwatch: Colors.grey),
      initialRoute: '/',
      routes: {
        '/': (context) => HomeScreen(),
        '/add': (context) => AddScreen(),
      },
      onGenerateRoute: (settings) {
        if (settings.name == '/details') {
          return MaterialPageRoute(
            builder: (context) {
              final repository = Provider.of<ClothingRepository>(context, listen: false);
              return DetailsScreen(
                detailsViewModel: DetailsViewModel(clothingRepository: repository),
              );
            },
            settings: settings,
          );
        } else if (settings.name == '/edit') {
          final item = settings.arguments as ClothingItem;
          return MaterialPageRoute(
            builder: (context) => EditScreen(item: item),
          );
        }
        return null;
      },
    );
  }
}
