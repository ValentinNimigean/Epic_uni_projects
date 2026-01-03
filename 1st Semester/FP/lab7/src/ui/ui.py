class UI:
    def __init__(self,service):
        """
        the function creates the class UI
        :param service:
        """
        self.__service=service

    def commands(self):
        """
        the function inputs commands and sends them to the services repository
        :return:
        """
        self.__service.add_repository_test()
        self.__service.add_services_test("0","0")
        print("tests done succesfuly!")
        self.__service.undo()
        print("\n")
        print("Choose one of the following commands:")
        print("add a number - format is <add> <complex number(a+bi)>")
        print("filter out the elements of the list from 'start' to 'end' - format is <filter> <start-pos. interger> <end-pos interger>")
        print("display the list - format is <display>")
        print("undo the previous action - format is <undo>")
        print("close the program - format is <exit>")
        while True:
            try:
                command_str = input(">>>")
                command_str=command_str.strip()
                command=command_str.split(" ")

                if command[0] == "add":

                    if len(command)==2:
                        real = 0
                        imaginary = 0

                        sign_1=command[1].count('+')
                        sign_2=command[1].count('-')
                        command[1]=command[1].replace('+',' ')
                        command[1] = command[1].replace('-', ' ')
                        imaginary_ok=command[1].count(('i'))
                        command[1] = command[1].replace('i', ' ')
                        command[1]=command[1].strip()
                        number=command[1].split(" ")
                        if len(number)==1:
                            number=command[1]

                            if imaginary_ok==1:
                                if number.isnumeric():
                                    if sign_1==0 and sign_2==0:
                                        imaginary=number
                                    elif sign_2==1:
                                        imaginary='-'+number
                                    elif sign_2+sign_1>1:
                                        raise Exception("Invalid structure!")
                                else:
                                    raise Exception("The imaginary value should be an interger!")
                            elif imaginary_ok==0:
                                if number.isnumeric():
                                    if sign_1==0 and sign_2==0:
                                        real=number
                                    elif sign_2==1:
                                        real='-'+number
                                    elif sign_2+sign_1>1:
                                        raise Exception("Invalid structure!")
                                else:
                                    raise Exception("The real value should be an interger!")
                            else:
                                raise Exception("Too many imaginary values!")
                        elif len(number)==2:
                            if imaginary_ok==0:
                                raise Exception("No valid imaginary value!")
                            else:
                                if number[0].isnumeric():
                                    if number[1].isnumeric():
                                        if sign_1==1 and sign_2==1:
                                            real='-'+number[0]
                                            imaginary=number[1]
                                        elif sign_1==0 and sign_2==1:
                                            real=number[0]
                                            imaginary='-'+number[1]
                                        elif sign_1==1 and sign_2==0:
                                            real=number[0]
                                            imaginary=number[1]
                                        elif sign_1==0 and sign_2==2:
                                            real='-'+number[0]
                                            imaginary='-'+number[1]
                                        else:
                                            raise Exception("Invalid complex number structure!")




                                    else:
                                        raise Exception("The imaginary value should be an interger!")
                                else:
                                    raise Exception("The real value should be an interger!")
                    else:
                        raise Exception("Too many/few arguments")
                    real=str(real)
                    imaginary=str(imaginary)
                    self.__service.add_number(real,imaginary)
                    print("Number added succesfully!")



                elif command[0] == "filter":
                    if len(command) == 3:
                        if command[1].isnumeric():
                            if int(command[1]) > 0:
                                start = int(command[1])
                            else:
                                raise Exception("The start statement should be a positive interger!")
                        else:
                            raise Exception("The start statement should be a positive interger!")
                        if command[2].isnumeric():
                            if int(command[2]) > 0:
                                end = int(command[2])
                            else:
                                raise Exception("The end statement should be a positive interger!")
                        else:
                            raise Exception("The end statement should be a positive interger!")
                        if start > end:
                            aux = start
                            start = end
                            end = aux
                        if start>len(self.__service.display_list_service()):
                            raise Exception("The values are out of bounds!")
                        self.__service.filter_number(start, end)
                        print("List filtered succesfuly!")


                    else:
                        raise Exception("Invalid command structure!")
                elif command[0]=="display":
                    if len(command)==1:
                        self.display_list()

                    else:
                        raise Exception("Invalid command structure!")
                elif command[0]=="undo":
                    if len(command)==1:
                        if len(self.__service.stack_lenght())==1:
                            raise Exception("No previous steps!")
                        else:
                            self.__service.undo()
                            print("Undone Succesfully!")
                    else:
                        raise Exception("Invalid command structure!")
                elif command[0]=="exit":
                    return ()

                else:
                    raise Exception("Invalid Command")
            except Exception as ex:
                print(ex)

    def display_list(self):
        """
        the function prints the list of numbers
        :return:
        """
        if self.__service.display_list_service()==[]:
            raise Exception("Empty list!")
        else:
            for i in self.__service.display_list_service():
                print(str(i))
