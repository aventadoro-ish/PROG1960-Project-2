# Timetable Generator
Authors: Josh and Mat<br>
Developed as PROG1960 Project 2<br>
Highly not recomended to use in any other setting.

---

# Usage
The primary inputs of the program are two files:
- **parameters file** (_.csv_): lists working hours, availible rooms, their type and capacity ![image](https://user-images.githubusercontent.com/81328778/229381020-ac0a34f7-7893-4b6f-9693-33c615954669.png)
- **events file** (_.csv_): lists all the classes to be scheduled with room requirements, weekly hours, and attendants (instructors and student streams) ![image](https://user-images.githubusercontent.com/81328778/229381044-7cc791b4-ab8e-4c6f-b84d-0679513fac92.png)


On program launch, you will be prompted to enter relative paths to parameters file and events file.
You can use included examples from Examples/ folder.

The program will then list events/classes to be scheduled with total number of hours per week and room capacity requirement.
Optinally, you can edit those parameters.
Then you will be asked how many different schedule variants to output.

The **output** is a set of _.csv_ schedule files. <br>
Rows represent timeslots, columns represent classroom.
The intersection is the scheduled event with professors/student streams that attend that event.
![image](https://user-images.githubusercontent.com/81328778/229380983-59f2d320-0da1-4cd3-ba38-2b49fd26bf71.png)

---

