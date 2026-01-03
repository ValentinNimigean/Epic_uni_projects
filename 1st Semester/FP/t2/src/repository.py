from src.domain import tennis_player
class repository:
    def __init__(self,file):
        self.players=[]
        self.file=file
        self.players=self.load_from_file(self.file)
    def load_from_file(self,file):
        tennis=open(file,"r")
        for player in tennis:
            player=player.strip()
            player=player.split(",")
            self.players.append(tennis_player(int(player[0]),player[1],int(player[2])))
        return self.players

        tennis.close()
    def get_players(self):
        return self.players
    def remove(self,player):
        self.players.remove(player)
    def update(self,id):

        for i in self.players:
            if i.get_id()==id:
                rank=i.condition()
                rank=rank+1
                i.set_strenght(rank)
