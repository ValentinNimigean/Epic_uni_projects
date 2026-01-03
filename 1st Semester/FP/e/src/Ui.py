class Ui:
    def __init__(self,cont):
        self.__cont=cont


    def print_text(self):
        print("In year",self.__cont.get_year(),",",self.__cont.get_starved(),"people starved.")
        print(self.__cont.get_new_people(),"people came to the city.")
        print("City population is",self.__cont.get_population())
        print("City owns", self.__cont.get_land(),"acres of land.")
        print("Harvest was",self.__cont.get_harvest_price(),"units per acre")
        print("Rats ate",self.__cont.get_rats(),"units.")
        print("Land price is",self.__cont.get_land_price(),"units per acre.")
        print()
        print("Grain stocks are",self.__cont.get_grains(),"units.")

    def run(self):
        while self.__cont.game_over()==False:
            self.print_text()
            try:

                acres_buy=input("Acres to buy/sell(+/-)->")

                acres_buy=int(acres_buy)



                units_feed=input("Units to feed the population->")

                units_feed=int(units_feed)
                if units_feed<0:
                    raise Exception("units to feed should be a positive value")


                acres_plant=input("Acres to plant->")
                acres_plant=int(acres_plant)
                if acres_plant<0:
                    raise Exception("Acres to plant should be a positive value")
                try:
                    self.__cont.check_values(acres_buy, units_feed, acres_plant)
                    self.__cont.new_year()
                except Exception as e:
                    print(e)


                print()
            except Exception as e:
                print(e)
                print()
                print()




        self.print_text()
        print()
        print("GAME OVER")
        if self.__cont.get_year()==5:
            if self.__cont.get_population()>100 and self.__cont.get_land()>1000:
                print("CONGRATULATIONS(YOU DID GREAT)")
            else:
                print("YOU DID NOT DO WELL (YOU LOST)")
        else:
            print("YOU DID NOT DO WELL (YOU LOST)")










