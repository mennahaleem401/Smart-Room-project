# Smart room with Arduino
I will demonstrate how to create a smart room using Arduino and sensors in this repository.
# Overview of smart room
It is a room built using Arduino and contains a set of
 sensors that:
 
1- Count the Number of people inside it.

2- Measure the Temperature. 

3- Measure the value of gas.

# Hardware used: 
1- Arduino nano

2- 2 IR sensors

3- jumpers

4- MQ-2 Gas sensor

5- Buzzer

6- tmp35 Temperature sensor

7-2 Pushbuttons

8- 2 LEDS

9- potentiometer

10- Resistors
(4 of 220ohm,1 of 330ohm,3 of 1kohm)

11- LCD 
(Liquid-crystal display)
# Hardware Connections 
![Screenshot 2024-03-01 144028](https://github.com/mennahaleem401/Smart-Room-project/assets/120136580/27ed5505-2f1a-4082-a934-0ba03e743818)


# Code:
1. Definition and Initialization

The first step is to write the LCD library, define the Arduino pins, and identify the variables that are used in the code.

I have created some functions :
 1- Check the gas function 

  We are using an MQ-2 Gas sensor to measure the percentage of gas present in a room. The readings of the gas sensor are stored in a variable named read_gas. If the reading is greater than or equal to 150 degrees, the buzzer will receive a high-voltage signal, otherwise, it will receive a low-voltage signal.

  2- Check Temperature 
  
we are using a tmp35 sensor to measure the temperature in the room, store the reading of it, and make it from range 0…1023 to 0…5000 and check if this temperature is greater than or equal to 100 turn on the red LED else turns off.
At the end of this function call the lcd_show() function to show this reading in it.

3- Check the  2 ir sensor

1- Check the out_ir sensor

 we are using an out_ir sensor to detect if the person wants to enter the room or wants to exit the room.
First, we put the check variable, in the flag and out flag equal zero which out flag refers to the person standing outside and wanting to enter the room, the in flag refers to the person standing inside and wanting to exit the room and the check variable refer to if the ir detect a person or not.
We first check if the check=1&& the flag in=1 this means this person exits the room, else he wants to enter so put check =1 and out =1.

2- Check the out_ir sensor

we are using the in_ir sensor to detect also if the person wants to enter the room or wants to exit the room.
We first check if the check=1&& the flag out=1 this means this person enters the room, else he wants to exit so put check =1 and in =1…
At the end of this function, we call the lcd_show() function to show the number of people in the room.

4- Control of white LED and LCD by Buttons

These two buttons are connected as one button we use this method to minimize the number of used digital pins.
We take the reading of the button and wait 10 milliseconds to avoid the bouncing problem and if read_btn =487 so will increase the cnt variable to show the reading the user wants and call the lcd_show() function else if read_btn =738 reverse the reading of the LED…

5- Showing in LCD:

In this function, we show the number of people, percentage of Gas sensors, and Temperature sensors based on the press of a button…

Challenge we faced 

We faced a challenge with LCD when changing the reading in it from high reading to low reading will output a false result 

How to solve it 

The first solution is using the clear function but when used there is blurry vision.
 so we used the second solution which calculates the highest number will output and clear this by empty spaces instead of using the clear function…
