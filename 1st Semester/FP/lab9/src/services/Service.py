from src.exceptions.Exceptions import ServException
from src.domain.Student import Student
from src.domain.Discipline import Discipline
from src.domain.Grade import Grade
from src.domain.Undo_Redo_execution import Execution
class Services:
    def __init__(self,student_repository, discipline_repository, grade_repository):
        """
        function builds the Services class
        :param student_repository:
        :param discipline_repository:
        :param grade_repository:
        """
        self.__stud_repo= student_repository
        self.__dis_repo = discipline_repository
        self.__grd_repo = grade_repository
        self.__undo=[]
        self.__redo=[]




    def add_student(self,conditions):
        """
        function manages the process of of adding a student to the list
        :param conditions:
        :return:
        """
        id=conditions[0]
        name=' '.join(conditions[1:])
        name=name.strip()
        name=name.replace(' ','_')
        student = Student(id,name)

        self.validate_add_student(student)
        self.already_exists_student(student)
        self.add_std_to_memo(student)
        self.undo_redo_add([Execution(self.__stud_repo.repo_remove, student),Execution(self.__stud_repo.repo_add, student)])

    def add_std_to_memo(self, student):
        """
        function adds the student object to memory
        :param student:
        :return:
        """
        self.__stud_repo.repo_add(student)




    def already_exists_student(self,student):
        """
        function checks by id if the id of the student is already in use
        :param student:
        :return:
        """
        l=self.__stud_repo.get_list()
        id=student.get_id()
        ids=[i.get_id() for  i in l]
        if id in ids:
            raise ServException("Id already exists!")
        return True

    def find_student(self,id):
        """
        function either returns the object with the same id or an exception
        :param id:
        :return:
        """
        l=self.__stud_repo.get_list()

        ids = [i.get_id() for i in l]
        if id in ids:
            poz = ids.index(id)
            return l[poz]
        else:
            raise ServException("ID doesnt exist!")




    def validate_add_student(self,student):
        """
        function checks if the student object is valid
        :param student:
        :return:
        """
        error=""
        if student.get_id().isnumeric()==False:
            error+="Student id should be a positive interger!\n"
        else:
            if student.get_name()=="":
                error+="Invalid Student name\n"

        if error!="":
            raise ServException(error)

    def print_students(self):
        """
        function takes the list of students to the ui so it can be printed
        :return:
        """
        return self.__stud_repo.get_list()

    def remove_student(self,id):
        """
        function manages the process of removing a student from the list
        :param id:
        :return:
        """
        if id[0].isnumeric()==False:
            raise ServException("Id Should be a positive interger!")
        else:
            student= self.find_student(id[0])
            grades=self.remove_student_grades(id[0])
            self.__stud_repo.repo_remove(student)

            self.undo_redo_add([Execution(self.undo_remove_student, student, grades),
                                  Execution(self.redo_remove_student, student)])


    def undo_remove_student(self,student,grades):
        self.__stud_repo.repo_add(student)
        for i in grades:
            self.__grd_repo.repo_add(i)
    def redo_remove_student(self,student):
        self.remove_student_grades(student.get_id())
        self.__stud_repo.repo_remove(student)



    def remove_student_grades(self,id):
        grades=[]
        for i in self.__grd_repo.get_list():
            if i.get_std_id() == id:
                grades.append(i)
                self.__grd_repo.repo_remove(i)
        for i in self.__grd_repo.get_list():
            if i.get_std_id() == id:
                self.__grd_repo.repo_remove(i)
        for i in self.__grd_repo.get_list():
            if i.get_std_id() == id:
                self.__grd_repo.repo_remove(i)
        for i in self.__grd_repo.get_list():
            if i.get_std_id() == id:
                self.__grd_repo.repo_remove(i)

        return grades









    def valid_update_student(self,student):
        """
        function checks if the student i want to update is present in te list
        :param student:
        :return:
        """
        l = self.__stud_repo.get_list()
        id=student.get_id()
        ids = [i.get_id() for i in l]
        if id not in ids:
            raise ServException("ID doesnt exist!")

    def update_student(self,conditions):
        """
        function manages the process of updating a student object from the list
        :param conditions:
        :return:
        """
        id = conditions[0]
        name = ' '.join(conditions[1:])
        name = name.strip()
        name = name.replace(' ', '_')
        student = Student(id, name)
        self.validate_add_student(student)
        self.valid_update_student(student)
        undo_update=self.find_student(id)
        self.update_std_to_mem(student)
        self.undo_redo_add([Execution(self.update_std_to_mem,undo_update),Execution(self.update_std_to_mem,student)])

    def update_std_to_mem(self, student):
        """
        function updates student intro memory
        :param student:
        :return:
        """
        self.__stud_repo.update(student)


    def search_student(self,string):
        """
        function searches students using partial string matching

        :param string:
        :return:
        """
        list=self.__stud_repo.get_list()
        list1=[]
        for i in list:
            if string in i.get_id() or string.lower() in i.get_name().lower():
                list1.append(i)
        return list1


    def add_discipline(self,conditions):
        """
                function manages the process of of adding a discipline to the list
                :param conditions:
                :return:
                """
        id=conditions[0]
        name=' '.join(conditions[1:])
        name=name.strip()
        name=name.replace(' ','_')
        discipline = Discipline(id, name)
        self.validate_add_discipline(discipline)
        self.already_exists_discipline(discipline)
        self.add_dsp_to_memo(discipline)
        self.undo_redo_add([Execution(self.__dis_repo.repo_remove, discipline), Execution(self.__dis_repo.repo_add, discipline)])
    def add_dsp_to_memo(self,discipline):
        """
        function adds discipline to memory
        :param discipline:
        :return:
        """
        self.__dis_repo.repo_add(discipline)
    def validate_add_discipline(self,discipline):
        """
        checks if the discipline i want to add is valid
        :param discipline:
        :return:
        """
        error=""
        if discipline.get_id().isnumeric()==False:
            error+="Discipline id should be a positive interger!\n"
        else:
            if discipline.get_name()== "":
                error+="Invalid Discipline name\n"

        if error!="":
            raise ServException(error)

    def already_exists_discipline(self, discipline):
        """
        checks if the id is taken
        :param discipline:
        :return:
        """
        l = self.__dis_repo.get_list()
        id = discipline.get_id()
        ids = [i.get_id() for i in l]
        if id in ids:
            raise ServException("Id already exists")
        return True

    def remove_discipline(self,id):
        """
        manages the removal of a discipline
        :param id:
        :return:
        """
        if id[0].isnumeric()==False:
            raise ServException("Id Should be a positive interger!")
        else:
            discipline= self.find_discipline(id[0])

            grades=self.remove_discipline_grades(id[0])
            self.__dis_repo.repo_remove(discipline)
            self.undo_redo_add([Execution(self.undo_remove_discipline, discipline, grades),
                                  Execution(self.redo_remove_discipline, discipline)])



    def redo_remove_discipline(self,discipline):
        self.remove_discipline_grades(discipline.get_id())
        self.__dis_repo.repo_remove(discipline)



    def remove_discipline_grades(self,id):
        """
        removes the grades of a discipline
        :param id:
        :return:
        """
        grades=[]
        for i in self.__grd_repo.get_list():
            if i.get_dsp_id() == id:
                grades.append(i)
                self.__grd_repo.repo_remove(i)
        for i in self.__grd_repo.get_list():
            if i.get_dsp_id() == id:
                self.__grd_repo.repo_remove(i)
        for i in self.__grd_repo.get_list():
            if i.get_dsp_id() == id:
                self.__grd_repo.repo_remove(i)
        for i in self.__grd_repo.get_list():
            if i.get_dsp_id() == id:
                self.__grd_repo.repo_remove(i)
        return grades


    def undo_remove_discipline(self,discipline,grades):
        self.__dis_repo.repo_add(discipline)
        for i in grades:
            self.__grd_repo.repo_add(i)
    def find_discipline(self,id):
        """
        returns the discipline with a specific id if it exists
        :param id:
        :return:
        """
        l=self.__dis_repo.get_list()

        ids = [i.get_id() for i in l]
        if id in ids:
            poz = ids.index(id)
            return l[poz]
        else:
            raise ServException("ID doesnt exist!")
    def print_disciplines(self):
        """
        gets the list from the memory
        :return:
        """
        return self.__dis_repo.get_list()

    def valid_update_discipline(self,discipline):
        """
        checks if there is a discipline gthat can be updated
        :param discipline:
        :return:
        """
        l = self.__dis_repo.get_list()
        id=discipline.get_id()
        ids = [i.get_id() for i in l]
        if id not in ids:
            raise ServException("ID doesnt exist!")

    def update_discipline(self,conditions):
        id = conditions[0]
        name = ' '.join(conditions[1:])
        name = name.strip()
        name = name.replace(' ', '_')
        discipline = Discipline(id, name)
        undo_update = self.find_discipline(id)

        self.validate_add_discipline(discipline)
        self.valid_update_discipline(discipline)
        self.update_dsp_to_mem(discipline)
        self.undo_redo_add([Execution(self.update_dsp_to_mem, undo_update), Execution(self.update_dsp_to_mem, discipline)])


    def update_dsp_to_mem(self,discipline):
        self.__dis_repo.update(discipline)

    def search_discipline(self,string):
        """
        function searches for disciplines using partial string search
        :param string:
        :return:
        """
        list=self.__dis_repo.get_list()
        list1=[]
        for i in list:
            if string in i.get_id() or string.lower() in i.get_name().lower():
                list1.append(i)
        return list1




    def valid_grade(self,grd):
        """
        function checks if a grade is valid
        :param grd:
        :return:
        """
        if grd.get_std_id().isnumeric==False or grd.get_dsp_id().isnumeric==False or grd.get_value().isnumeric==False:
            raise ServException("All parameters should be positivve intergers!")
        elif float(grd.get_value())>10:
            raise ServException("Grade value shouldn be higher than 10")
        else:
            list1=self.__stud_repo.get_list()
            list2=self.__dis_repo.get_list()
            list1=[i.get_id() for i in list1]
            list2=[j.get_id() for j in list2]
            if grd.get_std_id() not in list1 or grd.get_dsp_id() not in list2:
                raise ServException("Student or discipline doesn't exist")


    def grade(self,conditions):
        """
        function manages the grade function
        :param conditions:
        :return:
        """
        grd=Grade(conditions[0],conditions[1],conditions[2])
        self.valid_grade(grd)
        self.__grd_repo.repo_add(grd)
        self.undo_redo_add([Execution(self.__grd_repo.repo_remove, grd), Execution(self.__grd_repo.repo_add, grd)])

    def print_grades(self):
        """
        function calls from memory the list of grades
        :return:
        """
        return  self.__grd_repo.get_list()




    def fail_querry_average (self,database):
        """
        function builds a list of failing students
        :param database:
        :return:
        """
        l=[]
        for student in database:
            for discipline in database[student]:
                if sum(database[student][discipline])/len(database[student][discipline])<5.0 and student not in l:
                    l.append(student)
        return l

    def fail_querry(self):
        """
        function builds a list of students that are failing
        :return:
        """
        list=self.__grd_repo.get_list()
        querry={}
        for i in list:
            std=int(i.get_std_id())
            dsp=int(i.get_dsp_id())
            grd=float(i.get_value())
            if std not in querry:
                querry[std]={}
            if dsp not in querry[std]:
                querry[std][dsp]=[]
            querry[std][dsp].append(grd)
        fails=sorted(self.fail_querry_average(querry))
        students=self.__stud_repo.get_list()
        fails1=[]
        for j in fails:
            id = str(j)
            ids = [i.get_id() for i in students]
            poz = ids.index(id)
            fails1.append(students[poz])
        return fails1

    def best_students_average(self,database):
        """
        function builds a dictionary of students with their cumulated average grades
        :param database:
        :return:
        """
        students={}
        for student in database:
            for discipline in database[student]:
                if student not in students:
                    students[student]=0
                lenght=len(database[student])

                students[student] += float(sum(database[student][discipline]) / len(database[student][discipline]))
                students[student]=students[student]/lenght


        return students


    def best_students_querry(self):
        """
        function returns the list of students sorted by their average grades
        :return:
        """
        list=self.__grd_repo.get_list()

        querry={}
        for i in list:
            std=int(i.get_std_id())
            dsp=int(i.get_dsp_id())
            grd=float(i.get_value())
            if std not in querry:
                querry[std]={}
            if dsp not in querry[std]:
                querry[std][dsp]=[]
            querry[std][dsp].append(grd)
        best_students_dic= self.best_students_average(querry)
        best_students_dic=dict(sorted(best_students_dic.items(), key=lambda item: item[1], reverse=True))
        best_students= []
        students=self.__stud_repo.get_list()

        for j in best_students_dic:
            id = str(j)
            ids = [i.get_id() for i in students]
            poz = ids.index(id)
            best_students.append(students[poz])
        return best_students


    def disciplines_querry_average(self,database):
        """
        function returns a dictionary of disciplines and their average grades
        :param database:
        :return:
        """
        grades={}
        for discipline in database:
            if discipline not in grades:
                grades[discipline]=0

            grades[discipline]= float(sum(database[discipline]) / len(database[discipline]))
        return grades


    def disciplines_querry(self):
        """
        function builds the list of disciplines sorted by average grades
        :return:
        """
        list=self.__grd_repo.get_list()
        querry={}
        for i in list:
            dsp = int(i.get_dsp_id())
            grd = float(i.get_value())
            if dsp not in querry:
                querry[dsp] = []
            querry[dsp].append(grd)

        disciplines_dic=self.disciplines_querry_average(querry)
        disciplines_dic= dict(sorted(disciplines_dic.items(), key=lambda item: item[1], reverse=True))
        best_disciplines= []
        disciplines = self.__dis_repo.get_list()
        print(disciplines_dic)
        for j in disciplines_dic:
            id = str(j)
            ids = [i.get_id() for i in disciplines]
            poz = ids.index(id)
            best_disciplines.append(disciplines[poz])
        return best_disciplines

    def undo_redo_add(self,commands: [Execution,Execution]):
        self.__undo.append(commands)
        self.__redo=[]

    def undo(self):
        if len(self.__undo)==0:
            raise ServException("No more undos!")
        else:
            commands=self.__undo.pop()
            self.__redo.append(commands)

            commands[0].do()


    def redo(self):

        if len(self.__redo)==0:
            raise ServException("No more redos!")
        else:

            commands=self.__redo.pop()
            self.__undo.append(commands)
            commands[1].do()


    def clear(self):
        self.__undo=[]
        self.__redo=[]




