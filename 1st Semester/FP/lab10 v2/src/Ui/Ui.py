from src.Exceptions.Exceptions import *

class ui:
    def __init__(self, services):
        self.__service = services
        self.__new_coord=0



    def run(self):
        self.printBoard()
        print("This is the placing phase of the game. You will place your pieces on the board.")
        print("You have 9 pieces to place.")
        k=0

        while k<9:
            try:
                n=0
                n = self.input_coordinate_phase_1()
                self.__service.manage_add_piece(n)
                self.printBoard()


                if self.__service.check_mill(n)==False:
                    k=k+1
                    self.__service.oponent_phase_1()
                    self.printBoard()
            except UiException as e:
                print(e)
            except ServException as e:
                print(e)
            except RepoException as e:
                print(e)
            if self.__service.check_mill(n)==True and n!=0 and self.__service.get_board()[n]=='X' :
                mill = False
                while mill == False:
                    try:

                        if self.__service.check_mill(n) == True:
                            print("You have formed a mill!")
                            print("You can remove a piece from the board.")
                            self.input_mill()
                            self.printBoard()
                            self.__service.oponent_phase_1()
                            self.printBoard()
                            k = k + 1
                            mill = True
                    except ServException as e:
                        print(e)
                    except RepoException as e:
                        print(e)
                    except UiException as e:
                        print(e)

        print("You have finished placing your pieces on the board.")

        self.phase_2()

    def phase_2(self):
        print("This is the moving phase of the game. You will move your pieces on the board.")
        while(self.__service.is_game_over()==False):
            if self.__service.is_game_over()==True:
                print("Game over!")
                return
            m=0
            try:
                n = self.input_coordinate_phase_2()
                m=0
                m=self.move_coordinate_phase_2(n)
                self.__new_coord=m
                self.__service.manage_move_piece(n,m)
                self.printBoard()

                if self.__service.check_mill(m)==False or self.__service.get_board()[m]!='X':
                    m=0

                    self.__service.oponent_phase_2()
                    self.printBoard()


            except UiException as e:
                print(e)
            except ServException as e:
                print(e)
            except RepoException as e:
                print(e)
            if self.__service.check_mill(m)==True and m!=0 and self.__service.get_board()[m]=='X':
                mill = False
                while mill == False:
                    try:

                        if self.__service.check_mill(m) == True and m!=0 and self.__service.get_board()[m]=='X':
                            print("You have formed a mill!")
                            print("You can remove a piece from the board.")
                            self.input_mill()
                            self.printBoard()
                            self.__service.oponent_phase_2()
                            self.printBoard()
                            mill = True
                    except ServException as e:
                        print(e)
                    except RepoException as e:
                        print(e)
                    except UiException as e:
                        print(e)









    def input_mill(self):
        n=input("Write the coordinate of the piece you want to remove:")
        if n.isnumeric()==False:
            raise UiException("position shoiuld be a positive interger!")
        else:
            n=int(n)
            board=self.get_board()
            if n>24 or n<1:
                raise UiException("position should be between 1 and 24!")
            elif board[n]!='O':
                raise UiException("position should be one of your oponent's pieces!")
            else:
                self.__service.manage_remove_piece(n)



    def input_coordinate_phase_1(self):
        n=input("Write the coordinate on wich you want to place a piece (1-24):")
        if n.isnumeric()==False:
            raise UiException("position should be a positive interger!")
        else:
            n=int(n)
            if n>24 or n<1:
                raise UiException("position should be between 1 and 24!")
            else:
                return n

    def input_coordinate_phase_2(self):
        n=input("Write the coordinate of the piece you want to move(1-24):")
        if n.isnumeric()==False:
            raise UiException("position shoiuld be a positive interger!")
        else:
            n=int(n)
            board=self.get_board()
            if n>24 or n<1:
                raise UiException("position should be between 1 and 24!")
            elif board[n]!='X':
                raise UiException("position should be one of your pieces!")
            else:
                return n
    def move_coordinate_phase_2(self,old_position):
        n=input("Write the coordinate on wich you want to move the piece:")
        if n.isnumeric()==False:
            raise UiException("position shoiuld be a positive interger!")
        else:
            n=int(n)
            if self.__service.get_board().count('X')==3:
                print("You are in the final phase of the game. You can move your pieces anywhere on the board.")

            if n>24 or n<1:
                raise UiException("position should be between 1 and 24!")
            elif self.__service.get_board()[n]!='_':
                raise ServException("position should be empty!")
            else:
                if self.__service.get_board().count('X')==3:
                    return n
                else:
                    moves = self.__service.get_moves()
                    possible_moves = moves[old_position]
                    if n not in possible_moves and self.__service.get_board().count('X') > 3:
                        raise ServException("position should be one of the possible moves!")
                    else:
                        return n





    def get_board(self):
        return self.__service.get_board()
    def printBoard(self):
        board=self.get_board()
        print(" ")
        print(" ")
        print(" ")
        print(" ")
        print(" ")
        print(" ")
        print(" ")
        print("01(",board[1], ")----------------------------02(",board[2], ")-------------------------------03(", board[3], ")")
        print("|                                  |                                     |      ")
        print("|                                  |                                     |      ")
        print("|           04(",board[4], ")----------------05(", board[5], ")-------------------06(", board[6], ")     |")
        print("|           |                      |                         |           |")
        print("|           |                      |                         |           |")
        print("|           |            07(", board[7], ")---08(", board[8], ")---09(", board[9], ")         |           |")
        print("|           |            |                   |               |           |")
        print("|           |            |                   |               |           |")
        print("10(",board[10], ")-----11(", board[11], ")------12(", board[12], ")             13(",board[13], ")---------14(", board[14], ")-----15(",board[15], ")")
        print("|           |            |                   |               |           |")
        print("|           |            |                   |               |           |")
        print("|           |            16(",board[16], ")---17(", board[17], ")---18(", board[18], ")         |           |")
        print("|           |                      |                         |           |")
        print("|           |                      |                         |           |")
        print("|           19(", board[19], ")----------------20(",board[20], ")-------------------21(", board[21], ")     |")
        print("|                                  |                                     |      ")
        print("|                                  |                                     |      ")
        print("22(", board[22], ")----------------------------23(",board[23], ")-------------------------------24(",board[24], ")")
