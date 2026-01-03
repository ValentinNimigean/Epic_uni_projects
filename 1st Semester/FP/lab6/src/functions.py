#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print statements. Functions here
# communicate via function parameters, the return statement and raising of exceptions. 
#
import random


def build_expence (rule1,rule2,rule3):
    return {"apartment":int(rule1),
            "type":rule2,
            "amount":int(rule3)
    }
def test_build_expence():
    apartment="35"
    type="gas"
    amount="21"
    expense=build_expence(apartment,type,amount)
    assert int(apartment)==expense["apartment"]
    assert type==expense["type"]
    assert int(amount)==expense["amount"]

def create_total():
    l1=[]
    for i in range(0,250):
        l1.append(0)
    return l1
def hardcode(list,list1):
    """
    The program hardcodes 15 expenses at the beggining of the program
    :param list:Expenses
    :param list1: Total cost for each apartment
    :return:
    """
    types=["gas","heating","electricity","water","others"]

    for i in range (0,15):
        r2=random.choice(types)
        r1=random.randint(1,100)
        r3=random.randint(1,100)
        ok=1
        for i in range(0,len(list)):
            if int(list[i]["apartment"]) == r1 and list[i]["type"] == r2:
                ok=0
        if ok==1:
            list.append(build_expence(r1,r2,r3))
            list1[r1]+=r3


def already_exists(list,rule1,rule2):
    """
    The program verifies if two expenses of the same type and for the same apartment exist at the same time
    :param list:Expenses
    :param rule1: apartment
    :param rule2: type
    :return:
    """
    for i in range(0,len(list)):
        if int(list[i]["apartment"])==int(rule1) and list[i]["type"]==rule2:
            raise Exception("Transaction already exists")
def check_add(rule1,rule2,rule3):
    """
    The program verifies if the parameters given for the add function are valid

    :param rule1: apartment
    :param rule2: type
    :param rule3: amount
    :return:
    """
    wrong=""
    if rule1.isnumeric()==False:
        wrong+="Invalid apartment number!\n"
    if rule2 != "gas" and rule2!="water" and rule2 != "heating" and rule2!="electricity" and rule2!="others":
        wrong+="Invalid expense type!\n"
    if rule3.isnumeric()==False:

        wrong += "Invalid amount!\n"

    if len(wrong)>0:
        raise Exception (wrong)

def test_check_add():
    apartment="10"
    type="gas"
    amount="25"
    check_add(apartment,type,amount)
    bad_apartment="-40"
    bad_type="juice"
    bad_amount="-60"
    try:
        check_add(bad_apartment,bad_type,bad_amount)
        assert False
    except Exception as wrong:
        assert str(wrong)=="Invalid apartment number!\nInvalid expense type!\nInvalid amount!\n"
def test_expence_insert():
    apartment="10"
    type="gas"
    amount="25"
    expense1=[]
    total1=create_total()
    expence_insert(expense1,total1,apartment,type,amount)
    assert len(expense1)==1
    assert total1[expense1[0]["apartment"]]==total1
    try:
        expence_insert(expense1,total1,apartment,type,amount)
    except Exception as ex:
        assert str(ex)=="Transaction already exists"

def expence_insert(list,total,rule1,rule2,rule3):
    """
    program inserts expence into the list and adds to the total cost of each apartment
    :param list:list of expenses
    :param total: list of total cost for each apartment
    :param rule1: apartment number
    :param rule2: expence type
    :param rule3: amount
    :return:
    """
    build_expence(rule1,rule2,rule3)
    total[int(rule1)]+=int(rule3)
    list.append(build_expence(rule1,rule2,rule3))




def check_list(command):
    """
    The program checks if the list command is valid
    :param command:command
    :return:
    """
    if len(command)==1:
        return 1
    elif len(command)==2:
        if command[1].isnumeric()==False:
            raise Exception("Invalid Cost")
        else:
            return 2
    elif len(command)==3:
        if command[2].isnumeric()==False:
            raise Exception("Invalid Cost")
        elif command[1]!="<" and command[1]!=">" and command[1]!="=":
            raise Exception("invalid Sign")
        else:
            return 3
    elif len(command)>3:
        raise Exception("Too many arguments")






def check_remove(command):
    """
    Program checks if the remove command given is valid
    :param command: command
    :return:
    """
    if len(command)==1:
        raise Exception("Not enough arguments!")
    elif len(command)==2:
        if command[1].isnumeric()==False:
            if command[1] != "gas" and command[1] != "water" and command[1] != "heating" and command[1] != "electricity" and command[1] != "others":
                raise Exception("Invalid Type!")
            else:
                return 2
        else:
            return 1
    elif len(command)==4:
        if command[1].isnumeric()==False or command[3].isnumeric()==False or command[2]!="to":
            raise Exception ("Invalid format")
        else:
            return 3
    elif len(command)==3 or len(command)>4:
        raise Exception("Invalid Format")

