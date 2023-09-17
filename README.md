# 11COMA_UNIT2_AOS1_SAC

Overview of Task:

Groups of 2-4 students will collaborate to document the planning, analysis, design, development and evaluation of their chosen innovative digital solution.

Each group must develop a solution to a different identified need.

They will also present their innovative solution in the form of a class presentation, video or poster. 

This task covers the key knowledge and skill for Unit 2.1 which are displayed on the Innovative Solutions course page.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Our group must create an emerging technology with the use of varying software and hardware components. The system must be complete by the 12th of September.​

​

Goal​:

Create an app ​

Objectives​:

Saves data to a database​

Loads data from a database​

Displays data from data base in a easy-to-use manner​

Read data from csv file that was created by hardware​

​

This goal relates to the identified need to create an app that displays data from the related emerging hardware technology. Stated objectives reflect component that the app should have.


Goal​:

Create a smart toothbrush​

Objectives​:

Prototype screen feature of the toothbrush​

Prototype data collection​

Prototype wireless sending of data​

Prototype speaker to play sound for the user​

Allow for data collected to be saved in a CSV file​

​

This goal relates to the identified need of conceptualising hardware componentry to create a system evolving technology considered emerging. Stated objectives reflect components and functions that should be implemented into the solution.​

------------------------------------------------

The first hardware prototype that has been created is a concept for collecting, transmitting, formatting and storing data collected. This prototype utilizes two ESP32 microcomputers with one being used as a data collector and transmitter and the other being used as the base and receiver. As a proof of concept, currently the transmitter is only collecting temperature data using an BMP280. However, the methodology of storing and sending data structures would be the same with more appropriate sensors.

The transmitter sends its defined device name and a float of its data reading, which it sends to the other ESP32 using the ESP-NOW wireless communication protocol. Then the receiving ESP32 uses "Ardu Spreadsheet", also known as ArduS, which is a third-party Arduino IDE tool to take data printed to the serial monitor and store it in a CSV file which is then imported into the Plaque Pounder app. 

The Second hardware concept that has been created is a prototype of the digital display and speaker that would be used on or in the Toothbrush. This prototype utilizes an Arduino Nano microcomputer to compute and process the actions of input and output devices such as two buttons for commencing brushing, as well as the second button being used to change the display functionality mode display other additional information to the user such as battery life and brush duration. The speaker plays an enlightening tone at the start and end of a brushing sequence.
