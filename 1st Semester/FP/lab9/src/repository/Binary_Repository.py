from src.domain.Student import *
from src.domain.Discipline import *
from src.domain.Grade import *
from src.repository.Repository import Student_Repository
import  pickle
class Student_Binary_Repository:
    def __init__(self,file):
        self.__list=[]
        self.__file=file


    def repo_add(self,student):
        """
        adds student to memory
        :param student:
        :return:
        """
        self.__list.append(student)
        self.save_to_file(self.__file)

    def repo_remove(self,student):
        """
        removes student from memory
        :param student:
        :return:
        """
        self.__list.remove(student)
        self.save_to_file(self.__file)

    def get_list(self):
        """

        :return:
        """
        return self.__list


    def update(self,element):
        """
        updates a student from memory
        :param element:
        :return:
        """
        id = element.get_id()
        ids = [i.get_id() for i in self.__list]
        poz = ids.index(id)
        self.__list[poz] = element
        self.save_to_file(self.__file)
    def save_to_file(self,file):
        list=open(file,"wb")
        for i in self.__list:
            pickle.dump(i,list)
        list.close()

    def load_from_file(self,file):
        list=open(file,"rb")
        while True:
            try:
                i=pickle.load(list)
                self.__list.append(i)
            except EOFError:
                break
        list.close()


class Discipline_Binary_Repository:
    def __init__(self,file):
        """
        builds discipline repository
        """
        self.__list = []
        self.__file=file


    def repo_add(self, element):
        """
        adds to memory
        :param element:
        :return:
        """
        self.__list.append(element)
        self.save_to_file(self.__file)

    def repo_remove(self, element):
        """
        removes from memory
        :param element:
        :return:
        """
        self.__list.remove(element)
        self.save_to_file(self.__file)

    def get_list(self):

        return self.__list

    def update(self, element):
        """
        updtaes element in memory
        :param element:
        :return:
        """
        id = element.get_id()
        ids = [i.get_id() for i in self.__list]
        poz = ids.index(id)
        self.__list[poz] = element
        self.save_to_file(self.__file)

    def save_to_file(self,file):
        list=open(file,"wb")
        for i in self.__list:
            pickle.dump(i,list)
        list.close()

    def load_from_file(self,file):
        list=open(file,"rb")
        while True:
            try:
                i=pickle.load(list)
                self.__list.append(i)
            except EOFError:
                break


class Grade_Binary_Repository:
    def __init__(self,file):
        self.__list = []
        self.__file=file



    def repo_add(self, element):
        self.__list.append(element)
        self.save_to_file(self.__file)

    def repo_remove(self, element):
        self.__list.remove(element)
        self.save_to_file(self.__file)

    def get_list(self):
        return self.__list


    def save_to_file(self,file):
        list=open(file,"wb")
        for i in self.__list:
            pickle.dump(i,list)

        list.close()

    def load_from_file(self,file):
        list=open(file,"rb")
        while True:
            try:
                i=pickle.load(list)
                self.__list.append(i)
            except EOFError:
                break
        list.close()








