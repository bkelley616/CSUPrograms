#!/usr/bin/python3

# Brandon Kelley 2716916 Project 2
# let.py is a program that parses and evaluates a given simple strong typed program

# ************************************** Open File *************************************

import sys  # needed to read commandline argument

# note: same method of opening file from my last project
try:  # try to find the file from the commandline, output error if unable to find
    filename = sys.argv[1]  # the script name itself is located at index 0, so look at the second location, index 1

    try:  # try to open the file, output error message if unable.
        file = open(filename, "r+")
    except IOError as e:
        print("-----------------------------------------------------------------")
        print("Error: unable to find/read " + filename)
        print("\n-----------------------------------------------------------------")
        sys.exit()  # exit program, after displaying error

    print("-----------------------------------------------------------------")  # formatting
    print("Reading " + filename + "...\n")  # tell user what file is being read (that they typed)
except IndexError as e:
    print("-----------------------------------------------------------------")
    print("Error: No File Entered \n\nPlease Type the Filename After the Script Name in The Command Line")
    print("-----------------------------------------------------------------")
    exit(1)

# ************************************** End: Open File *************************************

# *************** Define utility methods and Global Variables ****************

# define lexan(), gets next token
def lexan():
    global mitr

    try:
        return next(mitr)
    except StopIteration:
        return ''


# define match(ch), check if character given matches lookahead and consumes it if it does. if not, syntax error
def match(ch):
    global lookahead

    if ch == lookahead:
        lookahead = lexan()
    else:
        print("Syntax Error: \n\tTrace:\tmatch()")
        print("\nProgram terminated with exit code 1")
        print("-----------------------------------------------------------------")
        exit(1)


# define error_stmt, function to output error (with trace) and terminate program
def error_stmt(trace):  # did this to refactor code to be smaller, had error code repeated multiple times
    print("Syntax Error: \n\tTrace:\t" + trace)
    print("\nProgram terminated with exit code 1")
    print("-----------------------------------------------------------------")
    exit(1)

# define globals
wlist = file.read().split()  # split file into tokens, create list with token
mitr = iter(wlist)  # make an iterative list out of given list
lookahead = lexan()  # get first token
var_table = dict()  # initialize dictionary
stmt_counter = 0  # used for formatting output of program (counts number of let statements)


# ********************* End:  Define utility methods and Global Variables *****************


# *********************** Grammar Methods (follows order on paper)**********************************

# define prog, begins the program and runs until it is finished with let statements or error
def prog():
    global lookahead #get global

    while (lookahead == 'let'):
        let_in_end()
        # print(var_table) # used to debug
        var_table.clear()

# define let_in_end, provides the structure of the tiny programming language by outlining the main component, let-in-end statements
def let_in_end():
    global lookahead  # get globals
    global stmt_counter

    if lookahead == "let":
        match("let")  # step over let, begin variable declaration
    else:
        error_stmt("let_in_end")

    decl_list()

    if lookahead == "in":
        match("in")  # step over in, begin solving program
    else:
        error_stmt("let_in_end")

    var_type = t_type()  # get variable type of next token
    answer = expr(var_type)  # get the answer to the in statement

    if lookahead == "end":
        match("end")  # step over end, move on to outputting result
    else:
        error_stmt("let_in_end")

    stmt_counter += 1  # count let statements for better readability of output

    if lookahead == ';':  # step over ; and print out the answer to the in block
        match(';')
        print("Let Statement #" + str(stmt_counter) + " Output:")
        print("\n\t" + str(answer[1]))
        print("")
        return
    else:
        error_stmt("let_in_end")

# define decl_list, structure of let block, defines the variable and stores in variable table (dictionary)
def decl_list():

    global lookahead

    while (lookahead != 'in'):  # until we get to the in block, define variables
        decl()
    return

