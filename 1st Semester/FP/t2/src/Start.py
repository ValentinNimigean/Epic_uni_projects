from src.ui import ui
from src.domain import *
from  src.repository import *
from  src.services import *

repo=repository("input_file.txt")
services=service(repo)
Ui=ui(services)

def run():
    Ui.run()


run()