# Instructions

The board is very similar in design to the [Adafruit Flora](https://www.adafruit.com/product/659). There are a few differences like extra I/O pins and LEDs but you can treat it in a similar manner. To set it up like an Adafruit Flora, you need to burn the correct bootloader. The advantage is that the Arduino IDE recognises the board as a Flora and you can program it through the USB port. The disadvantage is that the additional pin functionality is lost.  

Alternatively, you can treat the board like a programmable chip and write custom code on it through the SPI header.  

Follow the steps below to set it up in whichever way you want. Both methods require the use of a programmer. An Arduino UNO that is set up as an ISP will do fine.

## Convert an Arduino UNO to a programmer
1. Connect a working Arduino UNO to your computer.  
2. Using the Arduino IDE, burn the ArduinoISP sketch from the provided examples.  

Your Arduino UNO is now a programmer. For more details, you can refer [here](https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP)

## Connecting the Arduino UNO to the badge
You will need to connect the SPI headers as shown below.
|   UNO   |  Badge  |
|---------|:-------:|
| Pin 10  |  RESET  |
| Pin 11  |  MOSI   |
| Pin 12  |  MISO   |
| Pin 13  |  SCK    |
| GND     |  GND    |
| 3V3     |  3V3    |

If you are looking at the front of the badge, the SPI header is to the left of the ATMEGA32U4 chip. The pins are as follows.  
|  RESET  |   SCK   |  MISO  |
|---------|:-------:|-------:|
| **GND** |**MOSI** |**VCC** |

Note: You will also need to use a 10µF electrolytic capacitor between RESET and GND on the UNO. Connect this only after burning the ArduinoISP sketch.  

Additional note: The VCC pin on the badge pcb is not connected to anything else. To power the board during programming, connect the 3V3 pin on the UNO to the 3v3 pin on the badge (first hole on the bottom left). Be careful that you are using the 3V3 pin from the UNO and not the 5V pin. The badge only runs ar 3V3. You should also be careful that the connection is stable for the entire duration of the programming and does not dislodge as the badge is being programmed. You risk bricking the board.  

You can also try providing power with a battery.  

## Option 1: Burning the Adafruit Flora bootloader to the badge
1. First, make sure you have the relevant bootloader. Install the Adafruit boards to the Arduino IDE by following the isntructions [here](https://learn.adafruit.com/adafruit-arduino-ide-setup/arduino-1-dot-6-x-ide).
2. Connect the UNO to the badge as described in the section above. Double check the 3V3 cable.
3. Under Tools -> Board, choose Adafruit Flora.
4. Under Tools -> Port, choose the port that the UNO is connected to.
5. Under Tools -> Programmer, choose Arduinoo as ISP
6. When you are ready, click on Burn Bootloader in the Tools menu.  

Your board should now be detected as an Adafruit Flora. You might have to install the relevant drivers on Windows. See [here](https://learn.adafruit.com/getting-started-with-flora/windows-setup). You dont need the UNO anymore. Use the badge as if you use a regular Arduino. A ton of Flora related tutorials can be found [here](https://learn.adafruit.com/getting-started-with-flora/flora-projects).

## Option 2: No bootloader. Use an UNO to upload a sketch to the badge each time
1. In the Arduino IDE, open the sketch that you want to write to the badge. An example is [here](https://github.com/KrishnaManaswiD/Badge/blob/main/docs/demo.ino).
2. Coonect the UNO to the badge as described in the section above. Double check the 3V3 cable. 
3. Under Tools -> Port, choose the port that the UNO is connected to.
4. Under Tools -> Programmer, choose Arduinoo as ISP 
5. When ready, go to Sketch -> Upload using programmer. This will write the sketch to the badge.  

If you disconnect the UNO, connect a battery and turn the badge ON, you should see the sketch running.  
You need to use the UNO, that has been set up as a programmer, each time you want to upload a new sketch.  

## Powering the badge
I designed a battery holder to affix to the back of the badge. The STL file is located here. I printed it on an Anycubic Photon S.  
This holder is designed to hold two CR2032 batteries in the circular portion or a small LiPo battery in the rectangular section beside the magnetic piece.  
The badge has an onboard regulator that supplies 3.3V to the chips.  
Connect the batteries using the JST header.  

## Note to friends who received the badges as a gift
I programmed the board using the second method. It is running the example code that I linked above.  
The red LED at the top left of the board flashes once as soon as you turn on the badge.  
This is followed by two cycles of the Neopixel running through the colours of the rainbow.  
Finally, the LED on the badge glows to highlight the name.  
