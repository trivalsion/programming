# Programming
Programming Projects and Notes




# Project ideas
* ***Bold + Italic Text*** - Best Project Ideas
* `(Language: Language)` - Best/Recommended language to do the project in
## Networking
- ***Network updater of programs***`(Language: C)`
	* Downoads an update of latest version of an application(binaries and config files) to update the current version
- Remote shell(e.g. ssh)`(Language: C)`
- Peer-to-Peer network messenger(plan.md in notes-repo/programming/)`(Language: C)`


## UNIX System Programming
- FUSE filesystem`(Language: C)`
- Window manager(e.g. i3, OpenBox, XMonad)`(Language: C)`
- Re-Implement TCP/IP protocol stack`(Language: C)`
- Memory editor(e.g. like CheatEngine or Scanmem/GameConqueror - attach to other programs and read and modify their memory)`(Language: C)`


## Utilities
- Text editor`(Language: C)`
	* [Tutorial - The Craft of Text Editing](https://www.finseth.com/craft/)
- File manager`(Language: Python)`
- ***Device Manager - like windows device manager, but for linux/bsd(unix)***`(Recommended Language: C)`

### Multimedia
- Audio Player`(Language: Python)`
- Image Viewer`(Language: Python)`
- Video Player`(Language: Python)`


## Low-Level/Hardware
- Device Drivers(BSD, Linux)`(Language: C)`
- RAM disk - make RAM emulate a disk(block device like sdX)`(Language: C)`
- Hardware emulator(e.g. x86 or arm emulator)`(Language: C)`
	* IBM PC Emualtor with ability to add hardware through expansion slots(during compilaion)


## 3D
- 3D physical simulation(e.g. water simulation)`(Language: Python)`
- 3D Game without using a game engine, only using low-level APIs like OpenGL or Vulkan(or libraries like SDL2)`(Language: Python/C)`
- ***3D Renderer***`(Language: Python)`
	* [Example - Toy Renderer](https://momentsingraphics.de/)
- Raytracer`(Language: Python)`
	* [Example - Ray Tracing in One Weekend](https://raytracing.github.io/)
	* [Example - C Raytracer](https://github.com/wojciech-graj/C-Raytracer)
- 3D Game Engine`(Language: C+Python)`
- Contribute to an open-source 3D game`(Language: C+Python)`
	* Add modding capabilities by adding a lisp interpreter
	* Add an in-game command line


## Tools
- C compiler`(Language: C)`
- Linker`(Language: C)`
- Coreutils - unix core utilities e.g. ls`(Language: C)`


## Other
- AI
	* Computer Vision(Recognizing Stuff on Photos and Videos)`(Language: Python)`
		* OpenCV Library could be used
- SQL-compatible database`(Language: C)`
	* Also it can be an in-Memory Database(e.g. Redis) or support working in that mode
- LISP interpreter`(Language: C/Python)`
- Small reimplementation of C standard library`(Recommended Language: C)`
	* Also userspace memory allocator(e.g. malloc)


## Systems
- Payment system - secure trasnfer and proccessing of transaction data through the network and that can be easily repurposed to supporting data types other than financial transactions`(Language: C/Python)`
	* Can be tested by simulating transactions and user requests to the bank
- ***Inventory Management System***
	* With networking capabilities
	* Supporting multiple users with different priviledge/access levels


## Finished projects
- eFAX(DONE) - network file sender
- Assembler(DONE) - turns assembly code into CPU understandable instruction
- Command Line Shell(DONE) - interprets the commands entered by the user and executes them
- Create a library with functions common accross multiple personal coding projects(e.g. outputError function)`(Language: C)`(DONE)


## Project idea collections
### Links
* Best
	* [GNU software](https://www.gnu.org/software/software.html#allgnupkgs)
		* [List of GNU packages documentation by categories(When going to a project in documentation list press on the "[<project name> home]" link right after package description to go packages home page instead of directly going to it's manual)](https://www.gnu.org/manual/manual.html)
	* [42 Practice Projects - itnext.io](https://itnext.io/42-projects-to-practice-programming-skills-6f5acc10fec0)
	* [C Projects - Github](https://github.com/rby90/project-based-tutorials-in-c)

* [Learn Programming subreddit FAQ](https://www.reddit.com/r/learnprogramming/wiki/faq?utm_source=share&utm_medium=ios_app&utm_name=iossmf#wiki_where_can_i_find_practice_exercises_and_project_ideas.3F)
* [Projects from Scratch - Github](https://github.com/AlgoryL/Projects-from-Scratch)
* [Build your own X - Github](https://github.com/danistefanovic/build-your-own-x)
* [Mega Project List - Github](https://github.com/karan/Projects)
* [C Projects - codewithc.com](https://www.codewithc.com/category/projects/c-projects/)
* [1000 Networking Projects - 1000projects.com](https://1000projects.org/projects/networking-projects)
* [Programming Projects v1.4 - Github](https://github.com/desolt/pro-g-ramming-challenges)
* [Programming Projects v2.0 - Github](https://github.com/Agrendalath/Programming-Challenges-v2.0)
* [Codeabbey - programming projects collection](https://www.codeabbey.com/)
* [Project Euler - Harsh math problems programming projects](https://projecteuler.net/)




# Open-sorce projects with code that is understandable, clean and easy to read
- SQLite - relational, program embedded(not a client-server) database engine(in C)
- IDTech game engines
	* Doom 1(Both original and community improved code version)(in C)
	* Quake 3(Both original and community improved code version)(in C)
- Redis - in-Memory Database(in C)
- BSD - OS(in C)
	* OpenBSD(Secutity based, clean, in C)
	* NetBSD(Portablly written code, in C)
	* FreeBSD(Most documented, supported and widely used, in C)
- Linux - Kernel(in C)
- RTOSs
	* **Zephyr RTOS** - by Linux Foundation, comlete reature set, includes drivers(in C)
	* **freeRTOS** - small, fast, only thread switching functionality(in C)
	* **NuttX** - by Apache(in C)
- **GNU Nano** - Text editor(in C)
- [Open-Source contribution finder]](https://www.codetriage.com/?language=C)
- [Open-Source project finder](https://awesomeopensource.com/projects/c)




# Tool collection
* Make - build system
* Git - version control system
* GCC(C Compiler), LD(Linker), GNU AS(Assembler), GDB(Debugger) - GNU programming toolchain
* Clang(C Compiler), LLD(Linker), LLVM(Multiple tools) - LLVM programming toolchain
* Valgrind - memory leakage analyzer
* QEMU - emulator(emulates different platforms)
* [Draw.io - open-source diagram drawing software](https://www.diagrams.net/)
