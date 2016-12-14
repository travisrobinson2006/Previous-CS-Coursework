#Travis Robinson
#CS344
#Program 5

#imports
import random
import string
import sys
from random import randint

#for loops to generate 3 files, each with random lowercase chars in it
for i in range (0,3):
	fo = open('Travis_Robinson_mypython_file_'+str(i),'w')
	for x in range(0,10):
		random_char = random.choice(string.ascii_lowercase)
		sys.stdout.write(random_char)
		fo.write(random_char)
	fo.write('\n')#print new line at end of file for readability when cating out
	fo.close()
	sys.stdout.write('\n')#write new line to terminal for readability
#generate random numbers
random_int_1 = randint(1,42)
random_int_2 = randint(1,42)

print(random_int_1)
print(random_int_2)

random_int_1 = random_int_1*random_int_2
print(random_int_1)

