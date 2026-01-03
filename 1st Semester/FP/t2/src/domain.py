class tennis_player:
    def __init__(self,id,name,strenght):
        self.id=id
        self.name=name
        self.strenght=strenght

    def condition(self):
        return int(self.strenght)
    def get_id(self):
        return self.id
    def set_strenght(self,value):
        self.strenght=value

    def __str__(self):
        return "Id:"+str(self.id)+", Name:"+self.name+", Strenght:"+str(self.strenght)

