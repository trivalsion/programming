# Starting programming project proccess
1. Create a README.md explaining the purpose, build instructions and small usage instructions
	* [README Template](project_example/README.md)
2. Create a plan.md to plan out the project, the plan.md should contain:
	* `To Do` section - containing bullet pointds for things that are needed to be done in the project
	* `Features` - section which contains features of the project
		* `Not implemented` - features that aren't implemented yet
		* `Implemented` - features that work already
	* `Software Architecture` section - that explains how the project's code architecture works
	* `Resources` section - that contains links to different resources on topic of the project like guides, books or documentation
	* [plan.md example](project_example/plan.md)
		* [plan.md implementation](../../programs/nsh/plan.md)
3. Create a proper directory layout - different parts of code should go into different folders and non-code stuff should go into other folders(e.g. binaries should go into build dir)
	* Put output binaries into `build` folder
	* Put global include files into `include` folder in the root of the project
	* Put local include files into `include` folder in the directory it is local to(e.g. project-root/parser directory)
	* Put the main parts of the program into the `core` directory
5. Start coding the project and placing the source code files, include files and global include files in the right directories
6. Create a build system to build the program(with utilities like GNU Make)
	* [Advanced build system](Makefile)
		* [Advanced build system implementation example](project_example)(makefiles could just be copied over from the example to the project(root makefile contents to root makefiles and submakefiles' contents to submakefiles, then just rename some parts of variables and change them a bit to adapt to the project
7. Create a code API(function calls) so different parts of the program can properly talk with each other, implement API as series of global function implemented in code in different parts of the program, the prototypes of these functions should be present in the global header files located in the `include` folder in the root of the project
8. Create a proper error reporting system so that when some function in the program returns some error status, the error is reported using a special function declared in global header that would print out the error message and this function should be used in all instances when an error message should be printed out so the error reporting system is standardized and all of the errors could be redirected anywhere(e.g. stdout, file, network...) - e.g. outputError() function
9. Create a proper debugging system so that debug messages and functions could be disabled when the program is compiled for release, also all debug messages should be printed by one special debug outputting function declared in the global header to be standardized and global for all of the code
10. Create a proper automated testing system so that the program could be checked for bugs after changes. It could be implemented with scripts, makefile or special software
11. Create [documentation](documenting.md)


# Managing
* While doing the project split each big task into smaller steps and add them to todo section of plan.md or any other planner
* Fill the plan.md `Resources` or other documents in the project folder with the information and resources gathered on the topic of the project
* Create a copyright section in README.md or even make it into a seperate file and put links to original and copyright strings(e.g. Copyright (c) 2020 Some Name) of other people's source code that is used in the programming project(if it is used)


# C Specific
* Make sure that the executable does not have any memory leaks and all of the memory is freed by using `valgrind` which shows multiple memory problems including leaks and gives information(including the line) about where the problems have occured
	* Make sure to compile programs with `-g` flag before runnning them in valgrind so that valgrind could get all of the information about the executable
	* To get all memory problems that the program has use `valgrind --leak-check=full --show-leak-kinds=all exe`, and make sure to remove all of the memory errors
		* **!!!!!!!!!** Do not try to fix the `HEAP/LEAK SUMMARY` and `still reachable` problems if they pop up during programs execution(as they probably aren't leaks), only fix the `still reachable` problems which are still there at exit(the heap summary and problems list which are sill present at exit is printed at exit when the program finishes(e.g. quits with exit or returns))
			* **!!!!!!!!!** But fix ALL of the problems if they are printed when `--leak-check=full --show-leak-kinds=all` isn't used(isn't supplied to valgrind)
	* Make sure that after exit and at all points in the program there is not only no memory errors but `LEAK SUMMARY` is just zeroses meaning that nothing has been leaked
* Compiler should have the `-Wmissing-prototypes` flag supplied to it when compiling EACH of the .c files to make sure all non-static functions have a prototype in the header file
* Functions and global variables specific to some c file should be declared as static
* All headers SHOULD have header guards
	* 	```c
		#ifndef <HEADER_NAME_<GLOBAL/LOCAL>>
		#define <HEADER_NAME_<GLOBAL/LOCAL>>
		/* code */
		#endif
		```
