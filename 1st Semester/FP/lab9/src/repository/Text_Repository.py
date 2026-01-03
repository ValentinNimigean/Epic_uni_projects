from src.domain.Student import *
from src.domain.Discipline import *
from src.domain.Grade import *
from src.repository.Repository import Student_Repository
class Student_Text_Repository:
    def __init__(self,txtfile):
        self.__list=[]
        self.__txtfile=txtfile


    def repo_add(self,student):
        """
        adds student to memory
        :param student:
        :return:
        """
        self.__list.append(student)
        self.save_to_file(self.__txtfile)

    def repo_remove(self,student):
        """
        removes student from memory
        :param student:
        :return:
        """
        self.__list.remove(student)
        self.save_to_file(self.__txtfile)

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
        self.save_to_file(self.__txtfile)
    def save_to_file(self,file):
        list=open(file,"w")
        for i in self.__list:
            id=i.get_id()
            name=i.get_name()
            list.write(str(id)+","+name+'\n')
        list.close()

    def load_from_file(self,file):
        list=open(file,"r")
        for i in list:
            i=i.strip()
            i=i.split(",")
            i[0].strip()
            i[1].strip()
            self.__list.append(Student(i[0],i[1]))
        list.close()


class Discipline_Text_Repository:
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
        list=open(file,"w")
        for i in self.__list:
            id=i.get_id()
            name=i.get_name()
            list.write(str(id)+","+str(name)+'\n')

        list.close()

    def load_from_file(self,file):
        list=open(file,"r")
        for i in list:
            i=i.strip()
            i=i.split(",")
            i[0].strip()
            i[1].strip()
            self.__list.append(Grade(i[0],i[1]))
        list.close()



class Grade_Text_Repository:
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
        list=open(file,"w")
        for i in self.__list:
            id=i.get_std_id()
            discipline=i.get_dsp_id()
            value=i.get_value()
            list.write(str(id)+","+str(discipline)+","+str(value)+'\n')
        list.close()

    def load_from_file(self,file):
        list=open(file,"r")
        for i in list:
            i=i.strip()
            i=i.split(",")
            i[0].strip()
            i[1].strip()
            i[2].strip()
            self.__list.append(Grade(i[0],i[1],i[2]))
        list.close()








