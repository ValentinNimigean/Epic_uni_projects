class Payment {
  final int? id;
  final String date;
  final double amount;
  final String type;
  final String category;
  final String description;

  Payment({
    this.id,
    required this.date,
    required this.amount,
    required this.type,
    required this.category,
    required this.description,
  });

  factory Payment.fromJson(Map<String, dynamic> json) {
    return Payment(
      id: json['id'],
      date: json['date'],
      amount: (json['amount'] as num).toDouble(),
      type: json['type'],
      category: json['category'],
      description: json['description'],
    );
  }

  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'date': date,
      'amount': amount,
      'type': type,
      'category': category,
      'description': description,
    };
  }
}
