from domain.domain import Complex
import  xml.etree.ElementTree as xml
import random
import os
class Xml_repository:


    def __init__(self):
        """
        function builds the Xml_repository class
        """
        self.__list=[]
        self.__stack=[]
        check_file = os.stat("Xml_numbers.xml").st_size
        if check_file==0:
            for i in range(0, 10):
                real = str(random.randint(-100, 100))
                imaginary = str(random.randint(-100, 100))
                complex_number = Complex(real, imaginary)
                self.__list.append(complex_number)
        else:
            self.__list=self.load_list_file("Xml_numbers.xml")
        self.save_list_file("Xml_numbers.xml")
        self.__stack.append(self.__list.copy())



    def load_list_file(self,xmlfile):
        """
        function loads the list of numbers from the XML file
        :param xmlfile:
        :return:
        """
        list1=[]
        tree=xml.parse(xmlfile)
        root=tree.getroot()
        try:
            for number in root.findall("Complex"):
                real = str(number.find("real").text)
                imaginary = str(number.find("imaginary").text)
                list1.append(Complex(real, imaginary))
        except Exception :
            print("List is empty!")

        return list1

    def save_list_file(self,xmlfile):
        """
        function puts the list of numbers into the XML file
        :param xmlfile:
        :return:
        """
        numbers=open(xmlfile,'w')
        pass
        numbers.close()
        root=xml.Element("Complex")
        for i in self.__list.copy():
            number=xml.SubElement(root,"Complex")
            real=xml.SubElement(number,"real")
            real.text=str(i.get_real())
            imaginary = xml.SubElement(number, "imaginary")
            imaginary.text = str(i.get_imaginary())
            tree=xml.ElementTree(root)
            tree.write(xmlfile)


    def add_to_repository(self,complex_number:Complex):
        """
        function adds a number to the repository
        :param complex_number:
        :return:
        """
        self.__list.append(complex_number)
        self.__stack.append(self.__list.copy())
        self.save_list_file("Xml_numbers.xml")
    def filter_from_repository(self,start,end):
        """
        function filters the numbers from start to end
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
        self.save_list_file("Xml_numbers.xml")

    def get_stack(self):
        """
        function returns the stack
        """
        return self.__stack
    def get_list(self):
        """
        function returns the list
        :return:
        """

        return self.load_list_file("Xml_numbers.xml")

    def undo(self):
        """
        function undoes the last step
        """
        self.__stack.pop()
        self.__list=self.__stack[len(self.__stack)-1].copy()
        self.save_list_file("Xml_numbers.xml")






