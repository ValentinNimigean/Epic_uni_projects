#
# Functions section
#
def hardcode(list):
    name1="Milka Special"
    country1="Switzerland"
    price1=float(7.5)
    check_coffee(list,name1,country1,price1)
    name1="Dark Sensation"
    country1="France"
    price1=float(1.77)
    check_coffee(list,name1,country1,price1)
    name1="Chi-Town"
    country1="United States"
    price1=float(10)
    check_coffee(list,name1,country1,price1)
    name1="One Piece"
    country1="Japan"
    price1=float(1)
    check_coffee(list,name1,country1,price1)
    name1="Jay Spresso"
    country1="United States"
    price1=float(1.997)
    check_coffee(list,name1,country1,price1)


def get_name(coffee):
    return coffee["name"]
def get_country(coffee):
    return coffee["country"]
def get_price(coffee):
    return  coffee["price"]
def validate_coffee(coffee):
    """

    :param coffee: gives the coffee that needs to be validated
    :return:
    returns an error if the price of the coffee is invalid
    """

    price1=get_price(coffee)

    if price1<=0:
        raise Exception ("invalid price")


def build_coffee(coffee_name1,country_of_origin1,price1):
    """

    :param coffee_name1: gives the name of the coffee
    :param country_of_origin1: gives the name of the country of origin
    :param price1: gives the price
    :return: returns the coffee as a dictionary
    """
    return {"name":coffee_name1,
            "country":country_of_origin1,
            "price":price1}

def check_coffee(list,coffee_name1,country_of_origin1,price1):
    coffee=build_coffee(coffee_name1,country_of_origin1,price1)
    validate_coffee(coffee)
    add_coffee(list,coffee)



def add_coffee(list,coffee):
    """

    :param list: list of coffees
    :param coffee: coffee that needs to be added to the list
    :return: adds the coffee to the list

    """
    list.append(coffee)
    print_coffee()
def print_sequence(list):
    list1=[]
    for i in (0,len(list)):
        if i==0:
            list1.append(list[i])

        else:
            for j in range (0,len(list1)):
                if list[i-1]["country"] < list1[j]["country"]:
                    list1.append(list[i-1])
                    for k in range (j,len(list1)):
                        list1[k]=list1[k-1]
                    list1[j]=list1[i]
    print_list(list1)

def filter(list,country1,price1):
    for i in range(0,len(list)):
        if list[i]["country"]==country1 and price1>=list[i]["price"]:
            print_filter(list[i])
        elif country1=="" and price1>=list[i]["price"]:
            print_filter(list[i])
        elif price1==0 and list[i]["country"]==country1:
            print_filter(list[i])




#
# User interface section
#
def print_filter(coffee):
    print(coffee["name"]," ",coffee["country"]," ",coffee["price"])
def filter_input(list):
    country_1=input("input country:")
    price_1=input("input price:")
    if price_1=="":
        price_1=float(0)
    else:
        price_1=float(price_1)
    filter(list,country_1,price_1)
def print_list(list1):
    for i in range (0,len(list1)):
        print(list1[i]["name"]," ",list1[i]["country"])

def read_coffee(list):
    coffee_name=input("please enter name of the coffee:")
    country_of_origin=input("please enter country of origin:")
    price=float(input("please enter price:"))

    check_coffee(list,coffee_name,country_of_origin,price)
def print_coffee():
    print("Coffee added succesfully!")

def printfunc():
    print("choose one of the following commands:")
    print("1)Add a coffee shop")
    print("2)Display all coffees")
    print("3)Filter the coffees")

def menu():
    list=[]
    print("hardcode section [")
    hardcode(list)
    print("]")
    print(" ")
    printfunc()
    commands={"1":read_coffee,
              "2":print_sequence,
              "3":filter_input,

    }
    while True:
        print(list)
        command=input("choose one of the commands(1-3):")
        command.strip()

        if command in commands:
            try:
                commands[command](list)
            except Exception as wrong:
                print(wrong)





menu()