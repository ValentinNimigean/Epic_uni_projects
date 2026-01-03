class Complex:
    def __init__(self,real,imaginary):
        self.__real=real
        self.__imaginary=imaginary
    def get_real(self):
        """
        function gets the real part of the complex number
        :return:
        """
        return self.__real
    def get_imaginary(self):
        """
        function gets the imaginary part of the complex number
        :return:
        """
        return self.__imaginary
    def __str__(self):
        """
        function represents the complex numbers as strings
        :return:
        """
        if self.__imaginary.isnumeric()==False:
            return self.__real + self.__imaginary+'i'
        else:
            return self.__real + "+" + self.__imaginary + 'i'




