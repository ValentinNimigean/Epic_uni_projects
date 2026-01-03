from src.domain import tennis_player
class service:
    def __init__(self,repo):
        self.repo=repo

    def get_players(self):
       return self.repo.get_players()


    def remove_player(self,player):
        self.repo.remove(player)
    def update(self,id):
        self.repo.update(id)


