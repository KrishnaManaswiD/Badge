# Instructions

## Assembly
1. Solder all the components.
2. The name tag is laser-cut out of acrylic. Download the file [here](https://github.com/KrishnaManaswiD/Badge/blob/main/files/nameTag.dxf). I engraved the name by hand, using a rotary tool with a ball attachment. I then glued it to the front of the badge.
3. The battery holder is 3D printed and affixed to the back of the badge. The STL file is located [here](https://github.com/KrishnaManaswiD/Badge/blob/main/files/batteryHolder.stl). I printed it on an Anycubic Photon S.  
4. The metallic piece of the [magnetetic clip](https://www.amazon.com/Magnetic-Name-Badge-Holder/s?k=Magnetic+Name+Badge+Holder) is finally glued to the battery holder.

## Powering the badge
The battery holder is designed to hold two CR2032 batteries (3V each) in the circular portion or a small 3.7V LiPo battery in the rectangular section below the metallic piece.
The badge has an onboard regulator that supplies 3.3V to the chips. Connect the batteries using the JST header. **Be sure to check the polarity.**

![The back](https://github.com/KrishnaManaswiD/Badge/blob/main/files/labelledBack.png?raw=true)

## Programming
The board is very similar in design to the [Adafruit Flora](https://www.adafruit.com/product/659). There are a few differences like extra I/O pins and LEDs but you can treat it in a similar manner. To set it up like an Adafruit Flora, you need to burn the correct bootloader. The advantage is that the Arduino IDE recognises the board as a Flora and you can program it through the USB port. The disadvantage is that the additional pin functionality is lost.  

Alternatively, you can treat the board like a programmable chip and write custom code on it through the SPI header.  

Follow the steps below to set it up in whichever way you want. Both methods require the use of a programmer. An Arduino UNO that is set up as an ISP will do fine.

### Convert an Arduino UNO to a programmer
1. Connect a working Arduino UNO to your computer.  
2. Using the Arduino IDE, burn the ArduinoISP sketch from the provided examples.  

Your Arduino UNO is now a programmer. For more details, you can refer [here](https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP)

### Connecting the Arduino UNO to the badge
You will need to connect the SPI headers as shown below.
|   UNO   |  Badge  |
|---------|:-------:|
| Pin 10  |  RESET  |
| Pin 11  |  MOSI   |
| Pin 12  |  MISO   |
| Pin 13  |  SCK    |
| GND     |  GND    |
| 3V3     |  3V3    |

If you are looking at the front of the badge, the SPI header is to the left of the ATMEGA32U4 chip. The pins are as follows. The square pad is the GND pin in my design.   
|  RESET  |   SCK   |  MISO  |
|---------|:-------:|-------:|
| **GND** |**MOSI** |**VCC** |

![The front](https://github.com/KrishnaManaswiD/Badge/blob/main/files/labelledFront.png?raw=true)

Note: You will also need to use a 10µF electrolytic capacitor between RESET and GND on the UNO when using it as a programmer. Connect this only after burning the ArduinoISP sketch.  

Additional note: The VCC pin on the badge pcb is not connected to anything else. To power the board during programming, connect the 3V3 pin on the UNO to the 3v3 pin on the badge (first hole on the bottom left). **Be careful that you are using the 3V3 pin from the UNO and not the 5V pin. The badge only runs at 3.3V. You should also be careful that the connection is stable for the entire duration of the programming and does not dislodge as the badge is being programmed.** Else, you risk bricking the board. You can also try providing power with a battery.  

### Option 1: Burning the Adafruit Flora bootloader to the badge
1. First, make sure you have the relevant bootloader. Install the Adafruit boards to the Arduino IDE by following the isntructions [here](https://learn.adafruit.com/adafruit-arduino-ide-setup/arduino-1-dot-6-x-ide).
2. Connect the UNO to the badge as described in the section above. Double check the 3V3 cable.
3. Under Tools -> Board, choose Adafruit Flora.
4. Under Tools -> Port, choose the port that the UNO is connected to.
5. Under Tools -> Programmer, choose Arduinoo as ISP
6. When you are ready, click on Burn Bootloader in the Tools menu.  

Your board should now be detected as an Adafruit Flora. You might have to install the relevant drivers on Windows. See [here](https://learn.adafruit.com/getting-started-with-flora/windows-setup). You dont need the UNO anymore. Use the badge as if you use a regular Arduino. A ton of Flora related tutorials can be found [here](https://learn.adafruit.com/getting-started-with-flora/flora-projects).

### Option 2: No bootloader. Use an UNO to upload a sketch to the badge each time
1. In the Arduino IDE, open the sketch that you want to write to the badge. A demo code is [here](https://github.com/KrishnaManaswiD/Badge/blob/main/files/demo.ino).
2. Coonect the UNO to the badge as described in the section above. Double check the 3V3 cable. 
3. Under Tools -> Port, choose the port that the UNO is connected to.
4. Under Tools -> Programmer, choose Arduinoo as ISP 
5. When ready, go to Sketch -> Upload using programmer. This will write the sketch to the badge.  

If you disconnect the UNO, connect a battery and turn the badge ON, you should see the sketch running.  
You need to use the UNO, that has been set up as a programmer, each time you want to upload a new sketch.  

## Note to friends who received the badges as a gift
I programmed the board using the second method. It is running the demo code that I linked above.  
The red LED at the top left of the board flashes once as soon as you turn on the badge.  
This is followed by two cycles of the Neopixel running through the colours of the rainbow.  
Finally, the LED on the badge glows to highlight the name.  

![The badge](https://github.com/KrishnaManaswiD/Badge/blob/main/files/frontAnimated.gif?raw=true)

## Addressable LEDs and I/O
1. The red LED in the top left of the badge is on pin 7.
2. The LED above the name tag is on pin 13.
3. The neopixel is on pin 8.
4. I/O pins at the bottom are pins 6, 9, 10 and 12.


## Mistakes in the design
1. On the top silkscreen, the ON side of the power switch is indicated incorrectly. The switch is ON when it is towards the bottom end of the badge and OFF when it is towards the top end.
2. The USB connector needs to be grounded. The pcb does not do it. A simple fix is to solder a 0V resistor between the USB casing and a nearby GND pin.
3. The VCC pin on the SPI header is not connected to anything else. This means that during programming, power must be suplied to the board through the 3v3 pin.
