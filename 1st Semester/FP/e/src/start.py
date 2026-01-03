from src.Repository import Repository
from src.Controller import Controller
from src.Ui import Ui
repo=Repository()
cont=Controller(repo)
ui=Ui(cont)

ui.run()

