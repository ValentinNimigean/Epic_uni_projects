class Student:
    def __init__(self,student_id,student_name):
        self.__student_id=student_id
        self.__student_name=student_name


    def __str__(self):
        name=self.__student_name.replace('_',' ')
        return "Name:"+ name +" ID:"+self.__student_id


    def get_id(self):
        return self.__student_id

    def get_name(self):
        return self.__student_name

    def set_id(self,value):
        self.__student_id=value

    def set_name(self,value):
        self.__student_name=value





