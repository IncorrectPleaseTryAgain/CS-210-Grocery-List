from os import readlink
import re
import string

#dictionary to store sorted data
data = {}

#file to store sorted data
CONST_OUTPUT_FILE_NAME = "frequency.dat"

#Return - fstream
def openInputFile():
    input_message = ("* Please Enter Raw File Name (include extension): ")

    #while input file is open
    while True:
        print("**************************************************")
        input_file_name = input(input_message)

        try:
            #open input file
            input_file = open(input_file_name)
        except:
            #file could not be accessed
            print("* Error: Incorrect File Name\n")
        else:
            break

    return input_file

#Return - N/A
def writeSortedDataToOutputFile(output_file_name):
    #reference global variable
    global data

    input_file = openInputFile()

    #open outut file
    output_file = open(output_file_name, 'w')

    #read input
    for item in input_file:
        #remove '\n' from end of string
	    item = item.rstrip()

        #if item it is not in dictionary - add to dictionary
        #else if item is in dictionary - increment frequency
	    if item not in data:
		    data[item] = 1
	    else:
		    data[item] = data[item] + 1

    #write dictionary data to output file
    for key,value in data.items():
        #format data into single string
        item_string = key + ' ' + str(value) + '\n'
        #write data
        output_file.write(item_string)

    #close file
    input_file.close()
    output_file.close()

#Return - N/A
#Display list of items and frequency
def displayItemsAndFrequency(output_file_name):

    #while output file is open
    while True:
        try:
            #open outut file
            output_file = open(output_file_name, 'r')
        except:
            #output file not found - end function
            print("Could Not Open '{}'".format(output_file_name))
            return None
        else:
            #output file is open - break loop
            break

    #Display list
    print('===========================')
    print(f"{'Name' : <15}{'Frequency' : ^15}")
    for item in output_file:
        #split current item into name and frequency
        current_item = item.split()
        #display name and frequency
        print(f"{current_item[0] : <15}{current_item[1] : ^15}")
    print('===========================')

    #close output file
    output_file.close()

#Return - intiger
#Display frequency for specific item
def returnFrequencyForSpecificItem(output_file_name, specific_item_name):
    #open output file
    output_file = open(output_file_name, 'r')

    #search for specific item in output file
    for item in output_file:
        #if specific item found
        if(specific_item_name == item.split()[0]):
            #return item frequency
            return(int(item.split()[1]))

    #close output file
    output_file.close()

    #if specific item was not found return -1 (NO_ITEM_EXISTS)
    return -1
