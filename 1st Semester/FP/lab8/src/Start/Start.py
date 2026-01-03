import random

from src.services.Service import Services
from src.repository.Repository import Student_Repository
from src.repository.Repository import Discipline_Repository
from src.repository.Repository import Grade_Repository
from src.ui.Ui import Ui
def menu():
    ui.run()

student_repository=Student_Repository()
discipline_repository=Discipline_Repository()
grade_repository = Grade_Repository()

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