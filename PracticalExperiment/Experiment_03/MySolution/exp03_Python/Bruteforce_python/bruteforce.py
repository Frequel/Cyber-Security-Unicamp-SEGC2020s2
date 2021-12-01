#Developed By Matteo Di Fabio 264339 and Luca Genovese 264364
from zipfile import  ZipFile
import sys
import ntpath

if (len(sys.argv)!=5):
  print("Pass the correct number of parameters please")
  exit(1)

if sys.argv[1]!='-l':
  print("Insert a valid option: -l")
  exit(1)
elif(sys.argv[3]!='-f'):
  print("Insert a valid option: -f")
  exit(1)

my_path=sys.argv[2]
zip_file=sys.argv[4]

found=False
error=False
try:
  with open(my_path, "r") as fp:
    while True:
      my_password=(fp.readline())
      # If the result is an empty string
      if my_password == '':
        # We have reached the end of the file
        break
      my_password=my_password.rstrip()
      #if not empty open the zip

      try:
        with ZipFile(zip_file) as zf:
          
          try:
            zf.extractall(pwd=bytes(my_password, 'utf-8'))
            print("Found password: {}".format(my_password))
            found = True
            break
          except RuntimeError:
            pass
      except FileNotFoundError:
        print("Error in the zip file opening")
        error=True
        break

  fp.close()
except FileNotFoundError:
  error=True
  print("Error in the password list file opening")
if (found==False and error==False):
  print("No password found in password list file. Bruteforce attack failed.")
