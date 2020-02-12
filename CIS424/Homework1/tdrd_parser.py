
# Brandon Kelley 2716916 hw1

# tdrd_parser.py is a simple top-down recursive descent parser for the grammar given in hw1

# read file (same way I used for last project to handle errors)
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
        print("Syntax Error")
        print("\n-----------------------------------------------------------------")
        exit()


# define s(), (Start symbol), use given hw to decide "First" based on given grammar rules
# based on the grammar, we can either have any number of a's then "c d" and then any number of b's
# or we can have any number of b's then "d c" and then any number of a's

def s():
    if lookahead == 'a':  # first option: make sure we start with an a
        A()  # allow any number of a's

        if lookahead == 'c':  # make sure we have a c then d after the variable number of a's
            match('c')
        else:
            print("Syntax Error")
            print("\n-----------------------------------------------------------------")
            exit()

        if lookahead == 'd':  # make sure we have a c then d after the variable number of a's
            match('d')
        else:
            print("Syntax Error")
            print("\n-----------------------------------------------------------------")
            exit()

        B()  # allow any number of b's after

    elif lookahead == 'b':  # second option: make sure we start with a b
        B()  # allow any number of b's

        if lookahead == 'd':  # make sure we have a d then c after the variable number of b's
            match('d')
        else:
            print("Syntax Error")
            print("\n-----------------------------------------------------------------")
            exit()

        if lookahead == 'c': # make sure we have a d then c after the variable number of b's
            match('c')
        else:
            print("Syntax Error")
            print("\n-----------------------------------------------------------------")
            exit()

        A()  # allow any number of a's after

    else:
        print("Syntax Error")
        print("\n-----------------------------------------------------------------")
        exit()


# Define non-terminal A
def A():
    global lookahead
    match('a')
    if lookahead == 'a':
        A()


# Define non-terminal B
def B():
    global lookahead
    match('b')
    if lookahead == 'b':
        B()


wlist = file.read().split()  # split file into tokens, create list with token
mitr = iter(wlist)  # make an iterative list
lookahead = lexan()  # get first character

print("The given sentence is: ")
sentence = ""  # initialize the variable that will tell the user the given sentence
for token in wlist:
    sentence = sentence + " " + token  # append each token on

print(sentence + "\n")

s()  # call the start expression

if lookahead == '':  # if anything else is leftover but blank space, output syntax error
    print("Pass: Valid Sentence")
else:
    print("Fail: Syntax Error")

print("\n-----------------------------------------------------------------")
