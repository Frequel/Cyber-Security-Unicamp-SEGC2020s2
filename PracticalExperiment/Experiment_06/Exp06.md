#Computer Security - Data injection
One of the parts of the Mitnick vs Shimomura attack consisted of sending traffic packets forging a trusted source.

This task's goal is to develop an injector package in Python (use Scapy) and use it as follows:
1. Perform a file transmission in plain text between two computers with the protocol of your choice (might be FTP, netcat or any other tool/protocol).
2. Observe the transmission and check that there is a pattern in the sequence numbers.
3. Try to inject packets with the program developed during transmission of the file in order to modify its content, thus modifying the transmitted file.
In addition to developing the injector, each group must write a report describing in detail all procedures performed, the environment used, how the injection was made​​ and what happened during the attack.

The report must contain the impressions of the group on the process carried out, a discussion about which of the packages has been accepted---forged or legitimate---and why it occurred.

##Recommendations
- Studying TCP/IP references to remedy any problems or questions related to reception window, generation and calculation of sequence numbers and packet handling (e.g. overlapping of TCP segments).
- Recommended References: TCP/IP Illustrated Vol. 1 (Stevens), Computer Networks (Tanenbaum), Computer Networking (Kurose & Ross), RFCs.
- Recommended article: A Simple Active Attack Against TCP.

##Please note:
- The program should be done in Python.
- It is recommended the use of two virtual machines for file transmission and a third machine for packet injection (might be the host or another virtual machine).
- The file to be transferred is at this link.
- The injector package developed by the group will be tested in an Ubuntu Linux virtualized environment with the most recent VirtualBox.
- The program should compile correctly at the time of grading. Failing to do that will yield a 0 (Zero) in the experiment.

##Report writing and delivery of results
The group must submit:
- A 6-page report (pdf) describing the development process for the program and the test phase, types of attacks linked to the injector packages and countermeasures.
- Injector packages code.