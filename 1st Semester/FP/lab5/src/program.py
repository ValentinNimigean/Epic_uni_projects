#Nimigean Valentin
import math
# Write the implementation for A5 in this file
#
def get_real(number):
    number_split=number.replace('+',' ').replace('i',' ').split()
    return (number_split[0])

def get_imaginary(number):
    number_split = number.replace('+', ' ').replace('i', ' ').split()
    number_split.append(0)
    number_split.append(0)
    return (number_split[1])
def build1_dictionary(a,b):
    return {"real":a,
            "imaginary":b

    }
def build1_list(a,b):
    l1=[]
    l1.append(a)
    l1.append(b)
    return l1
#
# Write below this comment
#
# Write below this comment
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def initial_list(list):
    number='7+18i'
    list.append(build_complex_list(number))
    number = '18+10i'
    list.append(build_complex_list(number))
    number= '9+8i'
    list.append(build_complex_list(number))
    number= '16+180i'
    list.append(build_complex_list(number))
    number='25+6i'
    list.append(build_complex_list(number))
    number='7+100i'
    list.append(build_complex_list(number))
    number ='3+100i'
    list.append(build_complex_list(number))
    number ='4+6i'
    list.append(build_complex_list(number))
def build_complex_list(number):
    list_list = []
    list_list.append(int(get_real(number)))
    list_list.append(int(get_imaginary(number)))
    return list_list

def build_list(number):
    string=''
    string=string+str(number[0])+"+"+str(number[1])+"i"
    return  string
#
# Write below this comment
# Write below this comment
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def initial_dictionary(list):
    number='7+18i'
    list.append(build_complex_dictionary(number))
    number = '18+10i'
    list.append(build_complex_dictionary(number))
    number= '9+8i'
    list.append(build_complex_dictionary(number))
    number= '16+180i'
    list.append(build_complex_dictionary(number))
    number='25+6i'
    list.append(build_complex_dictionary(number))
    number='7+100i'
    list.append(build_complex_dictionary(number))
    number ='3+100i'
    list.append(build_complex_dictionary(number))
    number ='4+6i'
    list.append(build_complex_dictionary(number))

def build_complex_dictionary(number):
    complex_dictionary={'real':get_real(number),
    'imaginary':get_imaginary(number)
    }
    return complex_dictionary
def build_dictionary(number):
    string=''
    string=string+number["real"]+"+"+number["imaginary"]+"i"
    return string



#
# Write below this comment
# Write below this comment
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def mountain_subarray_dictionary(list):
    left=0
    right=0
    maxim_lenght=0
    maxim_left=0
    maxim_right=0
    maxim=0
    for i in range (1,len(list)-2):
        if list[i-1]["real"]<list[i]["real"]and list[i]["real"]>list[i+1]["real"]:
            left=i-1
            right=i+1
            while left > 0 and list[left-1]["real"]>list[left]["real"]:
                left=left-1
            while right < len(list)-1 and list[right]["real"] > list[right+1]["real"]:
                right=right+1

            if right-left+1>=maxim:
                maxim_right=right
                maxim_left=left
                maxim = right-left+1
    print_mountain_subarray_dictionary(maxim_left,maxim_right,list)





def mountain_subarray_list(list):
    left=0
    right=0
    maxim_lenght=0
    maxim_left=0
    maxim_right=0
    maxim=0
    for i in range (1,len(list)-2):
        if list[i-1][0]<list[i][0] and list[i][0]>list[i+1][0]:
            left=i-1
            right=i+1
            while left > 0 and list[left-1][0]>list[left][0]:
                left=left-1
            while right < len(list)-1 and list[right][0] > list[right+1][0]:
                right=right+1

            if right-left+1>=maxim:
                maxim_right=right
                maxim_left=left
                maxim = right-left+1
    print_mountain_subarray_list(maxim_left,maxim_right,list)





