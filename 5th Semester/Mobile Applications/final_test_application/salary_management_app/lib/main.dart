import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'providers/payment_provider.dart';
import 'screens/payments_list_screen.dart';
import 'screens/reports_screen.dart';
import 'screens/insights_screen.dart';
import 'screens/add_payment_screen.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (context) => PaymentProvider(),
      child: MaterialApp(
        title: 'Salary Manager',
        theme: ThemeData(
          colorScheme: ColorScheme.fromSeed(seedColor: Colors.blue),
          useMaterial3: true,
        ),
        home: const HomeScreen(),
      ),
    );
  }
}

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});
  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  int _currentIndex = 0;
  final List<Widget> _screens = [
    const PaymentsListScreen(),
    const ReportsScreen(),
    const InsightsScreen(),
  ];

  late final PaymentProvider _provider;
  VoidCallback? _listener;

  @override
  void initState() {
    super.initState();
    _provider = Provider.of<PaymentProvider>(context, listen: false);
    _listener = () {
      if (!mounted) return;
       if (_provider.errorMessage != null) {
          ScaffoldMessenger.of(context).showSnackBar(
             SnackBar(content: Text(_provider.errorMessage!))
          );
          _provider.clearError();
       }
       if (_provider.notification != null) {
          final String message = _provider.notification!;
          showDialog(
            context: context,
            builder: (ctx) => AlertDialog(
              title: const Text("New Notification"),
              content: Text(message),
              actions: [
                TextButton(
                  onPressed: ()=>Navigator.pop(ctx), 
                  child: const Text("OK")
                )
              ],
            )
          );
          _provider.clearNotification();
       }
       if (_provider.successMessage != null) {
          ScaffoldMessenger.of(context).showSnackBar(
             SnackBar(
               content: Text(_provider.successMessage!),
               backgroundColor: Colors.green,
               duration: const Duration(seconds: 2),
             )
          );
          _provider.clearSuccessMessage();
       }
    };
    _provider.addListener(_listener!);
  }
  
  @override
  void dispose() {
    _provider.removeListener(_listener!);
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Salary Manager"),
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        actions: [
          Consumer<PaymentProvider>(
            builder: (context, provider, child) {
               return Padding(
                 padding: const EdgeInsets.only(right: 16.0),
                 child: Icon(
                   provider.isOffline ? Icons.wifi_off : Icons.wifi,
                   color: provider.isOffline ? Colors.red : Colors.green,
                 ),
               );
            },
          ),
        ],
      ),
      body: Column(
        children: [
          Consumer<PaymentProvider>(
            builder: (context, provider, child) {
              if (provider.isOffline) {
                return Container(
                  color: Colors.red,
                  padding: const EdgeInsets.all(8.0),
                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                       const Text("Offline Mode", style: TextStyle(color: Colors.white)),
                       const SizedBox(width: 10),
                       TextButton(
                         onPressed: () {
                           provider.fetchPayments();
                         }, 
                         style: TextButton.styleFrom(
                           backgroundColor: Colors.white,
                         ),
                         child: const Text("Retry Connection")
                       )
                    ],
                  ),
                );
              }
              return const SizedBox.shrink(); 
            },
          ),
          Expanded(child: _screens[_currentIndex]),
        ],
      ),
      bottomNavigationBar: BottomNavigationBar(
        currentIndex: _currentIndex,
        onTap: (index) => setState(() => _currentIndex = index),
        items: const [
          BottomNavigationBarItem(icon: Icon(Icons.list), label: "Main"),
          BottomNavigationBarItem(icon: Icon(Icons.analytics), label: "Reports"),
          BottomNavigationBarItem(icon: Icon(Icons.insights), label: "Insights"),
        ],
      ),
      floatingActionButton: _currentIndex == 0 ? FloatingActionButton(
        onPressed: () {
           Navigator.push(context, MaterialPageRoute(builder: (c) => const AddPaymentScreen()));
        },
        child: const Icon(Icons.add),
      ) : null,
    );
  }
}
