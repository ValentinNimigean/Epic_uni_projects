import pygame

pygame.init()
class PygameUI:
    def __init__(self,services):
        self.__service = services
        self.__board = self.__service.get_board()
        self.board_image=pygame.image.load(r"C:\Users\Administrator\Desktop\a10-915-Nimigean-Valentin\src\Pictures\Board.png")
        self.board_image = pygame.transform.scale(self.board_image, (600, 600))
        self.screen = pygame.display.set_mode((600, 800))
        self.coords=[]
        self.coords.append([0,0,0,0])
        self.coords.append([25,25,55,55])
        self.coords.append([285, 20, 325, 55])
        self.coords.append([535, 20, 585, 20])
        self.coords.append([110, 110, 150, 150])
        self.coords.append([280, 110, 320, 150])
        self.coords.append([450, 110, 490, 150])
        self.coords.append([190, 190, 230, 230])
        self.coords.append([280, 190, 320, 230])
        self.coords.append([370, 190, 410, 230])
        self.coords.append([25, 280, 65, 320])
        self.coords.append([110, 280, 150, 320])
        self.coords.append([190, 280, 230, 320])
        self.coords.append([370, 280, 410, 320])
        self.coords.append([450, 280, 490, 320])
        self.coords.append([535, 280, 585, 320])
        self.coords.append([190, 370, 230, 410])
        self.coords.append([280, 370, 320, 410])
        self.coords.append([370, 370, 410, 410])
        self.coords.append([110, 450, 150, 490])
        self.coords.append([280, 450, 320, 490])
        self.coords.append([450, 450, 490, 490])
        self.coords.append([25, 535, 55, 585])
        self.coords.append([285, 535, 325, 585])
        self.coords.append([535, 535, 585, 585])
        self.depth=self.__service.get_depth()
        self.running = True
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont("arial", 20)
        self.fps = 60
        self.clicks = []
        self.clock= pygame.time.Clock()
        self.title=pygame.display.set_caption("9 Men's Morris")


        for pos in self.coords:
            self.clicks.append(pygame.Rect(pos[0], pos[1],40,40))
    def build_board(self,end,selection,check_mill,uncomplete_move,final_phase,new_location):
        for i in range(1, 25):
            if self.__board[i] == 'X':
                pygame.draw.circle(self.screen, (255, 0, 0), self.clicks[i].center, 20)
            elif self.__board[i] == 'O':
                pygame.draw.circle(self.screen, (0, 0, 0), self.clicks[i].center, 20)
            elif self.__board[i] == '_':
                pygame.draw.circle(self.screen, (255, 255, 255), self.clicks[i].center, 20)

        if end==True:
            self.screen.blit(self.font.render("Game over!", True, (0, 0, 0)), (200, 600))
        if self.__service.get_depth()<18 and end==False:
            self.screen.blit(self.font.render("Phase 1 : placing phase", True, (0, 0, 0)), (200, 600))
        if self.__service.get_depth()>=18 and end==False:
            if final_phase==False:
                self.screen.blit(self.font.render("Phase 2 : moving phase", True, (0, 0, 0)), (200, 600))
            else:
                self.screen.blit(self.font.render("Phase 3 : flying phase", True, (0, 0, 0)), (200, 600))
        if check_mill==True and end==False:
            self.screen.blit(self.font.render("Remove a piece from the board", True, (0, 0, 0)), (200, 700))
            for i, area in enumerate(self.clicks):
                if self.__board[i] == 'X':
                    pygame.draw.circle(self.screen, (255, 0, 0), area.center, 20)
                elif self.__board[i] == 'O':
                    pygame.draw.circle(self.screen, (0, 100, 0), area.center, 20)
                elif self.__board[i] == '_':
                    pygame.draw.circle(self.screen, (255, 255, 255), area.center, 20)
        if end==False and selection!=-1 and self.__service.get_depth()>=18 and check_mill==False and uncomplete_move==True:
            self.screen.blit(self.font.render("Select the new location of the piece", True, (0, 0, 0)), (200, 700))
            if final_phase==False:
                for i in self.__service.get_moves()[selection]:
                    if self.__board[i]=='_':
                        pygame.draw.circle(self.screen, (255, 100, 255), self.clicks[i].center, 20)
            else:
                for i in range (1,25):
                    if self.__board[i]=='_':
                        pygame.draw.circle(self.screen, (255, 100, 255), self.clicks[i].center, 20)








    def run(self):

        check_mills=False
        uncomplete_move=False
        complete=False
        final_phase=False
        new_location=0
        selection=-1
        end=False
        while self.running:
            self.screen.fill((255, 255, 255))
            self.screen.blit(self.board_image, (0, 0))
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False


                if end==False and check_mills==False and complete==False and self.__service.get_depth()<18 and  event.type == pygame.MOUSEBUTTONDOWN:
                    for i, area in enumerate(self.clicks):
                        if area.collidepoint(event.pos) and self.__service.get_board()[i] == '_':
                            selection = i
                            self.__service.manage_add_piece(i)
                            self.__board = self.__service.get_board()
                            complete=True
                            self.__board = self.__service.get_board()

                if end==False and check_mills==False and self.__service.get_depth() >=18 and event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        for i, area in enumerate(self.clicks):
                            if area.collidepoint(event.pos):
                                if self.__service.get_board()[i] == 'X':
                                    selection = i
                                    new_location = i
                                    uncomplete_move= True
                                    complete=False

                if end==False and uncomplete_move==True and complete==False and self.__service.get_depth() >=18 and event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        for i, area in enumerate(self.clicks):
                            if area.collidepoint(event.pos):
                                if final_phase==False:
                                    if i in self.__service.get_moves()[new_location] and self.__service.get_board()[i]=='_':

                                        self.__service.manage_move_piece(new_location, i)
                                        selection=i
                                        new_location = i
                                        uncomplete_move= False
                                        complete=True

                                else:
                                    if self.__service.get_board()[i]=='_':
                                        self.__service.manage_move_piece(new_location, i)
                                        selection = i
                                        new_location = i
                                        uncomplete_move = False
                                        complete = True

                if end == False and complete == True:


                    if self.__service.check_mill(selection) == True:
                        check_mills = True

                if end==False and check_mills == True and event.type == pygame.MOUSEBUTTONDOWN:
                    if event.button == 1:
                        for i, area in enumerate(self.clicks):
                            if area.collidepoint(event.pos):
                                if self.__service.get_board()[i] == 'O':
                                    self.__service.manage_remove_piece(i)

                                    check_mills = False
                                    self.__board = self.__service.get_board()
                                    complete = True
                                    new_location = 0
                                    uncomplete_move = False

                self.build_board(end,selection,check_mills,uncomplete_move,final_phase,new_location)
                pygame.display.update()



                if end==False and complete==True and check_mills==False and self.__service.get_depth()>=18:

                    self.__service.oponent_phase_2()
                    self.__board = self.__service.get_board()
                    complete=False

                if end==False and self.__service.get_depth() <18 and complete==True and check_mills==False:

                    self.__service.oponent_phase_1()
                    self.__board = self.__service.get_board()
                    complete=False
                if end==False and self.__service.is_game_over()==True and self.__service.get_depth()>=18:
                    end=True
                if self.__service.get_depth()>=18:
                    if self.__service.count_pieces() == 3:
                        final_phase = True

















