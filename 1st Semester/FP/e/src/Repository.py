import random
class Repository:
    def __init__ (self):
        self.year=1
        self.starved=0
        self.new_people=0
        self.population=100
        self.land=1000
        self.harvested=1000
        self.harvest_price=3
        self.land_price=20
        self.grain=3000
        self.rats = 200


        self.grain=self.grain-self.rats

    def increase_year(self):
        self.year=self.year+1
    def get_year(self):
        """
        returns the year
        :return:
        """
        return self.year
    def get_starved(self):
        return self.starved
    def get_rats(self):
        return self.rats
    def get_land(self):
        return self.land
    def get_harvest_price(self):
        return self.harvest_price
    def get_population(self):
        return self.population
    def get_grains(self):
        return self.grain
    def get_land_price(self):
        return self.land_price
    def get_new_people(self):
        return self.new_people
    def update(self,planted,given_to_population,land,grains):
        """
        function that updates the values based on valid inputs
        :param planted:
        :param given_to_population:
        :param land:
        :param grains:
        :return:
        """
        self.land=land
        self.grain=grains
        self.harvested=planted
        if given_to_population//20<self.population:
            self.starved=self.population-given_to_population//20
            self.new_people=0
        else:
            self.new_people=random.randint(0,10)
            self.starved=0


    def new_year(self):
        """
        function that makes the transition between years
        :return:
        """
        self.year=self.year+1
        self.population=self.population-self.starved+self.new_people
        self.harvest_price=random.randint(1,6)
        self.chance=random.randint(1,5)
        if self.chance==1:
            self.rats=self.grain//random.randint(10,100)
        else:
            self.rats=0
        self.grain=self.grain+self.harvested*self.harvest_price
        self.land_price=random.randint(15,25)
        self.grain=self.grain-self.rats

