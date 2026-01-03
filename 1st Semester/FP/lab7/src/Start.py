from ui.ui import UI
from services.services import Service
from repository.repository_binary import Binary_repository
from repository.repository_xml import Xml_repository
from repository.repository_memory import Memory_repository
from repository.repository_file import File_repository
import configparser
def menu():
    """
    starts the program
    :return:
    """
    ui.commands()


config=configparser.ConfigParser(   )
config.read("settings.properties")
repository_setting=config.get('Config','repository_type')
if repository_setting=='text':
    print("Using Text file repository")
    repository1=File_repository()
elif repository_setting=='memory':
    print("Using Memory repository")
    repository1=Memory_repository()
elif repository_setting=='binary':
    print("Using Binary repository")
    repository1=Binary_repository()
elif repository_setting=='xml':
    print("Using XML repository")
    repository1=Xml_repository()
else:
    print("Invalid type. Using Memory repository")
    repository1=Memory_repository()

service=Service(repository1)
ui=UI(service)
menu()
