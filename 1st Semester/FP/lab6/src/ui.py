#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are found here
#
import functions
def list1(list):
    ok=0
    for i in range (0,len(list)):
        ok=1
        print(list[i]["apartment"],list[i]["type"],list[i]["amount"])
    if ok==0:
        print("Nothing to show!")

def list2(list,apartment):
    ok=0
    for i in range (0,len(list)):
        if int(list[i]["apartment"])==int(apartment):
            ok=1
            print(list[i]["apartment"],list[i]["type"],list[i]["amount"])
    if ok==0:
        print("Nothing to show!")

def list3(total,sign,value):
    ok=0
    if sign=="=":
        for i in range (0,len(total)):
            if total[i]==value:
                ok=1
                print("Apartment",i)
    if sign==">":
        for i in range (0,len(total)):
            if total[i]>value:
                ok=1
                print("Apartment",i)
    if sign=="<":
        for i in range (0,len(total)):
            if total[i]<value and total[i]>0:
                ok=1
                print("Apartment",i)
    if ok==0:
        print("Nothing to show!")
def printfunc():
    print("Choose any of the commands bellow:")
    print("-add <apartment number> <expense type> <expense amount>")
    print("-remove <apartment>")
    print("-remove <start apartment> to <end apartment>")
    print("-remove <type>")
    print("-replace <apartment> <type> with <amount>")
    print("-list <apartment>")
    print("-list [ < | = | > ] <amount>")
    print("-filter <type>")
    print("-filter <value>")
    print("-undo")

def menu():
    stack_expenses=[]
    stack_total=[]

    expenses =[]
    total=functions.create_total()
    functions.hardcode(expenses,total)
    stack_expenses.append(expenses.copy())
    stack_total.append(total.copy())
    printfunc()
    while True:

        command=input(">>>")
        command.strip()
        command=command.split(" ")
        ok=1

        try:

            if command[0]=="":
                continue
            elif command[0]=="add":

                if len(command)!=4:
                    raise Exception ("Insuficient values")
                else:
                    functions.check_add(command[1],command[2],command[3])
                    functions.already_exists(expenses, command[1], command[2])
                    functions.expence_insert(expenses,total,command[1],command[2],command[3])
                    print("expense added succesfully!")

            elif command[0]=="list":
                ok=0

                functions.check_list(command)

                if functions.check_list(command)==1:
                    list1(expenses)
                elif functions.check_list(command)==2:

                    list2(expenses,command[1])
                elif functions.check_list((command))==3:
                    list3(total,command[1],int(command[2]))

            elif command[0]=="filter":
                functions.check_filter(command)
                if functions.check_filter(command)==1:
                    functions.filter1_total(expenses,total,command[1])
                    expenses=functions.filter_1(expenses,command[1])
                    print("Filtered Succesfully!")
                elif functions.check_filter(command)==2:
                    functions.filter2_total(expenses, total, command[1])
                    expenses=functions.filter_2(expenses,command[1])
                    print("Filtered Succesfully!")

            elif command[0]=="replace":
                functions.check_replace(command)
                functions.replace(expenses,total,command[1],command[2],command[4])
                print("Replaced Succesfully!")


            elif command[0]=="remove":
                functions.check_remove(command)
                if functions.check_remove(command)==1:
                    expenses=functions.remove1(expenses,int(command[1]))
                    total[int(command[1])]=0
                    print("Removed Succesfully!")
                if functions.check_remove(command)==2:
                    functions.remove2_total(expenses,total,command[1])
                    expenses=functions.remove2(expenses,command[1])
                    print("Removed Succesfully!")
                if functions.check_remove(command) == 3:
                    expenses=functions.remove3(expenses,int(command[1]),int(command[3]))
                    if int(command[1])>int(command[3]):
                        r1=int(command[3])
                        r2=int(command[1])
                    else:
                        r1=int(command[1])
                        r2=int(command[3])
                    for i in range (r1,r2+1):
                        total[i]=0
                    print("Removed Succesfully!")
            elif command[0]=="undo":
                functions.check_undo(command)
                if len(stack_total)<2 :
                    raise Exception("no previous steps")
                total=stack_total[len(stack_total)-2]
                expenses=stack_expenses[len(stack_expenses)-2]
                stack_total.pop(-1)
                stack_expenses.pop(-1)
                print("Undone Succesfully!")
                ok=0


            else:
                raise Exception("Invalid Command!")
            if ok==1:
                stack_expenses.append(expenses.copy())
                stack_total.append(total.copy())



        except Exception as wrong:
                print(wrong)