def longest_increasing(list,ok):
    list1=[]
    if ok==1:
        for i in range(0,len(list)):
            list1.append(math.sqrt(list[i][0]*list[i][0]+list[i][1]*list[i][1]))
    if ok==2:
        for i in range(0,len(list)):
            list1.append(math.sqrt(int(list[i]["real"])*int(list[i]["real"])+int(list[i]["imaginary"])*int(list[i]["imaginary"])))
    list2=[]
    for i in range(0,len(list)):
        list2.append(int(1))
    for i in range(1,len(list1)):
        for j in range(0,i):
            if list1[j]<list1[i] and list2[i]<list2[j]+1:
                list2[i]=list2[j]+1

    lenght=0
    for i in range(0,len(list)):
        if(list2[i]>lenght):
            lenght=list2[i]
    print_sequence(lenght,list2,list,ok)





#
# Write below this comment
# Write below this comment
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def print_mountain_subarray_dictionary(maxim_left,maxim_right,list):
    print("lenght is: ",maxim_right-maxim_left+1)
    for i in range(maxim_left,maxim_right+1):
        print(build_dictionary(list[i]))
def print_mountain_subarray_list(maxim_left,maxim_right,list):
    print("lenght is: ",maxim_right-maxim_left+1)
    for i in range(maxim_left,maxim_right+1):
        print(build_list(list[i]))

def print_sequence(lenght,list2,list,ok):
    print ("maximum lenght is:",lenght)
    for i in range(0,len(list)):
        if list2[len(list)-i-1]==lenght:
            if ok==1:
                print(build_list(list[len(list)-i-1]))
            if ok==2:
                print(build_dictionary(list[len(list)-i-1]))
            lenght=lenght-1

def choosetype():
    return  int(input("choose between list representation (1) and dictionary representation (2):"))

def choosefunc():
    return  int(input("choose one of the functionalities:"))

def printfunc():
    print("1) Read a list of complex numbers.")
    print("2) Display the entire list of numbers.")
    print("3) Display the lenght and the elements of a longest subarray of numbers where their real part is in the form of a mountain.")
    print("4) Display the length and elements of a longest increasing subsequence, when considering each number's modulus.")
    print("5) Choose list representation method")
    print("6) Exit the application.")
    print("")
def printlist(list):
    for i in range(0, len(list)):
        print(list[i][0], "+", list[i][1],"i")
def printdictionary(list):
    for i in range(0, len(list)):
        print(list[i]["real"], "+", list[i]["imaginary"],"i")

def read_list_list(list1):
    n=int (input("input the lenght of the list: "))
    list1=[]
    for i in range(0,n):
        number=str(input("please input element: "))

        list1.append(build_complex_list(number))
    return  list1
def read_list_dictionary(list1):
    n=int (input("input the lenght of the list: "))
    list1=[]
    for i in range(0,n):
        number=str(input("please input element: "))

        list1.append(build_complex_dictionary(number))
    return  list1
def menu1(list,ok):


    printfunc()
    function=choosefunc()
    if function>5:
        menu1(list,ok)
    if function==1:
        if ok==1:
            list=read_list_list(list)
            print("List created succesfully!")
        if ok==2:
            list=read_list_dictionary(list)
            print("List created succesfully!")
    if function==2:
        if ok==1:
            printlist(list)
        if ok==2:
            printdictionary(list)
    if function==3:
        if ok==1:
            mountain_subarray_list(list)
        if ok==2:
            mountain_subarray_dictionary(list)
    if function==4:
        longest_increasing(list,ok)
    if function==5:
        menu(list,ok)
    if function==6:
        print ("byeeee :3")
        return 
    menu1(list,ok)

def menu(list,ok):
    ok=choosetype()
    if ok!=1 and ok!=2:
        print ("invalid selection!")
        menu()
    if ok==1:
        list=[]
        initial_list(list)
    if ok==2:
        list=[]
        initial_dictionary(list)
    menu1(list,ok)





if __name__ == "__main__":
    menu(0,0)


