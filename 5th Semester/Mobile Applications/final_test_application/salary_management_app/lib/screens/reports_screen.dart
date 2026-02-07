import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../providers/payment_provider.dart';

class ReportsScreen extends StatefulWidget {
  const ReportsScreen({super.key});

  @override
  State<ReportsScreen> createState() => _ReportsScreenState();
}

class _ReportsScreenState extends State<ReportsScreen> {
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
      appBar: AppBar(title: const Text("Monthly Payroll Analysis")),
      body: Consumer<PaymentProvider>(
        builder: (context, provider, child) {
          if (provider.isLoading && provider.allPayments.isEmpty) {
            return const Center(child: CircularProgressIndicator());
          }
          final analysis = provider.monthlyAnalysis;
          if (analysis.isEmpty) {
            return const Center(child: Text("No data available."));
          }
          return ListView.builder(
            itemCount: analysis.length,
            itemBuilder: (context, index) {
              String month = analysis.keys.elementAt(index);
              double total = analysis[month]!;
              return Card(
                child: ListTile(
                  title: Text(month),
                  trailing: Text(total.toStringAsFixed(2)),
                ),
              );
            },
          );
        },
      ),
    );
  }
}
