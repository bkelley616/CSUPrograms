
# Brandon Kelley 2716916 CIS 424 Project 3
from functools import reduce

print("\n--------------------------------------------------------------------------------------")
print("\n\t\t\t\tCIS 424 Project 3")



# Problem 5 - Use the function Map and an anonymous function to turn an integer list L into a list of reals, each of
# which is the absolute value of the element in L. *)

print("\n\n\t\t\t\t Problem 5:\n")

def convertToRealABS (List):
    if len(List) == 0:  # if list is empty print error
        print("Error: List is empty")
    else:  # else print new list based on lambda functions return value
        print(list(map(lambda x : float(-x) if x < 0 else float(x), List)))

print("\tTest Case(s):\n")

#convertToRealABS([])
print("convertToRealABS([10, -20, -30, -40, 50, 60])")
convertToRealABS([10, -20, -30, -40, 50, 60])


# Problem 6 - Use the function Reduce and an anonymous function to find the maximum of a list of reals.

print("\n\n\t\t\t\t Problem 6:\n")

def getMax (List):
    if len(List) == 0:  # if list is empty print error
        print("Error: List is empty")
    else:  # else print return max value by comparing one by one with reduce
        print(reduce(lambda x, y: x if x > y else y, List))

print("\tTest Case(s):\n")

#getMax([])
print("getMax([10.0, -20.0, -30.0, -40.0, 50.0, 60.0])")
getMax([10.0, -20.0, -30.0, -40.0, 50.0, 60.0])


# Problem 7 - Use the function Filter and an anonymous function to find those elements of a list of reals that are
# between 10.0 and 20.0 (inclusive).

print("\n\n\t\t\t\t Problem 7:\n")

def filterToRange10to20 (List):
    if len(List) == 0:  # if list is empty print error
        print("Error: List is empty")
    else:  # else filter out elements that don't fit the lambda function and return the list
        print(list(filter(lambda x : x >= 10.0 and x <= 20.0, List)))

print("\tTest Case(s):\n")

#getMax([])
print("filterToRange10to20([1.0, 9.99, 10.0, 10.1, 15.0, 19.99, 20.0, 20.1, 25.0])")
filterToRange10to20([1.0, 9.99, 10.0, 10.1, 15.0, 19.99, 20.0, 20.1, 25.0])



print("\n--------------------------------------------------------------------------------------")