import 'package:flutter/foundation.dart';
import '../models/clothing_item.dart';
import '../repositories/clothing_repository.dart';


class DetailsScreenState {
  final ClothingItem item;
  DetailsScreenState({required this.item});
}

class DetailsViewModel extends ChangeNotifier {
  final ClothingRepository _clothingRepository;

  DetailsViewModel({required ClothingRepository clothingRepository})
      : _clothingRepository = clothingRepository;

  DetailsScreenState? _detailsScreenState;
  DetailsScreenState? get detailsScreenState => _detailsScreenState;

  Future<void> onLoadItem(String id) async {
    try {
      final item = _clothingRepository.items.firstWhere((item) => item.id == id);
      _detailsScreenState = DetailsScreenState(item: item);
    } catch (e) {
      _detailsScreenState = null;
    }
  }
  void deleteItem() {
    if (_detailsScreenState != null) {
      _clothingRepository.delete(_detailsScreenState!.item.id);
      _detailsScreenState = null;
    }
  }

  @override
  void dispose() {
    super.dispose();
  }
}
