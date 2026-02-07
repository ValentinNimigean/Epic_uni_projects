import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../providers/payment_provider.dart';
import '../models/payment.dart';

class AddPaymentScreen extends StatefulWidget {
  const AddPaymentScreen({super.key});

  @override
  State<AddPaymentScreen> createState() => _AddPaymentScreenState();
}

class _AddPaymentScreenState extends State<AddPaymentScreen> {
  final _formKey = GlobalKey<FormState>();
  final _dateController = TextEditingController();
  final _amountController = TextEditingController();
  final _typeController = TextEditingController();
  final _categoryController = TextEditingController();
  final _descController = TextEditingController();

  @override
  void dispose() {
    _dateController.dispose();
    _amountController.dispose();
    _typeController.dispose();
    _categoryController.dispose();
    _descController.dispose();
    super.dispose();
  }

  void _submit() async {
    if (_formKey.currentState!.validate()) {
      final provider = Provider.of<PaymentProvider>(context, listen: false);
      if (provider.isOffline) {
         ScaffoldMessenger.of(context).showSnackBar(
           const SnackBar(content: Text("Cannot add payment while offline"))
         );
         return;
      }
      
      final payment = Payment(
        date: _dateController.text,
        amount: double.parse(_amountController.text),
        type: _typeController.text,
        category: _categoryController.text,
        description: _descController.text,
      );
      
      try {
        await provider.addPayment(payment);
        // If we get here, it succeeded
        if (mounted) Navigator.pop(context);
      } catch (e) {
        // Error is already displayed via provider's error handling
        // No need to do anything here
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text("Add Payment")),
      body: Consumer<PaymentProvider>(
        builder: (context, provider, child) {
          if (provider.isOffline) {
            return const Center(child: Text("Offline Mode: Adding payments is disabled."));
          }
          return Padding(
            padding: const EdgeInsets.all(16.0),
            child: Form(
              key: _formKey,
              child: ListView(
                children: [
                  TextFormField(
                    controller: _dateController,
                    decoration: const InputDecoration(labelText: "Date (YYYY-MM-DD)"),
                    validator: (v) {
                       if (v == null || v.isEmpty) return "Required";
                       // Simple regex check
                       if (!RegExp(r'^\d{4}-\d{2}-\d{2}$').hasMatch(v)) return "Format: YYYY-MM-DD";
                       return null;
                    },
                  ),
                  TextFormField(
                    controller: _amountController,
                    decoration: const InputDecoration(labelText: "Amount"),
                    keyboardType: TextInputType.number,
                    validator: (v) {
                      if (v == null || v.isEmpty) return "Required";
                      if (double.tryParse(v) == null) return "Invalid number";
                      return null;
                    },
                  ),
                  TextFormField(
                    controller: _typeController,
                    decoration: const InputDecoration(labelText: "Type (e.g. salary, bonus)"),
                    validator: (v) => v == null || v.isEmpty ? "Required" : null,
                  ),
                  TextFormField(
                    controller: _categoryController,
                    decoration: const InputDecoration(labelText: "Category (e.g. tech, sales)"),
                    validator: (v) => v == null || v.isEmpty ? "Required" : null,
                  ),
                  TextFormField(
                    controller: _descController,
                    decoration: const InputDecoration(labelText: "Description"),
                  ),
                  const SizedBox(height: 20),
                  ElevatedButton(
                    onPressed: provider.isLoading ? null : _submit,
                    child: provider.isLoading 
                      ? const CircularProgressIndicator()
                      : const Text("Save Payment"),
                  ),
                ],
              ),
            ),
          );
        },
      ),
    );
  }
}
