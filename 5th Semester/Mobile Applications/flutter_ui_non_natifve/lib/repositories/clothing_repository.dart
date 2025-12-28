import 'package:flutter/foundation.dart';
import '../models/clothing_item.dart';

class ClothingRepository extends ChangeNotifier {
  List<ClothingItem> _items = [
    const ClothingItem(
      id: '1',
      name: 'Denim Jacket',
      brand: 'RAF SIMONS',
      season: 'AW',
      year: 2016,
      category: 'Jacket',
      material: 'Denim',
      imageUrl: 'https://image-cdn.hypb.st/https%3A%2F%2Fs3.store.hypebeast.com%2Fmedia%2Fimage%2Fec%2F5d%2Fjacket-2-1-c4d98.jpg?fit=max&w=720&q=90',
      notes: 'Iconic piece from a great collection.',
    ),
    const ClothingItem(
      id: '2',
      name: 'Distressed Jeans',
      brand: 'HELMUT LANG',
      season: 'SS',
      year: 2001,
      category: 'Pants',
      material: 'Denim',
      imageUrl: 'https://endyma.com/cdn/shop/products/EmptyName_363.jpg?v=1571271421&width=1946',
      notes: 'Classic painter jeans.',
    ),
    const ClothingItem(
      id: '3',
      name: 'Black Tee',
      brand: 'COMME DES GARÇONS',
      season: 'SS',
      year: 2018,
      category: 'T-shirt',
      material: 'Cotton',
      notes: '',
    ),
    const ClothingItem(
      id: '4',
      name: 'Cargo Pants',
      brand: 'ACRONYM',
      season: 'FW',
      year: 2020,
      category: 'Pants',
      material: 'Schoeller Dryskin',
      notes: 'P10-DS model',
    ),
    const ClothingItem(
      id: '5',
      name: 'DHL T-Shirt',
      brand: 'VETEMENTS',
      season: 'SS',
      year: 2016,
      category: 'T-shirt',
      material: 'Cotton',
      imageUrl: 'https://thewebster.com/media/catalog/product/1/7/1764265469220351020-1.jpg?quality=100&fit=bounds&height=&width=',
    ),
    const ClothingItem(
      id: '6',
      name: 'Reworked Denim',
      brand: 'VETEMENTS',
      season: 'SS',
      year: 2017,
      category: 'Pants',
      material: 'Denim',
      imageUrl: 'https://media-assets.grailed.com/prd/listing/temp/14e4aaa9504b43568d70cee90f8afbc9?',
      notes: 'Collaboration with Levi\'s.',
    ),
  ];

  List<ClothingItem> get items => List.unmodifiable(_items);

  ClothingItem add(ClothingItem item) {
    _items = List.from(_items)..add(item);
    notifyListeners();
    return item;
  }

  ClothingItem update(ClothingItem item) {
    final index = _items.indexWhere((i) => i.id == item.id);
    if (index != -1) {
      _items = List.from(_items)..[index] = item;
      notifyListeners();
      return item;
    }
    throw Exception('Item not found');
  }

  void delete(String id) {
    _items = _items.where((item) => item.id != id).toList();
    notifyListeners();
  }
}
