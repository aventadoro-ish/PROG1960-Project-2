# Student Grouping Progam<br>
Authors: Josh and Mat<br>
Developed as PROG1960 Project 2<br>
Highly not recomended to use in any other setting.

Spreadsheet:
https://docs.google.com/spreadsheets/d/1vrPotIOJp3yOAVOMteReJWZpXDEjCI-o6P_Rk3fFPxI

# Usage<br>
The primary inputs of the program are two files:

## Parameters.csv<br>
Includes info about working hours, availible rooms.<br>
TODO: support for other parameters: early/late classes preference, etc.<br>

### Example file:
ROOMS,,
Lecture Hall A,Lecture Hall,50
Lecture Hall B,L,170
Computer Lab A,c,50
Tech Lab A,t,50
Sports Hall A,s,50
,,
,,
WORK DAYS,,
MON,8,12
TUE,8,12
THU,8,15
FRI,10,12

---

## Events.csv
Lists all the classes to be scheduled with room requirements, weekly hours, and attendants (instructors and student streams).

### Example file:
AC Repair Theory,5,l,Hameed,CET L1,50
AC Circuits,5,L,Hameed,CET,30,EET,21
AC Circuits,5,Technical Lab,Jane,CET,30,EET,21
Ladders 101,5,C,Professor Professorson,CET,45,,
Naptime,3,S,Reggie,EET,21,,
