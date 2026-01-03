import random
class ui:
    def __init__(self,service):
        self.service=service


    def run(self):
        self.print_players()
        self.game_phase()


    def print_players(self):
        print("the players (sorted descending by strenght) are:")
        players=self.service.get_players()
        for i in range(len(players)):
            print(players[len(players)-i-1])

    def game_phase(self):
        k=len(self.service.get_players())
        p=int(1)
        while p<=k:
            p=p*2
        p=int(p/2)
        if p!=k:
            print("Qualifying round!")
            players=self.service.get_players()
            eliminees=[]
            for i in range((k-p)*2):
                eliminees.append(players[i])
            while eliminees!=[]:
                player1=eliminees[random.randint(0,len(eliminees)-1)]
                eliminees.remove(player1)
                player2 = eliminees[random.randint(0, len(eliminees) - 1)]
                eliminees.remove(player2)
                print("Who will win?"+str(player1.name)+"(1) or "+str(player2.name)+"(2):")
                choise=int(input())
                if choise==1:
                    self.service.update(player1.get_id())
                    self.service.remove_player(player2)
                else:
                    self.service.update(player2.get_id())
                    self.service.remove_player(player1)


            self.print_players()







