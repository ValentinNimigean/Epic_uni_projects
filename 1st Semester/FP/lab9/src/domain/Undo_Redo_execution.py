class Execution:
    def __init__(self,command, *values):
        self.__command = command
        self.__values= (values)
    def do(self):
        self.__command(*self.__values)
    def get_command(self):
        return self.__command
