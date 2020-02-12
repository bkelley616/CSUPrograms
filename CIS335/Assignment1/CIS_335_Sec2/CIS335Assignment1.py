
# Brandon Kelley 2716916 Assignment 1
# This program takes in an integer (decimal) and converts it to a Hexadecimal String

print("--------------------------------------------------------------------------------------------------")
print("\t\tDecimal to Hexadecimal Converter\n") # formatting

decimalNumber = ''  # create decimal number string, this is needed to catch the user error of not entering an integer
while str(decimalNumber).isdigit() == False:
    decimalNumber = input("\t\tPlease Enter a Integer to be converted to a Hexadecimal string:\n\n\t\t\t\t")
    if str(decimalNumber).isdigit() == True:
        break
    else:
        print("\n\t\tError: Not an Integer\n")

decimalNumber = int(decimalNumber)  # convert the successful user integer into integer type

# tell user what number they entered/formatting
print("\n\t\tYou entered: %d\n\n\t\tConverting to Hexadecimal String...\n\t\t" % decimalNumber)

# create dictionary of conversion between decimal to hexadecimal
conversionValue = {
  0: "0",
  1: "1",
  2: "2",
  3: "3",
  4: "4",
  5: "5",
  6: "6",
  7: "7",
  8: "8",
  9: "9",
  10: "A",
  11: "B",
  12: "C",
  13: "D",
  14: "E",
  15: "F"
}


hexadecimalString = ""  # create empty string to hold hexadecimal string, will need to be reversed
while decimalNumber > 0:
    remainder = decimalNumber % 16  # get the remainder
    hexadecimalString += conversionValue[remainder]  # append the corresponding value on to the hex output string
    decimalNumber = int(decimalNumber / 16)
# actually do the division to lower the decimal number to the new correct value

correctHexadecimalString = "" # create empty string to reverse the current hexadecimal string
for i in hexadecimalString:
    correctHexadecimalString = i + correctHexadecimalString


print("\t\tHexadecimal String: %s" % correctHexadecimalString)  # print out the correct hexadecimal string to user

# end program
print("--------------------------------------------------------------------------------------------------")