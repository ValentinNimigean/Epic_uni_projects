import 'package:flutter/material.dart';
import 'package:flutter_ui_non_natifve/screens/details_screen.dart';
import 'package:flutter_ui_non_natifve/viewmodels/details_view_model.dart';
import 'package:provider/provider.dart';
import 'models/clothing_item.dart';
import 'repositories/clothing_repository.dart';
import 'screens/home_screen.dart';
import 'screens/add_screen.dart';
import 'screens/edit_screen.dart';

void main() {
  runApp(ArchiveApp());
}

class ArchiveApp extends StatelessWidget {


  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (_) => ClothingRepository(),
      child: MaterialApp(
        title: 'Clothing Archive',
        theme: ThemeData(primarySwatch: Colors.blue),
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
      ),
    );
  }
}

