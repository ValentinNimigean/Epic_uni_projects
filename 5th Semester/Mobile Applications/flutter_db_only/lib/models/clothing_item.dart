import 'package:equatable/equatable.dart';

class ClothingItem extends Equatable {
  final String id;
  final String name;
  final String brand;
  final String season;
  final int year;
  final String category;
  final String material;
  final String? imageUrl;
  final String? notes;

  const ClothingItem({
    required this.id,
    required this.name,
    required this.brand,
    required this.season,
    required this.year,
    required this.category,
    required this.material,
    this.imageUrl,
    this.notes,
  });

  @override
  List<Object?> get props => [id, name, brand, season, year, category, material, imageUrl, notes];

  ClothingItem copyWith({
    String? id,
    String? name,
    String? brand,
    String? season,
    int? year,
    String? category,
    String? material,
    String? imageUrl,
    String? notes,
  }) {
    return ClothingItem(
      id: id ?? this.id,
      name: name ?? this.name,
      brand: brand ?? this.brand,
      season: season ?? this.season,
      year: year ?? this.year,
      category: category ?? this.category,
      material: material ?? this.material,
      imageUrl: imageUrl ?? this.imageUrl,
      notes: notes ?? this.notes,
    );
  }

  // Convert to Map for database storage
  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'name': name,
      'brand': brand,
      'season': season,
      'year': year,
      'category': category,
      'material': material,
      'image_url': imageUrl,
      'notes': notes,
    };
  }

  // Create ClothingItem from Map (database row)
  factory ClothingItem.fromJson(Map<String, dynamic> json) {
    return ClothingItem(
      id: json['id'].toString(),
      name: json['name'] ?? '',
      brand: json['brand'] ?? '',
      season: json['season'] ?? '',
      year: json['year'] ?? 0,
      category: json['category'] ?? '',
      material: json['material'] ?? '',
      imageUrl: json['image_url'],
      notes: json['notes'],
    );
  }
}
