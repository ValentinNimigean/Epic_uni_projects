class mills:
    def __init__(self):
        self.__mills = []
        self.__mills.append([])
        self.__mills.append([[2, 3],[10, 22]])
        self.__mills.append([[1, 3],[5, 8]])
        self.__mills.append([[1, 2],[15, 24]])
        self.__mills.append([[5, 6], [11, 19]])
        self.__mills.append([[4, 6], [2, 8]])
        self.__mills.append([[4, 5], [14, 21]])
        self.__mills.append([[8, 9], [12, 16]])
        self.__mills.append([[7, 9], [2, 5]])
        self.__mills.append([[7, 8], [13, 18]])
        self.__mills.append([[11, 12], [1, 22]])
        self.__mills.append([[10, 12], [4, 19]])
        self.__mills.append([[10, 11], [7, 16]])
        self.__mills.append([[14, 15], [9, 18]])
        self.__mills.append([[13, 15], [6, 21]])
        self.__mills.append([[13, 14], [3, 24]])
        self.__mills.append([[17, 18], [7, 12]])
        self.__mills.append([[16, 18], [20, 23]])
        self.__mills.append([[16, 17], [9, 13]])
        self.__mills.append([[20, 21], [4, 11]])
        self.__mills.append([[19, 21], [17, 23]])
        self.__mills.append([[19, 20], [6, 14]])
        self.__mills.append([[23, 24], [1, 10]])
        self.__mills.append([[22, 24], [17, 20]])
        self.__mills.append([[22, 23], [3, 15]])
    def get_mills(self):
        return self.__mills

class moves:
    def __init__(self):
        self.__moves = []
        self.__moves.append([])
        self.__moves.append([2,10])
        self.__moves.append([1,3,5])
        self.__moves.append([2,15])
        self.__moves.append([5,11])
        self.__moves.append([2,4,6,8])
        self.__moves.append([5,14])
        self.__moves.append([8,12])
        self.__moves.append([5,7,9])
        self.__moves.append([8,13])
        self.__moves.append([1,11,22])
        self.__moves.append([4,10,12,19])
        self.__moves.append([7,11,16])
        self.__moves.append([9,14,18])
        self.__moves.append([6,13,15,21])
        self.__moves.append([3,14,24])
        self.__moves.append([12,17])
        self.__moves.append([16,18,20])
        self.__moves.append([13,17])
        self.__moves.append([11,20])
        self.__moves.append([17,19,21,23])
        self.__moves.append([14,20])
        self.__moves.append([10,23])
        self.__moves.append([20,22,24])
        self.__moves.append([15,23])



    def get_moves(self):
        return self.__moves

