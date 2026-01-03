import  unittest
from  src.exceptions.Exceptions import ServException
from src.services.Service import Services
from src.repository.Repository import *

class Test_Domain(unittest.TestCase):
    def test_student(self):
        """
        tests the student class
        :return:
        """
        student=Student('1',"placeholder")
        self.assertEqual(student.get_id(), '1')
        self.assertEqual(student.get_name(), "placeholder")
    def test_discipline(self):
        """
        tests the discipline class
        :return:
        """
        discipline=Discipline('1',"placeholder")
        self.assertEqual(discipline.get_id(), '1')
        self.assertEqual(discipline.get_name(), "placeholder")

class Test_Services(unittest.TestCase):


    def test_validate_add_student(self):
        """
        tests the validate_add_student function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service= Services(student_repository, discipline_repository, grade_repository)
        student=Student('1',"Placeholder")
        service.validate_add_student(student)
        student=Student('-1',"")
        with self.assertRaises(ServException):
            service.validate_add_student(student)
    

    def test_validate_add_discipline(self):
        """
          tests the validate_add_discipline function
          :return:
          """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        discipline = Discipline('1', "Placeholder")
        service.validate_add_discipline(discipline)
        discipline = Discipline('-1', "")
        with self.assertRaises(ServException):
            service.validate_add_discipline(discipline)

    def test_valid_update_student(self):
        """
        tests the valid_update function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        student = Student('1', "Placeholder")
        with self.assertRaises(ServException):
            service.valid_update_student(student)
        service.add_std_to_memo(student)
        service.valid_update_student(student)
    def test_valid_update_discipline(self):
        """
        tests the valid_update_discipline function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        discipline = Discipline('1', "Placeholder")
        with self.assertRaises(ServException):
            service.valid_update_discipline(discipline)
        service.add_dsp_to_memo(discipline)
        service.valid_update_discipline(discipline)


    def test_already_exists_student(self):
        """
        tests the already_exists_student function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        student = Student('1', "Placeholder")
        self.assertEqual (service.already_exists_student(student),True)
        service.add_std_to_memo(student)
        with self.assertRaises(ServException):
            service.already_exists_student(student)


    def test_already_exists_discipline(self):
        """
         tests the already_exists_discipline function
         :return:
         """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        discipline = Discipline('1', "Placeholder")
        self.assertEqual (service.already_exists_discipline(discipline),True)
        service.add_dsp_to_memo(discipline)
        with self.assertRaises(ServException):
            service.already_exists_discipline(discipline)
    def test_add_student(self):

        """
        tests the add student function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        operators=['-1','']
        with self.assertRaises(ServException):
            service.add_student(operators)


    def test_add_discipline(self):
        """
        tests the add_discipline function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        operators=['-1','']
        with self.assertRaises(ServException):
            service.add_discipline(operators)


    def test_doesnt_exist_student(self):
        """
        tests the doesnt_exist_student function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        student = Student('1', "Placeholder")
        service.add_std_to_memo(student)
        self.assertEqual(service.doesnt_exist_student('1'), student)
        with self.assertRaises(ServException):
            service.doesnt_exist_student('2')
    def test_doesnt_exist_discipline(self):
        """
        tests the doesnt_exist_student function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        discipline = Discipline('1', "Placeholder")
        service.add_dsp_to_memo(discipline)
        self.assertEqual(service.doesnt_exist_discipline('1'), discipline)
        with self.assertRaises(ServException):
            service.doesnt_exist_discipline('2')


    def test_remove_student(self):
        """
        tests the remove
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        id='1'
        with self.assertRaises(ServException):
            service.remove_student(id)

    def test_remove_discipline(self):
        """
        tests the remove_disciplline function
        :return:
        """
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        id='1'
        with self.assertRaises(ServException):
            service.remove_discipline(id)
    def test_print_students(self):
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        student = Student('1', "Placeholder")
        service.add_std_to_memo(student)
        self.assertEqual(service.print_students(),[student])

    def test_print_disciplines(self):
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        grade_repository = Grade_Repository()
        service = Services(student_repository, discipline_repository, grade_repository)
        discipline = Discipline('1', "Placeholder")
        service.add_dsp_to_memo(discipline)
        self.assertEqual(service.print_disciplines(),[discipline])

class Test_Repository(unittest.TestCase):
    def test_add_repo(self):
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        student = Student('1', "Placeholder")
        student_repository.repo_add(student)
        self.assertEqual(student_repository.get_list(), [student])
        discipline = Discipline('1', "Placeholder")
        discipline_repository.repo_add(discipline)
        self.assertEqual(discipline_repository.get_list(), [discipline])


    def test_remove_repo(self):
        student_repository = Student_Repository()
        discipline_repository = Discipline_Repository()
        student = Student('1', "Placeholder")
        student_repository.repo_add(student)
        student_repository.repo_remove(student)
        self.assertEqual(student_repository.get_list(), [])
        discipline = Discipline('1', "Placeholder")
        discipline_repository.repo_add(discipline)
        discipline_repository.repo_remove(discipline)
        self.assertEqual(discipline_repository.get_list(), [])





