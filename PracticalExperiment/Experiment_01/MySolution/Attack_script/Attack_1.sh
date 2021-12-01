#!/bin/sh
sudo nmap -sV -Pn -p 1-1024 -v 192.168.56.106 > nmap_out_TCP.txt #This command scans the TCP port in the range from 1 to 1024 on the victim's PC (using his IP 192.168.56.106). 
#Without use the ping and interrogating the port about the service running on it and save the command line output in the file
sudo nmap -sU -Pn -p 1-1024 -v 192.168.56.106 > nmap_out_UDP.txt #This command scans the UDP port in the range from 1 to 1024 on the victim's PC (using his IP 192.168.56.106). 
#Without use the ping and interrogating the port about the service running on it and save the command line output in the file
grep -oE "[0-9]+/(tcp|udp)[ ]*open.*" nmap_out_TCP.txt | grep -oE "[0-9]+" > port_scanning_TCP.txt	# This grep extract the port number from text result in the file.

grep -oE "[0-9]+/(tcp|udp)[ ]*open.*" nmap_out_UDP.txt | grep -oE "[0-9]+" > port_scanning_UDP.txt

input="./port_scanning_UDP.txt"
while IFS= read -r line			#read line by line the input file
do
	./Attack_2_U.sh "$line"		#for each iteration execute Attack_2 with line as parameter. Line contains the port actually attacked.
done < "$input"

input="./port_scanning_TCP.txt"		#read line by line the input file
while IFS= read -r line
do
	./Attack_2_T.sh "$line"		#for each iteration execute Attack_2 with line as parameter. Line contains the port actually attacked.
done < "$input"



