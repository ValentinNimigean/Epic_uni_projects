class Controller:
    def __init__(self,repo):
        self.__repo=repo

    def get_year(self):
        """
        gets the year from the repo
        :return:
        """
        return self.__repo.get_year()
    def get_starved(self):
        return self.__repo.get_starved()
    def get_population(self):
        return self.__repo.get_population()
    def get_land(self):
        return self.__repo.get_land()

    def get_harvest_price(self):
        return self.__repo.get_harvest_price()
    def get_rats(self):
        return self.__repo.get_rats()
    def get_land_price(self):
        return self.__repo.get_land_price()
    def get_grains(self):
        return self.__repo.get_grains()
    def get_new_people(self):
        return self.__repo.get_new_people()

    def game_over(self):
        """
        checks if the game is over
        :return:
        """
        if self.__repo.get_year()==5:
            return True
        if self.__repo.get_starved()>self.__repo.get_population():
            return True
        return False

    def check_values(self,a,b,c):
        """
        checks the validity of the inputed parameters
        :param a:
        :param b:
        :param c:
        :return:
        """
        e=""
        grains = self.get_grains()
        land_price = self.get_land_price()
        land = self.get_land()
        population=self.get_population()
        if a>0:

            if a*land_price>grains:
                e=e+"can't buy that much land\n"
            else:
                land=land+a
                grains=grains-land_price*a
        elif a<0:
            if a*(-1)>land:
                e=e+"you don't have that much land to sell\n"
            else:
                land=land+a
                grains=grains+land_price*a*(-1)


        if b>grains:
            e=e+"you don't have enough grains for the population\n"
        else:
            grains=grains-b

        if c>grains:
            e=e+"you don't have enough grains to plant\n"
        else:
            grains=grains-c

        if population*10<c:
            e=e+"you don't have enough people to farm the grains"

        if e!="":
            raise Exception(e)

        planted=c
        given_to_population=b
        self.__repo.update(planted,given_to_population,land,grains)

    def new_year(self):
        """
        updates elements between years at the repo level
        :return:
        """
        self.__repo.new_year()





