class Discipline:
    def __init__(self,discipline_id,discipline_name):
        """
        function builds the Discipline class
        :param discipline_id:
        :param discipline_name:
        """
        self.__discipline_id=discipline_id
        self.__discipline_name=discipline_name


    def __str__(self):
        """
        function builds the string from the Discipline class
        :return:
        """
        name=self.__discipline_name.replace('_',' ')
        return "Name:"+ name +" ID:"+self.__discipline_id


    def get_id(self):
        """

        :return:
        """
        return self.__discipline_id

    def get_name(self):
        """

        :return:
        """
        return self.__discipline_name

    def set_id(self,value):
        """

        :param value:
        :return:
        """
        self.__discipline_id=value

    def set_name(self,value):
        """
        :param value:
        :return:
        """

        self.__discipline_name=value





