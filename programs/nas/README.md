# nAS Assembler
nAS is an assembler written in C



## Informations
### Description
nAS is an assembler that is made to be modular so it could be edited and compiled for multiple differe target architectures. All architecutre specific parts are seperated from the other parts of the OS by a function interface.


### Supported Assembly languages
* CHIP8 assembly
* 6502 assembly(To be implemented)
* PDP11(To be implemented)
* msp430(To be implemented)
* thumb without thumb2 extensions(To be implemented)


### Documentation
* [Full nAS Documentation(may be incomplete)](documentation.md)



## Building nAS
*NOTE: These are the instructions that were only tested on Debian based systems(e.g. Debian, Ubuntu) and RHEL based systems(e.g. Fedora)*


### Setup
Get ready for the build by getting source code and going to the directory with code

```
git clone https://github.com/programming
cd programming/programs/nas/
```


### Build and Run
Compile defualt configuration
```
make
```
To change make configuration, read the build system section in [documentation](documentation.md#build-system)



## Usage
```
Usage: nas [option] file ...
Options:
	-v	--version	Prints out current version of the program and exits
	-h	--help		Prints out this help message and exits
```



## Copyright
* Credits for the CHIP-8 emulator
	* [Copyright (c) 2020 David Matlack](https://github.com/dmatlack/chip8)
		* [Chip8 emulator](arch/chip8/chip8emu)
		* [Test program(not a complete copy, but a rewrite)](test/test-program.s)
