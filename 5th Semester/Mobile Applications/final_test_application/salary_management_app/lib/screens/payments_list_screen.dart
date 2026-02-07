import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../providers/payment_provider.dart';
import 'payment_detail_screen.dart';

class PaymentsListScreen extends StatefulWidget {
  const PaymentsListScreen({super.key});

  @override
  State<PaymentsListScreen> createState() => _PaymentsListScreenState();
}

class _PaymentsListScreenState extends State<PaymentsListScreen> {
  @override
  void initState() {
    super.initState();
    // Fetch payments on load
    WidgetsBinding.instance.addPostFrameCallback((_) {
      Provider.of<PaymentProvider>(context, listen: false).fetchPayments();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Consumer<PaymentProvider>(
      builder: (context, provider, child) {
        if (provider.isLoading && provider.payments.isEmpty) {
          return const Center(child: CircularProgressIndicator());
        }
        
        if (provider.payments.isEmpty) {
             return Center(
               child: Column(
                 mainAxisAlignment: MainAxisAlignment.center,
                 children: [
                   const Text("No payments found."),
                   ElevatedButton(
                     onPressed: () => provider.fetchPayments(), 
                     child: const Text("Retry")
                   )
                 ],
               ),
             );
        }

        return RefreshIndicator(
          onRefresh: () => provider.fetchPayments(),
          child: ListView.builder(
            itemCount: provider.payments.length,
            itemBuilder: (context, index) {
              final payment = provider.payments[index];
              return Card(
                child: ListTile(
                  title: Text("${payment.category} - ${payment.amount}"),
                  subtitle: Text(payment.date),
                  onTap: () {
                    Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (context) => PaymentDetailScreen(id: payment.id!),
                      ),
                    );
                  },
                  trailing: IconButton(
                    icon: const Icon(Icons.delete, color: Colors.red),
                    onPressed: () {
                       if (provider.isOffline) {
                         ScaffoldMessenger.of(context).showSnackBar(
                           const SnackBar(content: Text("Cannot delete while offline")),
                         );
                         return;
                       }
                       showDialog(
                         context: context,
                         builder: (ctx) => AlertDialog(
                           title: const Text("Delete Payment?"),
                           content: const Text("Are you sure?"),
                           actions: [
                             TextButton(
                               onPressed: () => Navigator.pop(ctx),
                               child: const Text("Cancel"),
                             ),
                             TextButton(
                               onPressed: () {
                                 Navigator.pop(ctx);
                                 provider.deletePayment(payment.id!);
                               },
                               child: const Text("Delete"),
                             ),
                           ],
                         ),
                       );
                    },
                  ),
                ),
              );
            },
          ),
        );
      },
    );
  }
}
