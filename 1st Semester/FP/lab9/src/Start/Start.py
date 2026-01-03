import random
import  configparser
from src.services.Service import *
from src.repository.Repository import *
from src.repository.Text_Repository import *
from src.repository.Binary_Repository import *
from src.ui.Ui import Ui
import os

def menu():
    ui.run()


config=configparser.ConfigParser()
settings_text="[Settings]\n"+open('settings.properties').read()
config.read_string(settings_text)
repository_setting=config.get('Settings','repository')
students_file=config.get('Settings','students')
disciplines_file=config.get('Settings','disciplines')
grades_file=config.get('Settings','grades')
path="C:\\Users\\valen\\Documents\\GitHub\\a9-915-Nimigean-Valentin\\src\\Files\\"


repository_setting=repository_setting.strip()
if repository_setting=='"text"':
    print("Using Text file repository")
    students_file=students_file.replace('"',' ')
    disciplines_file=disciplines_file.replace('"',' ')
    grades_file=grades_file.replace('"',' ')
    students_file=students_file.strip()
    disciplines_file=disciplines_file.strip()
    grades_file=grades_file.strip()
    students_file=path+students_file
    disciplines_file=path+disciplines_file
    grades_file=path+grades_file
    student_repository=Student_Text_Repository(students_file)
    discipline_repository=Discipline_Text_Repository(disciplines_file)
    grade_repository=Grade_Text_Repository(grades_file)

elif repository_setting=='"binary"':
    print("Using Binary file repository")
    students_file=students_file.replace('"',' ')
    disciplines_file=disciplines_file.replace('"',' ')
    grades_file=grades_file.replace('"',' ')
    students_file=students_file.strip()
    disciplines_file=disciplines_file.strip()
    grades_file=grades_file.strip()
    students_file=path+students_file
    disciplines_file=path+disciplines_file
    grades_file=path+grades_file
    student_repository=Student_Binary_Repository(students_file)
    discipline_repository=Discipline_Binary_Repository(disciplines_file)
    grade_repository=Grade_Binary_Repository(grades_file)

elif repository_setting=='"inmemory"':
    print("Using inmemory repository")
    student_repository=Student_Repository()
    discipline_repository=Discipline_Repository()
    grade_repository=Grade_Repository()
else:
    print("Invalid repository setting")
    print("Using inmemory repository")
    student_repository=Student_Repository()
    discipline_repository=Discipline_Repository()
    grade_repository=Grade_Repository()



services=Services(student_repository,discipline_repository,grade_repository)

ui=Ui(services)


disciplines = ["Mathematics", "English", "Science", "History", "Geography",
                     "Physical Education", "Computer Science", "Art", "Music",
                     "Foreign Language", "Edging", "Social Studies", "Physics",
                     "Chemistry", "Biology", "Economics", "Psychology", "Sociology",
                     "Health Education", "Political Science"]
for i in range (1,21):
    l=[]
    l.append(str(i))
    l.append(disciplines[i-1])
    services.add_discipline(l)

names = ["Emily Johnson", "Liam Smith", "Olivia Brown", "Noah Davis", "Ava Taylor",
              "Sophia Miller", "Jackson Wilson", "Isabella Anderson", "Lucas Martinez",
              "Mia Jackson", "Aiden Harris", "Evelyn Thompson", "Elijah Turner",
              "Abigail White", "Caden Moore", "Charlotte Hill", "Mason Parker",
              "Amelia Wright", "Oliver Cooper", "Harper King"]

for i in range (1,21):
    l=[]
    l.append(str(i))
    l.append(names[i-1])
    services.add_student(l)


for i in range (1, 60):
    l=[]
    stud_id=random.randint(1,20)
    dis_id=random.randint(1,20)
    grd=random.randint(4,10)
    l.append(str(stud_id))
    l.append(str(dis_id))
    l.append(str(grd))
    services.grade(l)

menu()