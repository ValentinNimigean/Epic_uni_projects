from src.Exceptions.Exceptions import *
from src.Domain.Moves import *
from src.Domain.Moves import *
from src.Repository.Repository import *
from src.Domain.Oponent import *
class services:
    def __init__(self,repository,mills,moves,oponent):

        self.__repository=repository
        self.__mills=mills
        self.__moves=moves
        self.__oponent=oponent
    def get_depth(self):
        """
        returns the  current round
        :return:
        """
        return self.__oponent.get_depth()

    def is_game_over(self):
        """
        checks if the game is over
        :return:
        """
        board=self.__repository.get_board()
        o=0
        x=0
        x_moves=0
        o_moves=0
        for i in range (1,25):
            if board[i]=='X':
                x=x+1
                if self.check_move(i)!=[]:
                    x_moves=x_moves+1

            if board[i]=='O':
                o=o+1
                if self.check_move(i)!=[]:
                    o_moves=o_moves+1
        if x==3 and o>=3:
            return False
        if o==3 and x>=3:
            return False
        if x<3 or o<3:
            return True
        if x_moves==0 or o_moves==0:
            return True
        return False





    def manage_add_piece(self,position):
        """
        adds a piece to the board
        :param position:
        :return:
        """

        if self.__repository.board_check_empty(position) ==False:
            raise RepoException("Position already filled!")
        else:
            self.__repository.board_add(position)


    def manage_remove_piece(self,position):
        """
        removes a piece from the board
        :param position:
        :return:
        """
        if self.__repository.board_check_empty(position) ==True:
            raise RepoException("Position already empty!")
        else:
            self.__repository.board_remove(position)

    def check_move(self,position):
        """
        checks if a move is valid
        :param position:
        :return:
        """
        moves=self.__moves.get_moves()
        possible_moves=[]
        for i in moves[position]:
            if self.__repository.board_check_empty(i) ==True:
                possible_moves.append(i)
        return possible_moves

    def check_mill(self,position):
        """
        checks if a mill is formed
        :param position:
        :return:
        """

        for i in self.__mills.get_mills()[position]:
            if self.__repository.get_board()[i[0]]==self.__repository.get_board()[i[1]] and self.__repository.get_board()[i[0]]==self.__repository.get_board()[position]:
                return True
        return False



                
    def get_board(self):
        """
        returns the board
        :return:
        """
        return  self.__repository.get_board()
    def get_pieces(self):
        """
        returns the pieces
        :return:
        """
        return self.__repository.get_pieces()
    def get_moves(self):
        """
        returns the moves
        :return:
        """
        return self.__moves.get_moves()

    def manage_move_piece(self,position_old,position_new):
        """
        moves a piece
        :param position_old:
        :param position_new:
        :return:
        """
        if self.__repository.board_check_empty(position_new) ==False:
            raise RepoException("Position already filled!")
        else:
            self.__repository.board_update(position_old,position_new)

    def oponent_phase_1(self):
        """
        ai for phase 1
        :return:
        """
        self.__oponent.inc_depth()
        board=self.get_board()
        self.__oponent.minimax_phase1(board,self.__oponent.get_depth(),-10000,10000,False)
        self.__oponent.inc_depth()
        self.__oponent.update_board()
    def oponent_phase_2(self):
        """
        ai for phase 2
        :return:
        """
        self.__oponent.inc_depth()
        board=self.get_board()
        self.__oponent.minimax_phase2(board,0,-10000,10000,False)
        self.__oponent.inc_depth()
        self.__oponent.update_board()

    def count_pieces(self):
        """
        counts the number of pieces
        :return:
        """
        list=self.__repository.get_board()
        number=0
        for i in list:
            if i=='X':
                number=number+1
        return number
    def count_pieces_oponent(self):
        """
        counts the number of oponent's pieces
        :return:
        """
        list=self.__repository.get_board()
        number=0
        for i in list:
            if i=='O':
                number=number+1
        return number