# define decl(), provides structure of each variable definition, and puts each declaration in variable table
def decl():

    global lookahead      # get globals
    global var_table

    var_id = lookahead      # get the variable id
    lookahead = lexan()     # advance to next token

    if lookahead != ':':  # step over :
        error_stmt("decl()")
    match(":")

    var_type = t_type() # get variable type

    if lookahead != '=':   # step over =
        error_stmt("decl()")
    match("=")

    var_attributes = expr(var_type)  # set variable attributes to list returned in following format: (type, value)

    if lookahead != ';':  # step over ;
        error_stmt("decl()")
    match(';')

    var_table[var_id] = dict()  # create/add variable to dictionary
    var_table[var_id]["Attributes"] = var_attributes  # set the attributes of the variable in the dictionary

    return

# define t_type, used to get type, int and real supported then return that type
def t_type(): # change to t_type not conflict with default python type method as noted in class

    if lookahead == 'int':  # get, set, and return type of int
        var_type = "int"
        match(lookahead)
        return var_type
    elif lookahead == "real":  # get, set, and return type of real
        var_type = "real"
        match(lookahead)
        return var_type
    else:
        error_stmt("t_type()")

# define expr(exp_type), take variable type as parameter, solves the expression, and returns the resulting value
def expr(exp_type):  # breaks down into terms
    global lookahead  # get global lookahead

    if lookahead == "if":  # check for if statement, if true step over then, then continue with then statement
        if (cond()):      # program will ignore the else statement using the logic in the while loop
            match("then")
        else:   # returns false, so skip to else statement
            while lookahead != "else":
                lookahead = lexan()   # step past then statement
            match("else")  # match the else so the else statement wont be ignored below

    val = term(exp_type)   # initialize value to left term

    while (lookahead != ''):  # while lookahead is not empty, (operator expected)
        if lookahead == "else":  # ignore else statements, the if statement above takes care of this issue by matching
                                 # the else statement so it wont get ignored if the condition is false
            while lookahead != ')':
                lookahead = lexan()
        elif lookahead == '+':  # perform addition
            match('+')  # step past +
            val[1] += term(exp_type)[1]
        elif lookahead == '-':  # perform subtraction
            match('-')  # step past -
            val[1] -= term(exp_type)[1]
        elif lookahead == ')':  # break out of loop for ), ;, end
            break
        elif lookahead == ';':
            break
        elif lookahead == "end":
            break
        else:
            error_stmt("expr(var_type)")

    return val  # return the resulting value after the expr is solved

# define term(exp_type), takes variable type, and will return the resulting factor (breaks down to factor)
def term(exp_type):
    global lookahead  # get global

    val = factor(exp_type)  # get left factor value

    while lookahead != '':  # while lookahead is not empty, compute val and right factor
        if lookahead == '*':
            match('*')  # step past *
            val[1] *= factor(exp_type)[1]
        elif lookahead == '/':
            match('/')  # step past /
            val[1] /= factor(exp_type)[1]
        else:
            break

    return val  # return the resulting value when the term is solved

