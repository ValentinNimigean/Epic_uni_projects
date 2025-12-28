from src.Domain.Moves import *
class oponent:
    def __init__(self,repository,mills,moves):
        self.__repo=repository
        self.__mills=mills
        self.__moves=moves
        self.__depth=0
        self.__countermoove=[]
        self.__board=self.__repo.get_board()
    def get_depth(self):
        """
        function that returns the depth
        :return:
        """
        return self.__depth
    def inc_depth(self):
        """
        function that increments the depth
        :return:
        """
        self.__depth=self.__depth+1

    def update_board(self):
        """
        function that updates the board
        :return:
        """
        self.__repo.set_board(self.__countermoove)
    def is_mill_1(self,board,position):
        """
        function that checks if a mill is formed
        :param board:
        :param position:
        :return:
        """
        mills=self.__mills.get_mills()
        if board[position]=='X':
            for j in mills[position]:
                if board[j[0]]=='X' and board[j[1]]=='X':
                    return True
        return False

    def is_mill_2(self,board,position):
        """
        function that checks if a mill is formed
        :param board:
        :param position:
        :return:
        """
        mills=self.__mills.get_mills()
        if board[position]=='O':
            for j in mills[position]:
                if board[j[0]]=='O' and board[j[1]]=='O':
                    return True
        return False
    def might_be_mill_1(self,board,position):
        """
        function that checks if a mill has the potential to be formed starting from position
        :param board:
        :param position:
        :return:
        """
        mills=self.__mills.get_mills()

        if board[position]=='X':
            for j in mills[position]:
                if board[j[0]]=='_' and board[j[1]]=='_':
                    return True
                if board[j[0]]=='X' and board[j[1]]=='_':
                    return True
                if board[j[0]]=='_' and board[j[1]]=='X':
                    return True
        return False
    def might_be_mill_2(self,board,position):
        """
        function that checks if a mill has the potential to be formed starting from position
        :param board:
        :param position:
        :return:
        """
        mills=self.__mills.get_mills()

        if board[position]=='O':
            for j in mills[position]:
                if board[j[0]]=='_' and board[j[1]]=='_':
                    return True
                if board[j[0]]=='O' and board[j[1]]=='_':
                    return True
                if board[j[0]]=='_' and board[j[1]]=='O':
                    return True
        return False

    def count_mills_1(self,board):
        """
        function that counts the number of mills that can be formed starting from position
        :param board:
        :return:
        """
        counter=0
        for i in range(1,25):
            if board[i]=='X':
                if self.is_mill_1(board,i):
                    counter=counter+11
                elif self.might_be_mill_1(board,i):
                    counter=counter+10
        return counter


    def count_mills_2(self,board):
        """
        function that counts the number of mills that can be formed starting from position
        :param board:
        :return:
        """
        counter=0
        for i in range(1,25):
            if board[i]=='O':
                if self.is_mill_2(board,i):
                    counter=counter-11
                elif self.might_be_mill_2(board,i):
                    counter=counter-10
        return counter

    def minimax_phase1(self,board,depth,alpha,beta,maximizingPlayer):
        """
        function that implements the min_max algorithm
        :param board:
        :param depth:
        :return:
        """
        if depth==self.__depth+2:

            return self.count_mills_1(board)+self.count_mills_2(board)

        if maximizingPlayer:
            minValue=-10000
            children=self.make_placement_1(board)

            for child in children:
                actual_value=minValue
                value=self.minimax_phase1(child,depth+1,alpha,beta,False)
                minValue=max(minValue,value)
                if minValue>actual_value and depth==self.__depth:
                        self.__countermoove=child

                alpha=max(alpha,minValue)
                if beta<=alpha:
                    break
            return minValue
        else:
            maxValue=10000
            children=self.make_placement_2(board)

            for child in children:
                actual_value=maxValue
                value=self.minimax_phase1(child,depth+1,alpha,beta,True)
                maxValue=min(maxValue,value)
                if maxValue<actual_value and depth==self.__depth:
                        self.__countermoove=child
                beta=min(beta,maxValue)
                if beta<=alpha:
                    break
            return maxValue
    def minimax_phase2(self,board,depth,alpha,beta,maximizingPlayer):
        """
        function that implements the min_max algorithm
        :param board:
        :param depth:
        :return:
        """
        if depth==4:
            return self.count_mills_1(board)+self.count_mills_2(board)


        if maximizingPlayer:

            minValue=-10000
            children=self.make_move_1(board)
            for child in children:
                actual_value=minValue
                value=self.minimax_phase2(child,depth+1,alpha,beta,False)
                minValue=max(minValue,value)
                if minValue>actual_value and depth==0:
                        self.__countermoove=child

                alpha=max(alpha,minValue)
                if beta<=alpha:
                    break
            return minValue
        else:
            maxValue=10000
            children=self.make_move_2(board)
            for child in children:
                actual_value=maxValue
                value=self.minimax_phase2(child,depth+1,alpha,beta,True)
                maxValue=min(maxValue,value)
                if maxValue<actual_value and depth==0:
                        self.__countermoove=child
                beta=min(beta,maxValue)
                if beta<=alpha:
                    break
            return maxValue







    def make_placement_1(self,board):
        """
        function that makes a hypotethical placement
        :param board:
        :return:
        """
        children=[]
        for position in range(1,25):
            if board[position]=='_':
                board_copy=board.copy()
                board_copy[position]='X'
                if self.is_mill_1(board_copy,position):
                    if self.is_mill_1(board_copy,position):
                        children=children+self.make_removal_1(board_copy)

                else:
                    children.append(board_copy)
        return children

    def make_removal_1(self,board):
        """
        function that makes a hypotethical removal
        :param board:
        :return:
        """
        children=[]
        for position in range(1,25):
            if board[position]=='O':
                board_copy=board.copy()
                board_copy[position]='_'
                children.append(board_copy)
        return children

    def make_placement_2(self,board):
        """
        function that makes a hypotethical placement
        :param board:
        :return:
        """
        children=[]
        for position in range(1,25):
            if board[position]=='_':
                board_copy=board.copy()
                board_copy[position]='O'
                if self.is_mill_2(board_copy,position):
                    if self.is_mill_2(board_copy,position):
                        children=children+self.make_removal_2(board_copy)

                else:
                    children.append(board_copy)
        return children
    def make_removal_2(self,board):
        """
        function that makes a hypotethical removal
        :param board:
        :return:
        """
        children=[]
        for position in range(1,25):
            if board[position]=='X':
                board_copy=board.copy()
                board_copy[position]='_'
                children.append(board_copy)
        return children
    def make_move_1(self,board):
        """
        function that makes a hypotethical move
        :param board:
        :return:
        """
        children=[]
        for position in range(1,25):
            if board[position]=='X':
                if self.__repo.get_pieces('X')==3:
                    for move in range(1,25):
                        if board[move]=='_':
                            board_copy=board.copy()
                            board_copy[position]='_'
                            board_copy[move]='X'
                            if self.is_mill_1(board_copy,move):
                                children=children+self.make_removal_1(board_copy)
                            else:
                                children.append(board_copy)
                else:
                    for move in self.__moves.get_moves()[position]:
                        if board[move]=='_':
                            board_copy=board.copy()
                            board_copy[position]='_'
                            board_copy[move]='X'
                            if self.is_mill_1(board_copy,move):
                                children=children+self.make_removal_1(board_copy)
                            else:
                                children.append(board_copy)
        return children
    def make_move_2(self,board):
        """
        function that makes a hypotethical move
        :param board:
        :return:
        """
        children=[]
        for position in range(1,25):
            if board[position]=='O':
                if self.__repo.get_pieces('O')==3:
                    for move in range(1,25):
                        if board[move]=='_':
                            board_copy=board.copy()
                            board_copy[position]='_'
                            board_copy[move]='O'
                            if self.is_mill_2(board_copy,move):
                                children=children+self.make_removal_2(board_copy)
                            else:
                                children.append(board_copy)
                else:
                    for move in self.__moves.get_moves()[position]:
                        if board[move]=='_':
                            board_copy=board.copy()
                            board_copy[position]='_'
                            board_copy[move]='O'
                            if self.is_mill_2(board_copy,move):
                                children=children+self.make_removal_2(board_copy)
                            else:
                                children.append(board_copy)
        return children
    def get_board(self):
        """
        function that returns the board
        :return:
        """
        return self.__board
