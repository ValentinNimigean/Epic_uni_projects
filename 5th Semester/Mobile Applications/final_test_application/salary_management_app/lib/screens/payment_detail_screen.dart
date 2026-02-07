import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../providers/payment_provider.dart';
import '../models/payment.dart';

class PaymentDetailScreen extends StatelessWidget {
  final int id;
  const PaymentDetailScreen({super.key, required this.id});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("Payment Details")),
      body: FutureBuilder<Payment?>(
        future: Provider.of<PaymentProvider>(context, listen: false).getPaymentDetail(id),
        builder: (context, snapshot) {
          if (snapshot.connectionState == ConnectionState.waiting) {
            return const Center(child: CircularProgressIndicator());
          }
          if (snapshot.hasError) {
             return Center(child: Text("Error: ${snapshot.error}"));
          }
          if (!snapshot.hasData || snapshot.data == null) {
            return const Center(child: Text("Payment not found"));
          }
          
          final payment = snapshot.data!;
          return Padding(
            padding: const EdgeInsets.all(16.0),
            child: Card(
              elevation: 4,
              child: Padding(
                padding: const EdgeInsets.all(16.0),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Text("ID: ${payment.id}", style: Theme.of(context).textTheme.bodySmall),
                    const SizedBox(height: 8),
                    Text("Amount: ${payment.amount}", style: Theme.of(context).textTheme.headlineMedium),
                    const SizedBox(height: 8),
                    Text("Date: ${payment.date}", style: Theme.of(context).textTheme.titleMedium),
                    const Divider(),
                    Text("Type: ${payment.type}"),
                    Text("Category: ${payment.category}"),
                    const SizedBox(height: 16),
                    Text("Description:", style: Theme.of(context).textTheme.titleSmall),
                    Text(payment.description),
                  ],
                ),
              ),
            ),
          );
        },
      ),
    );
  }
}
