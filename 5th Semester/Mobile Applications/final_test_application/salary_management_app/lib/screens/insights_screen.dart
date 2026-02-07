import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../providers/payment_provider.dart';

class InsightsScreen extends StatefulWidget {
  const InsightsScreen({super.key});

  @override
  State<InsightsScreen> createState() => _InsightsScreenState();
}

class _InsightsScreenState extends State<InsightsScreen> {
  @override
  void initState() {
    super.initState();
    WidgetsBinding.instance.addPostFrameCallback((_) {
      Provider.of<PaymentProvider>(context, listen: false).fetchAllPayments();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("Top Departments")),
      body: Consumer<PaymentProvider>(
        builder: (context, provider, child) {
          if (provider.isLoading && provider.allPayments.isEmpty) {
             return const Center(child: CircularProgressIndicator());
          }
          final topDepts = provider.topDepartments;
          if (topDepts.isEmpty) {
             return const Center(child: Text("No data available."));
          }
          return ListView.builder(
            itemCount: topDepts.length,
            itemBuilder: (context, index) {
               final entry = topDepts[index];
               return Card(
                 child: ListTile(
                   leading: CircleAvatar(child: Text("${index + 1}")),
                   title: Text(entry.key),
                   trailing: Text(entry.value.toStringAsFixed(2)),
                 ),
               );
            },
          );
        },
      ),
    );
  }
}
