class repository:
    def __init__(self):
        self.__board = []

        for i in range(1,26):
            self.__board.append('_')

    def get_board(self):
        """
        returns the board
        :return:
        """
        return self.__board
    def board_remove(self,position):
        """
        removes a piece from the board
        :param position:
        :return:
        """
        self.__board[position] = '_'
    def board_add(self,position):
        """
        adds a piece to the board
        :param position:
        :return:
        """
        self.__board[position] = 'X'



    def board_check_empty(self,position):
        """
        checks if a position is empty
        :param position:
        :return:
        """
        if self.__board[int(position)] == '_':
            return True
        else:
            return False

    def set_board(self,board):
        """
        sets the board
        :param board:
        :return:
        """
        self.__board=board
    def board_update(self,position_old,position_new):
        """
        updates the board
        :param position_old:
        :param position_new:
        :return:
        """
        self.board_remove(position_old)
        self.board_add(position_new)


    def get_pieces(self,player):
        """
        gets the number of pieces of a player
        :param player:
        :return:
        """
        num_i=0
        for i in range(1,25):
            if self.__board[i]==player:
                num_i=num_i+1
        return num_i












