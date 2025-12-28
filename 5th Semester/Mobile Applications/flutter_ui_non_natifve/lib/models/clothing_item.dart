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
}
