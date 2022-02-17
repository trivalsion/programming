# Resources
## Information
- alexgyver.ru
- [Arduino Foundations](https://www.arduino.cc/en/Tutorial/Foundations)
- [Arduino Reference](https://www.arduino.cc/reference/en/)
- Books
	* The Art of Electronics
	* Practical Electronics ed4 - Paul Scherz



## Tutorials
- OSDev
    * [OS for Arduino](https://github.com/rahra/minios)
    * [Arduino QEMU](https://qemu.readthedocs.io/en/latest/system/target-avr.html)
- [Embedded microcontroller tutorial](https://embedded.fm/blog/ese101)
- [Breaking free of Arduino Limitations](https://www.youtube.com/playlist?list=PLCfTdbBFZLXWOjRyKWdliCb-AvCyAP_9l)
- [Arduino Official Tutorials](https://www.arduino.cc/en/Tutorial/HomePage)
- [Using arduino without an IDE](https://wiki.freebsd.org/Arduino)
- [Arduino thread on embedded reddit](https://www.reddit.com/r/embedded/comments/mpdk5z/another_can_i_start_learning_embedded_with_an/?utm_medium=android_app&utm_source=share)
- [Bare metal Arduino programming](https://www.instructables.com/AVR-Programming-with-Arduino-AVRdude-and-AVR-gcc/)




# Notes
## Notes
- Microcontrollers for starters
	* STM32(ARM32)
	* Arduino Nano(AVR8) without IDE, usig only makefiles and text editors
	* ESP32



## Questions
- How to use arduino fully barebones - without IDE, only with compiler, makefile and text editor...?
- What are some cheap AVR boards that could be used without IDE?
- Any microcontrollers cheaper then arduino(not the original but fake ones that are 4-5 or less dollars) or ability to use arduino barebones without IDE and bulit in functions(makefile, programmer, linkerscript, avr-gcc)?
- How to learn using ESP/STM32 or any other microcontroller only with linkerscripts, makefiles and source without an IDE?
- Boards to do practice programming and driver development, not electrical engeneering?
- How do I choose and learn to use a microcontroller programmer(any recommendations of the programmer)?


# Shopping List
* Do not but WAVGAT arduinos
## List
* Proccessing
    * x1 Arduino Nano
    * x2 ATtiny13
        * x1 ATtiny programmer/flasher ------------------- SELECT A CERTAIN MODEL --------------
* Output
    * 1x 1602 Display
        * 1x I2C Display Adapter ------------------ SELECT A CERTAIN MODEL --------------
* Devices
    * x2 RTC ------------------ SELECT A CERTAIN MODEL --------------
    * x1 Beeper Speaker ------------------ SELECT A CERTAIN MODEL --------------
    * x1 74HC595 Output Shift Register
    * x1 74HV165 Input Shift Register
    * x2 EEPROM ------------------ SELECT A CERTAIN MODEL --------------
* Electrical
    * Resistors
        * x100 100 Ohm
        * x100 220 Ohm
        * x100 10 KOhm
    * Capacitor
        * x50 Ceramic 100nF
        * x40 Electrolytic 16V 100-470mF
    * MOSFET
        * x25 2N7000 TO92
    * Diode
        * x25 1N4937
    * Other
        * x10 7805 Linear stabilizers
        * x5 Touch buttons
        * x5 10 KOhm Potentiometer
    * x1 Bread Board



## Devices
### Proccessing
- Arduino Nano


### Output
- LCD 1602
- Beeper(PC-Speaker)


### Input
- External Storage
    + SD Card shield
- Membrane matrix keyboard
- PS/2 Keyboard(PS/2 is easy to use)


### Devices
- RTC
- ATtiny13 - Cheap small microcontroller
- 74HC595 shift register for increasing output port amount
- 74HV165 shift register for increasing input port amount


### EEPROM(R/W from program, data stays on power off)
- EEPROMs - 24 xx xx(e.g. 24LC512)
   * 24 - Uses serial I2C connection
   * xx - The type of model(may be C/CL)
   * xx - Storage size in Kbits. To convert to KB - divide by 8.


### SRAM(R/W from program, data clears on power off)



## Electrical
- Resistors(most common and needed types)
   * 100 Ohm
   * 220 Ohm
   * 10 KOhm
- Capacitors(most common and needed types)
   * Ceramic 100 nF
   * Electrolytic 16V 100-470mF
- MOSFET
   * 2N7000 TO92
- Diode
   * 1N4937
- Linear Stabilizers
   * 7805(lowers to 5V)
- Touch Buttons
- Potentiometer
   * 10 KOhm
- 9v Battery Crown to Barrel-plug adapter
    * https://prom.ua/p653591034-perehodnik-razem-krona.html?
- Wires to Barrel-plug adapter
    * https://prom.ua/p730053227-konnektor-pitaniya-papa.html?
- Wires 0,25-0,35mm
- Bread Board



## Questions
* Are the 24<C/LC><*>-`24xxxx`(e.g. 24C128) EEPROMS the same?
    * What is the difference between C and LC models?
    * What does 24 mean and are there better chips and in what?
* What are the EEPROMS that are recommended to buy to be easy to use?
* Can I extend the RAM of the arduino with external SRAM chips, which to buy?
* Which chip should i start learning embedded programming from(barebones without IDE - only make files)?



## Tutorials
* EEPROM
   * 24LC512
      * https://www.youtube.com/watch?v=DQQJGCixgvU
      * https://www.hackster.io/techmirtz reading-and-writing-data-to-external-eeprom-using-arduino-670dd8
      * https://www.instructables.com/Reading-and-Writing-Data-to-External-EEPROM-Using-/
   * 24LC256
      * https://www.youtube.com/watch?v=ShqvATqXA7g
      * https://www.youtube.com/watch?v=Ejrh1vNeDhA
      * https://www.circuitbasics.com/how-to-use-eeprom-on-the-arduino/
   * 24C128
      * https://www.youtube.com/watch?v=ZSH5nZn8cf4
   * 24LC64
      * https://www.youtube.com/watch?v=phgSPxESXqs



## Learn
* Using interrupts on arduino
    * Build your own interrupt controller(out of a cheaper micro controller such as ATtiny)