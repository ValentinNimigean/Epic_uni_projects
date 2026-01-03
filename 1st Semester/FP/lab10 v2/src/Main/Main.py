from src.Ui.Ui import *
from src.Services.Services import *
from src.Repository.Repository import *
from src.Domain.Moves import *
from src.Domain.Oponent import *
from src.Ui.PyGame_Ui import *
import configparser
repository=repository()
millls=mills()
moves=moves()
oponent=oponent(repository,millls,moves)
services=services(repository,millls,moves,oponent)
config=configparser.ConfigParser(   )
config.read("settings.properties")
ui_setting=config.get('Config', 'ui_type')
if ui_setting== 'Console':
    print("Using Console UI")
    ui=ui(services)
elif ui_setting=='Pygame':
    print("Using Pygame UI")
    ui=PygameUI(services)
else:
    print("Invalid type. Using Pygame UI")
    ui=PygameUI(services)

ui.run()