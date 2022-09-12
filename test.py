import sys
import random as rand

if len(sys.argv) == 2:
    n = int(sys.argv[1])
else:    
    n = int(input(" > Choose size of test dataset: "))
File = open("test.txt", "w")
alphabet = 'qwertyuiopasdfghjklzxcvbnm'

for j in range(n):
    s = ''
    for i in range(5): s += rand.choice(alphabet)   
    File.write(f"{s} {rand.randint(0,n*10)} {s}@server.com\n")
    

