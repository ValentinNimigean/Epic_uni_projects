from domain.domain import Complex
import random
class Memory_repository:
    def __init__(self):
        """
        function initializes the Memory_repository class
        """
        self.__list=[]
        self.__stack=[]
        for i in range(0,10):
            real=str(random.randint(-100, 100))
            imaginary=str(random.randint(-100,100))
            complex_number=Complex(real,imaginary)
            self.__list.append(complex_number)
        self.__stack.append(self.__list.copy())

    def add_to_repository(self,complex_number:Complex):
        """
        function adds complex number to the repository
        :param complex_number:
        :return:
        """
        self.__list.append(complex_number)
        self.__stack.append(self.__list.copy())
    def filter_from_repository(self,start,end):
        """
        function filters numbers out of the repository
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
    def undo(self):
        """
        function replaces the repository with the last element of the stack
        :return:
        """
        self.__stack.pop()
        self.__list=self.__stack[len(self.__stack)-1].copy()

    def get_list(self):
        """
        functions gets the list used for the repository
        :return:
        """
        return self.__list

    def get_stack(self):
        """
        functions gets the stack used for the repository
        :return:
        """
        return self.__stack