def remove1(list,argument):
    """
 The program removes all excpenses from apartment denoted by the argument
    :param list: expences
    :param argument: number by wich i remove elements from the list
    :return:
    """
    l1=[]
    for i in range (0,len(list)):
        if list[i]["apartment"]!=int(argument):
            l1.append(list[i])
    return l1

def remove2_total(list,total,argument):
    """
    The program decreases the total amount for an apartment if the expense is of a specific type
    :param list:expense list
    :param total: total amount list
    :param argument: expense type
    :return:
    """
    for i in range (0,len(list)):
        if list[i]["type"]==argument:
            total[list[i]["apartment"]]-=list[i]["amount"]

def remove2(list,argument):
    """
    removes all expenses of the "argument" type
    :param list: expense list
    :param argument: expense type
    :return:
    """
    l1=[]
    for i in range (0,len(list)):
        if list[i]["type"]!=argument:
            l1.append(list[i])
    return l1
def remove3(list,argument1,argument2):
    """
    The program removes all expenses for the apartments in the interval determined by a1 and a2
    :param list:expense list
    :param argument1:initial apartmnet number
    :param argument2:  final apartment number
    :return:
    """
    l1=[]
    if argument1>argument2:
        aux=argument1
        argument1=argument2
        argument2=aux
    for i in range (0,len(list)):
        if list[i]["apartment"]<argument1 or list[i]["apartment"]>argument2:
            l1.append(list[i])
    return l1

def check_replace(command):
    """
    The program checks if the replace command given is valid
    :param command: replace command
    :return:
    """
    if len(command)!=5:
        raise Exception("Incorrect format!")
    else:
        wrong=""
        if command[1].isnumeric()==False:
            wrong+="Invalid Apartment Number! \n"
        if command[2] != "gas" and command[2] != "water" and command[2] != "heating" and command[2] != "electricity" and command[2] != "others":
            wrong+="Invalid Type! \n"
        if command[3] != "with":
            wrong+="Invalid connector parameter!"
        if command[4].isnumeric()==False:
            wrong+="Invalid Cost! \n"
        if wrong!="":
            raise Exception(wrong)

def replace(list,list1,rule1,rule2,rule3):
    """
The program checks if the expense to be replaced esxists and replaces the amount for that specific expense
    :param list: expense list
    :param list1: total cost list
    :param rule1: aqpartment number
    :param rule2: expense type
    :param rule3: amount with wich i replace
    :return:
    """
    ok1=0
    for i in range(0,len(list)):
        if int(list[i]["apartment"])==int(rule1) and list[i]["type"]==rule2:
            ok1=ok1+1
            list1[int(rule1)]-=list[i]["amount"]
            list[i]["amount"]=int(rule3)
            list1[int(rule1)]+=int(rule3)

    if ok1==0:
        raise Exception("Transaction does not exist!")



def check_filter(command):
    """
    the program checks if the filter command is valid
    :param command: filter command
    :return:
    """
    if len(command)==1:
        raise Exception ("No arguments")
    elif len(command)==2:
        if command[1].isnumeric()==True:
            return 1
        elif command[1] != "gas" and command[1] != "water" and command[1] != "heating" and command[1] != "electricity" and command[1] != "others":
            raise Exception("Invalid Type!")
        else:
            return 2
    elif len(command)>2:
        raise Exception("Too many arguments!")

def filter1_total(list,total,argument):
    """
    the program decreases the total amount for a specific apartment for every expense eich i filter out of the lsit
    :param list:expense list
    :param total: total amount list
    :param argument: amount by witch i filter
    :return:
    """

    for i in range(0,len(list)):
        if int(list[i]["amount"])>=int(argument):
            total[list[i]["apartment"]]-=list[i]["amount"]
def filter_1(list,argument):
    """
    the program filters expenses so that they are smaller that the argument
    :param list:expense list
    :param argument: amount by witch it filters
    :return:
    """

    l1=[]
    for i in range(0,len(list)):
        if int(list[i]["amount"])<int(argument):
            l1.append(list[i])
    return l1

def filter2_total(list,total,argument):
    """
    the program decreases the total amount for a specific apartment for every expense eich i filter out of the lsit
    :param list:expense list
    :param total: total amount list
    :param argument: amount by witch i filter
    :return:
    """
    for i in range(0,len(list)):
        if list[i]["type"].strip() != argument.strip():
            total[list[i]["apartment"]]-=list[i]["amount"]
def filter_2(list,argument):
    """
    the program filters expenses by expense type
    :param list: expense list
    :param argument: type i want to filter
    :return:
    """
    k=0
    list1=[]

    for i in range(0,len(list)):
        if list[i]["type"].strip()==argument.strip():
            list1.append(list[i])
    return list1

def check_undo(command):
    """
    the program checks if the undo function is valid
    :param command: command
    :return:
    """
    if len(command)>1:
        raise Exception("Invalid Format!")
def run_tests():
    test_check_add()
    test_build_expence()
    test_build_expence()