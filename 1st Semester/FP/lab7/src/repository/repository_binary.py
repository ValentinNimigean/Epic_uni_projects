import pickle
import random
from src.domain.domain import Complex
import  os

class Binary_repository:
    def __init__(self):
        """
        function creates the Binary_repository class
        """
        self.__list=[]
        self.__stack=[]
        check_file = os.stat("pickle_numbers.pkl").st_size
        if check_file==0:
            for i in range(0, 10):
                real = str(random.randint(-100, 100))
                imaginary = str(random.randint(-100, 100))
                complex_number = Complex(real, imaginary)
                self.__list.append(complex_number)
            self.save_list_file("pickle_numbers.pkl")
        else:
            self.__list=self.load_list_file("pickle_numbers.pkl")
        self.__stack.append(self.__list.copy())





    def add_to_repository(self,complex_number:Complex):
        """
        function adds number to repository
        :param complex_number:
        :return:
        """

        self.__list.append(complex_number)
        self.__stack.append(self.__list.copy())
        self.save_list_file("pickle_numbers.pkl")
    def filter_from_repository(self,start,end):
        """
        function filters out the numbers in (start-end)
        :param start:
        :param end:
        :return:
        """
        list1=[]
        for i in range(len(self.__list)):
            if i>=start-1 and i <=end-1:
                list1.append(self.__list[i])
        self.__list=list1.copy()
        self.__stack.append(self.__list.copy())
        self.save_list_file("pickle_numbers.pkl")

    def get_stack(self):
        """
        function returns the stack
        :return:
        """
        return self.__stack
    def get_list(self):
        """
        function returns the list
        :return:
        """
        return self.__list
    def undo(self):
        """
        function undoes the last step
        :return:
        """
        self.__stack.pop()
        self.__list=self.__stack[len(self.__stack)-1].copy()
        self.save_list_file("pickle_numbers.pkl")


    def load_list_file(self,pklfile):
        """
        function loads the list of numbers from the pickle file
        :param pklfile:
        :return:
        """
        list1 = []
        numbers = open(pklfile, "rb")
        while True:
            try:
                number = pickle.load(numbers)
                list1.append(number)
            except EOFError:
                break
        numbers.close()
        return list1

    def save_list_file(self,pklfile):
        """
        the function puts the list of numbers into the pickle file
        :param pklfile:
        :return:
        """
        numbers = open(pklfile, "wb")
        for i in self.__list:
            pickle.dump(i,numbers)
        numbers.close()