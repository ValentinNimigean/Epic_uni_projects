class UiException(Exception):

    def __init__(self, exc):
        """
        builds the ui exception class
        :param exc:
        """
        Exception.__init__(self)
        self.__exc = exc

    def __str__(self):
        return ''.join(self.__exc)

class ServException(Exception):


    def __init__(self, exc):
        """
        builds the service exception class
        """
        Exception.__init__(self)
        self.__exc = exc

    def __str__(self):
        return ''.join(self.__exc)

