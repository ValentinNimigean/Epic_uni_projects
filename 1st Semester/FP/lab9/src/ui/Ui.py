from  src.exceptions.Exceptions import *
class Ui:
    def __init__(self, services):
        self.__service = services

        self.__commands = {
            "add_student": self.ui_add_student,
            "print_students": self.ui_print_students,
            "remove_student":self.ui_remove_student,
            "update_student":self.ui_update_student,
            "add_discipline": self.ui_add_discipline,
            "print_disciplines": self.ui_print_disciplines,
            "remove_discipline": self.ui_remove_discipline,
            "update_discipline": self.ui_update_discipline,
            "search":self.ui_search,
            "grade":self.ui_grade,
            "print_grades":self.ui_print_grades,
            "failing_students":self.ui_failing_querry,
            "best_students":self.ui_best_students_querry,
            "disciplines_querry":self.ui_disciplines_querry,
            "undo":self.ui_undo,
            "redo":self.ui_redo

        }

    def ui_print_functions(self):
        print("choose one of the following functions:")
        print("<add_student/add_discipline> <id> <name>")
        print("<remove_student/remove_discipline> <id>")
        print("<print_students/print_disciplines>")
        print("<update_student/update_discipline> <id> <new_name>")
        print("<grade> <student_id> <discipline_id> <value")
        print("<print_grades>")
        print("<search> <string>")
        print("<failing_students>")
        print("<best_students>")
        print("<disciplines_querry>")

    def ui_redo(self,conditions):
        if conditions!=[]:
            raise UiException("Too many arguments!")
        else:
            self.__service.redo()
            print("Redo succesful!")
    def ui_undo(self,conditions):
        """
        function proceses the undo command
        :param conditions:
        :return:
        """
        if conditions!=[]:
            raise UiException("Too many arguments!")
        else:
            self.__service.undo()
            print("Undo succesful!")
    def ui_add_student(self,conditions):
        if len(conditions)<2:
            raise UiException("Not enough parameters!")
        else:
            self.__service.add_student(conditions)
            print("Student added succesfully!")

    def ui_remove_student(self,id):
        if id==[]:
            raise  UiException("Not enough arguments")
        elif len(id)>1:
            raise UiException("Too many arguments!")
        else:
            self.__service.remove_student(id)
            print("Student removed succesfully!")
    def ui_update_student(self,conditions):
        if len(conditions)<2:
            raise UiException("Not enough parameters!")
        else:
            self.__service.update_student(conditions)
            print("Student updated succesfully!")


    def ui_print_students(self,conditions):
        if conditions!=[]:
            raise UiException("Print command shouldnt have parameters!")
        list=self.__service.print_students()
        for i in range(0,len(list)):
            print(str(list[i]))










    def ui_add_discipline(self, conditions):
        if len(conditions)<2:
            raise UiException("Not enough parameters!")
        else:
            self.__service.add_discipline(conditions)
            print("Discipline added succesfully!")

    def ui_remove_discipline(self,id):
        if id==[]:
            raise  UiException("Not enough arguments")
        elif len(id)>1:
            raise UiException("Too many arguments!")
        else:
            self.__service.remove_discipline(id)
            print("Discipline removed succesfully!")



    def ui_update_discipline(self, conditions):
        """
        function proceses the update command
        :param conditions:
        :return:
        """
        if len(conditions)<2:
            raise UiException("Not enough parameters!")
        else:
            self.__service.update_discipline(conditions)
            print("Discipline updated succesfully!")

    def ui_print_disciplines(self,conditions):
        """
        function proceses the print command
        :param conditions:
        :return:
        """
        if conditions!=[]:
            raise UiException("Print command shouldnt have parameters!")
        list=self.__service.print_disciplines()
        for i in range(0,len(list)):
            print(str(list[i]))


    def ui_search(self,conditions):
        """
        function proceses the search command
        :param conditions:
        :return:
        """
        if len(conditions)!=1:
            raise UiException("There should only be one thing to search for!")

        else:
            print("Students:")
            list = self.__service.search_student(conditions[0])
            if list==[]:
                print("nothing to show!")
            else:
                for i in list:
                    print(str(i))
            print("Disciplines:")
            list = self.__service.search_discipline(conditions[0])
            if list == []:
                print("nothing to show!")
            else:
                for i in list:
                    print(str(i))




    def ui_grade(self,conditions):
        """
        function proceses the grade command
        :param conditions:
        :return:
        """
        if len(conditions)!=3:
            raise UiException("Too few/many arguments")
        else:
            self.__service.grade(conditions)
            print("Graded succesfully!")

    def ui_print_grades(self,conditions):
        """
        function proceses the print grades command
        :param conditions:
        :return:
        """
        if conditions!=[]:
            raise UiException("Print command shouldnt have parameters!")
        list=self.__service.print_grades()
        for i in range(0,len(list)):
            print(str(list[i]))



    def ui_failing_querry(self,conditions):
        """
        function proceses the failing students command
        :param conditions:
        :return:
        """
        if conditions!=[]:
            raise UiException("Too many arguments!")
        else:
            fails=self.__service.fail_querry()
            for i in fails:
                print(str(i))

    def ui_best_students_querry(self,conditions):
        """
        function proceses the best_students command
        :param conditions:
        :return:
        """
        if conditions!=[]:
            raise UiException("Too many arguments!")
        else:
            students=self.__service.best_students_querry()
            for i in students:
                print(str(i))
    def ui_disciplines_querry(self,conditions):
        """
        function proceses the disciplines querry command
        :param conditions:
        :return:
        """
        if conditions!=[]:
            raise UiException("Too many arguments!")
        else:
            disciplines=self.__service.disciplines_querry()
            for i in disciplines:
                print(str(i))
    def clear(self):
        self.__service.clear()



    def run(self):
        """
        function boots up the ui module
        :return:
        """
        self.clear()
        self.ui_print_functions()
        while True:
            command = input(">>>")
            command = command.strip()
            if command == "":
                continue
            if command == "exit":
                print("byeee :3")
                return

            parts = command.split()
            command_name = parts[0]
            params = parts[1:]
            if command_name in self.__commands:
                try:
                    self.__commands[command_name](params)
                except ServException as se:
                    print(f"Service error:{se}")
                except UiException as ue:
                    print(f"Ui error:{ue}")
            else:
                print("invalid command!")