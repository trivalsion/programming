# nSH Shell
nSH is a shell written in c



## Informations
### Description
nSH is a an independent shell and it's following of the POSIX standard is very loose so it is mostly not POSIX compatible


### Features
* No old POSIX standards
* Support for several of parts of the POSIX standard, these are:
	* Environment variables: several default environment variables are present, method of interaction and existance of env vars is the same as in POSIX shells
	* Output redirection using `<</>> >\<`
	* Starting background proccess by putting `&` after the command
	* Logic operators: `||`, `&&`
	* Builtin commands: echo, cd, help
	* Splitting one command into several lines using `/`
	* To execute an executable from current working direcotry, use `./` before it(e.g. `./ls`)


### Documentation
* [Full nSH Documentation(may be incomplete)](documentation.md)



## Building nSH
*NOTE: These are the instructions that were only tested on Debian based systems(e.g. Debian, Ubuntu) and RHEL based systems(e.g. Fedora)*


### Setup
Get ready for the build by getting source code and going to the directory with code

```
git clone https://github.com/programming
cd programming/programs/nsh/
```


### Build and Run
Compile defualt configuration
```
make
```
To change make configuration, read the build system section in [documentation](documentation.md#build-system)



## Usage


## Copyright