# Student Grouping Progam
Authors: Josh and Mat<br>
Developed as PROG1960 Project 2<br>
Highly not recomended to use in any other setting.

Spreadsheet:
https://docs.google.com/spreadsheets/d/1vrPotIOJp3yOAVOMteReJWZpXDEjCI-o6P_Rk3fFPxI

---

# Usage
The primary inputs of the program are two files:

## Parameters.csv
Includes info about working hours, availible rooms.<br>
TODO: support for other parameters: early/late classes preference, etc.<br>

### Example file:
ROOMS,,<br>
Lecture Hall A,Lecture Hall,50<br>
Lecture Hall B,L,170<br>
Computer Lab A,c,50<br>
Tech Lab A,t,50<br>
Sports Hall A,s,50<br>
,,<br>
,,<br>
WORK DAYS,,<br>
MON,8,12<br>
TUE,8,12<br>
THU,8,15<br>
FRI,10,12<br>

---

## Events.csv
Lists all the classes to be scheduled with room requirements, weekly hours, and attendants (instructors and student streams).

### Example file:
AC Repair Theory,5,l,Hameed,CET L1,50<br>
AC Circuits,5,L,Hameed,CET,30,EET,21<br>
AC Circuits,5,Technical Lab,Jane,CET,30,EET,21<br>
Ladders 101,5,C,Professor Professorson,CET,45,,<br>
Naptime,3,S,Reggie,EET,21,,<br>
