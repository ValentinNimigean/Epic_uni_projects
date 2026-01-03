from src.domain.Student import Student
from src.domain.Discipline import Discipline
class Student_Repository:
    def __init__(self):
        self.__list=[]

    def repo_add(self,student):
        """
        adds student to memory
        :param student:
        :return:
        """
        self.__list.append(student)

    def repo_remove(self,student):
        """
        removes student from memory
        :param student:
        :return:
        """
        self.__list.remove(student)

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

class Discipline_Repository:
    def __init__(self):
        """
        builds discipline repository
        """
        self.__list = []

    def repo_add(self, element):
        """
        adds to memory
        :param element:
        :return:
        """
        self.__list.append(element)

    def repo_remove(self, element):
        """
        removes from memory
        :param element:
        :return:
        """
        self.__list.remove(element)

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


class Grade_Repository:
    def __init__(self):
        self.__list = []


    def repo_add(self, element):
        self.__list.append(element)

    def repo_remove(self, element):
        self.__list.remove(element)

    def get_list(self):
        return self.__list








