from domain.domain import Complex
import random

class File_repository:
    def __init__(self):
        """
        function builds the File_repository class
        """
        self.__list=[]
        self.__stack=[]
        self.__list=self.load_list_file("txt_numbers.txt")
        if len(self.__list)==0:
            for i in range(0, 10):
                real = str(random.randint(-100, 100))
                imaginary = str(random.randint(-100, 100))
                complex_number = Complex(real, imaginary)
                self.__list.append(complex_number)
        self.save_list_file("txt_numbers.txt")
        self.__stack.append(self.__list.copy())


    def load_list_file(self,file):
        """
        function loads the list of numbers from a text file
        :param file: text file
        :return:
        """
        list1=[]
        numbers=open(file,"r")
        for number in numbers:
            number=number.strip()
            number=number.split("|")

            list1.append(Complex(number[0],number[1]))
        numbers.close()


        return list1

    def save_list_file(self,file):
        """
         function saves the list of numbers into a text file
        :param file:
        :return:
        """
        numbers=open(file,'w')
        for i in self.__list:
            numbers.write(Complex.get_real(i)+'|'+Complex.get_imaginary(i)+'\n')
        numbers.close()


    def add_to_repository(self,complex_number:Complex):
        """
        function adds a number to the list
        :param complex_number:
        :return:
        """
        self.__list=self.load_list_file("txt_numbers.txt")
        self.__list.append(complex_number)
        self.__stack.append(self.__list.copy())
        self.save_list_file("txt_numbers.txt")
    def filter_from_repository(self,start,end):
        """
        function filters the numbers in the interval (start-end) from the list
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
        self.save_list_file("txt_numbers.txt")

    def get_stack(self):
        """
        function gets the stack
        :return:
        """
        return self.__stack
    def get_list(self):
        """
        function gets the list
        :return:
        """
        return self.load_list_file("txt_numbers.txt")
    def undo(self):
        """
        function undoes the last step
        :return:
        """
        self.__stack.pop()
        self.__list=self.__stack[len(self.__stack)-1]
        self.save_list_file("txt_numbers.txt")






