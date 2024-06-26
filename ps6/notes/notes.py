# Notes
#-----------------------------------------#
'''
python is an OOP: variables have functionality in them beyond their values
    s = s.____ instead of s = ___(s)
truncation: when you divide an int by an int, you truncate the remainder (lose it)
    x = 1, y = 3
    x / y = 0.3333 # python converts this to float division
    x // y = 0 # you use // to signify int division
try: return int(____)
except ValueError: print("error, not an integer") # if you mess up instead of crashing it will execute the except clause
print("#", end="") # the end="" signifies to not start a new line after every #, the default is end="\n"
to search a list (names):
    if name in names:
        print("found")
using command line arguments: from sys import argv





'''
#------------------------------------------#
import cowsay
cowsay.cow("Problem set 6 notes")
