#Developed by:
#- Matteo Di Fabio 264339
#- Luca Genovese 264364
#Note: due to the use of tshark, our program has a dependencies, please install tshark with the following command: sudo apt-get install -y tshark
import os
import sys

if (len(sys.argv)!=3):
  print("Pass the correct number of parameters please")
  exit(1)

if sys.argv[1]!='-r':
  print("Insert a valid option: -r")
  exit(1)

x = "tshark -nr " + sys.argv[2] +  " --export-objects http,temp > capture.txt"
os.system(x)
#os.system("tshark -nr traffic1.pcap --export-objects http,temp")
#tshark -nr INPUT_FILE --export-objects http,OUTPUT_DIRECTORY