# define factor(exp_type), takes variable type, and returns the resulting attribute list (type, value) of the variable
def factor(exp_type):  # var type parameter is only used if (, overwritten otherwise
    global lookahead  # get globals
    global var_table

    if lookahead == '(':  # check for expression in parenthesis to do first ( <expr> )
        match('(')  # step past (
        var_attributes = expr(exp_type)  # set variable attributes by solving the nested expr recursively
        attributes = list((exp_type, var_attributes[1]))  # set attribute list
        match(')')  # step past )

    elif lookahead == 'int':  # int ( id ) cast
        var_type = t_type()  # get variable type

        if var_type != exp_type:  # make sure both types match
            error_stmt("factor(exp_type)")

        if lookahead == '(':  # check for (
            match('(')  # step past (

            if lookahead in var_table:  # variable is in table
                var_attributes = list(var_table[lookahead]["Attributes"])
                attributes = list((var_attributes[0], var_attributes[1]))  # get type and value from var_table
            else:  # variable not in table
                attributes = list((var_type, lookahead))  # use the var type and the next value

            match(lookahead)  # step past value
            match(')')  # step past )

    elif lookahead == 'real':  # real ( id ) cast
        var_type = t_type()  # get variable type

        if var_type != exp_type:  # make sure both types match
            error_stmt("factor(exp_type)")

        if lookahead == '(':  # check for (
            match('(')  # step past (

            if lookahead in var_table:  # variable is in table
                var_attributes = list(var_table[lookahead]["Attributes"])
                attributes = list((var_attributes[0], var_attributes[1]))  # get type and value from var_table
            else:  # variable not in table
                attributes = list((var_type, lookahead))  # use the var type and the next value

            match(lookahead)  # step past value
            match(')')  # step past )

    else:  # id | number

        var = lookahead  # var is next token

        if var in var_table:  # variable is already in table
            var_attributes = list(var_table[var]["Attributes"])

        else:
            if exp_type == 'int':  # use try and catch block to attempt to cast value as int
                try:  # if unable catch the exception and output corresponding error
                    var_attributes = list((exp_type, int(var)))

                except Exception:
                    error_stmt("factor(exp_type)")
            elif exp_type == 'real':  # use try and catch block to attempt to cast value as real
                try:  # if unable catch the exception and output corresponding error
                    var_attributes = list((exp_type, float(var)))

                except Exception:
                    error_stmt("factor(exp_type)")
            else:
                error_stmt("factor(exp_type)")

        attributes = list((exp_type, var_attributes[1]))  # set attribute list
        lookahead = lexan()  # advance lookahead

    return attributes  # return the attribute list of the given factor

# define cond(), used to evaluate if then else statements, returns True or False
def cond():
    global var_table  # get globals
    global lookahead

    match('if')  # step past if
    operand1 = oprnd()  # get first operand
    operator = lookahead  # operator is the next token
    match(lookahead)  # step past operator
    operand2 = oprnd()  # get second operand

    # evaluate the conditional statement based on the operator (and oprnd values), error if operator is unrecognized
    if operator == '>':
        if (operand1 > operand2):               # if statement is True then return true, else return False
            return True
        else:
            return False
    elif operator == '<':
        if (operand1 < operand2):
            return True
        else:
            return False
    elif operator == '>=':
        if (operand1 >= operand2):
            return True
        else:
            return False
    elif operator == '<=':
        if (operand1 <= operand2):
            return True
        else:
            return False
    elif operator == '==':
        if (operand1 == operand2):
            return True
        else:
            return False
    elif operator == '<>':
        if (operand1 != operand2):
            return True
        else:
            return False
    else:
        error_stmt("cond()")

# define oprnd(), returns the variable id or the number to be used in the conditional statement above
def oprnd():

    global lookahead  # get globals
    global var_table

    oprnd = lookahead  # set oprnd to the next token and then step past it
    match(lookahead)

    # check if oprnd is in the variable table
    if oprnd in var_table:   # if not it is a number so make sure it is the correct type in the else stmt
        oprnd = var_table[oprnd]["Attributes"][1]
        return oprnd
    else:
        try:
            oprnd = int(oprnd)  # oprnd is an int
        except Exception:
            try:
                oprnd = float(oprnd)  # oprnd is a real
            except Exception:
                error_stmt("oprnd()")  # oprnd is not defined in the variable table, and not a int or real number

    return oprnd  # return correct oprnd


# *********************** End: Grammar Methods (follows order on paper) **********************************


# ************************************* Run Program **********************************************
prog()  # call start of program

if lookahead == '':  # if no tokens are left but blank, exit with code 0 (successful), otherwise exit code 1 (error)
    print("\nProgram terminated with exit code 0")
    print("-----------------------------------------------------------------")
    exit(1)
else:
    print("\nProgram terminated with exit code 1")
    print("-----------------------------------------------------------------")
    exit(1)

# ************************************* End Program **********************************************
