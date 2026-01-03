from domain.domain import  Complex
class Service:
    def __init__(self,repository):
        """
        function creates the Service class
        :param repository:
        """
        self.__repository=repository

    def add_number(self,real,imaginary):
        """
        The function builds the complex number and adds it to the repository
        :param real: real part of the complex number
        :param imaginary: imaginary part of the complex number
        :return:
        """
        number=Complex(real,imaginary)
        self.__repository.add_to_repository(number)

    def add_repository_test(self):
        """
        tests the "add" functionality when it comes to the repository class
        :return:
        """
        l1=len(self.__repository.get_list())
        number=Complex("0","0")
        self.__repository.add_to_repository(number)
        assert len(self.__repository.get_list())==l1+1


    def add_services_test(self,real,imaginary):
        """
        tests the "add" functionality when it comes to the services class
        :param real: real part of the complex number
        :param imaginary: imaginary part of the complex number
        :return:
        """
        number=Complex(real,imaginary)
        assert number.get_real()==real
        assert number.get_imaginary()==imaginary


    def filter_number(self,start,end):
        """
        the function filters out of the repository the numbers found between the points "start" and "end"
        :param start: the strating point of the sequence that i want to filter out
        :param end: the ending point of the sequence that i want to filter out
        :return:
        """
        self.__repository.filter_from_repository(start, end)
    def display_list_service(self):
        """
        gets the list of numbers
        :return:
        """
        return self.__repository.get_list()
    def stack_lenght(self):
        """
        gets the stack
        :return:
        """
        return self.__repository.get_stack()
    def undo(self):
        """
        the function asks the repository to undo the last step
        :return:
        """
        self.__repository.undo()


