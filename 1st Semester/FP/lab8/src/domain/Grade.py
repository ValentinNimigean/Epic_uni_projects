class Grade:
    def __init__(self,student_id,discipline_id,value):
        self.__student_id=student_id
        self.__discipline_id=discipline_id
        self.__value=value


    def __str__(self):
        return "Student id: "+self.__student_id+"  Discipline id: "+self.__discipline_id+" Value: "+self.__value

    def get_std_id(self):
        return self.__student_id
    def get_dsp_id(self):
        return self.__discipline_id

    def get_value(self):
        return self.__value
    def set_value(self,value):
        self.__value=str(value)





