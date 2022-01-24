# Cheatsheet
* [GNU C Manual](https://www.gnu.org/software/gnu-c-manual/)
* [C Cheatsheet](https://developerinsider.co/c-programming-language-cheat-sheet/)
* `<var_name>` - just the name of var(e.g. `int <var_name>` = `int location`)
* `<type>` - any type from [Data types and data classes](#data-types-and-data-classes)


# Info
* `<code>` - Any C code
* `<condition>` - some statement which evaluates to either `true/1` or `false/0`, for example - `i == 8`, `i < 6`, `i != 1`


## 1. Variables
* Declaring variables - `<type> var_name;`, e.g. `int var_name;`
* Assigning variables at the time of declaration - `<type> var_name = value;`
* Using several types when declaring - `const int var;`


## 2. Conditionals
### If
* **`Description`** - `if` executes `<code>` if the `<condition>` is true(evaluates to `1/True` in terms of C)
```c
if (<condition>)
{
    <code>
}
else if (<condition>)
{
	<code>
}
else
	<code>
```

### Switch
* **`Description`** - if the `<var_value>` of some case is equal(==) to the value of `<var>`, then `<code>` under the case is executed, including code of other cases, so to stop exection of code after the cases code use `break` keyword like in loops; `default` is a case that executes if all other cases are not evaluated to true
* `<var>` example - `i` which was declrared before as `int i;` or `j` as`size_t j;`...
```C
switch(<var>)
{
    case var_value:
        <code>

    case var_value:
    case var_value:
        <code>
		break;

    default:
        <code>
}
```


## 3. Loops
* `break` - stops the loop and continues to execute code but after the loop(continues to execute the code that is after the {} block of code after the loop or if there is no {} then executes the code after the first statement after the loop)
* `continue` - starts a new iteration of the loop
### While
* **`Description`** - `while` executes `<code>` while the `<condition>` evaluates to `1/True` or until it encounters a `break`
```C
while (<condition>)
{
    <code>
    break;
    continue;
}
```

### For
* **`Description`** - `for` executes `<code>` while the `<condition>` evaluates to `1/True` or until it encounters a `break`. But unlike `while`, the `for` also executes `<incrementation>` statement after each loop iteration and executes `<init>` statement before the start of first loop iteration
* `init` - statements here are executed once when the loop starts, the statements that could be written here are only: variable assignment, variable declaration or variable assignment and declaration at the same time(e.g. `int i = 0`). There could be multiple declaration(in case there are multiple declaration, all of them should be of the same type(e.g. `int`)) or assignment statements seperated with commas(e.g. `int i, j = 0`)
* `condition` - loop continues while it is true(e.g. `i == 8`)
* `incrementation` - is executed each loop iteration, the statements that could be written here are only: variable assignment or most commonly used one - incrementation(e.g. `i++`). There could be multiple incrementation or assignment statements seperated with commas(i++, j++)
```c
for (<init>; <condition>; <incrementation>)
{
    <code>
	break;
	continue;
}
```


## 4. Functions
* **`Description`** -
* Declaring a function
	*	```c
			<type> name(<type> args, <type> name) // example "int name(int args, char arg)"
			{
				<code>
				return type_value; // return value of the same size as the type that the function was declared with
			}
		```
* Calling the function `name(args);`, e.g. `name(8)`


## 5. Pointers
* Getting the address of a variable - `&`, e.g. `&var_name`
* Accessing the value of address in a variable - `*`, e.g. `*var_name`, `*var_name = 5`
* Declaring pointers
	* `<type> *var_name;`
	* `<type> *var_name = &var`
* There may be multiple pointer levels - `<type> **var_name;`, `<type> *****var_name;`


## 6. Data types and data classes used during variable and function declarations
* `int <var_name>;`
* `char <var_name>;`
* `float <var_name>;`
* `double <var_name>;`
* `short <var_name>;`
* `long <var_name>;`

* `unsigned <type> <var_name>;`
* `signed <type> <var_name>;`

* `volatile <type> <var_name>;`
* `extern <type> <var_name>;`

* `auto <type> <var_name>;`
* `register <type> <var_name>;`
* `static <type> <var_name>;`
* `void <var_name>;`
* `inline <type> <var_name>;`


## 7. Preproccessor
* Including a file from global dirs(e.g. /usr/include) - `#include <file.h>`
* Including a file from local directory - `#include "file.h"`

* Macro names are changed with values by compiler before compilation - `#define MACRO-NAME value`, e.g. `#define MACRO-NAME 8`
	* Macro usage example - `int i = MACRO-NAME;`


## 8. Arrays and strings
* Declaring an array - `<type> name[index];`
* Assigning the array - `<type> name[index] = {el, el, el};`

* Using array members - `name[index]`
* Assigning array members - `name[index] = value;`

* `Using pointers` - `&name[1] + 1 = &name[2]`

* Declarign strings - `char name[index] = "string"`
	* Using strings without arrays - `"strings"`


## 9. Struct
* Declaring
	*	```c
			struct name
			{
   				<type> var;
    			struct name el;
    		}
		```

* Declaring variables of some struct type - `struct name el, el;`
* Assigning structure vars at declaration - `struct name el = {"var1_value", "var2_value"};`
* Making a struct array - `struct name[index];`

* Using struct members - `el.var`
* Assigning struct members - `el.var = value;`


## 10. Union - When several different data typs use one memory space - memory space chosen based on biggest size, if one variable is changed - same bits are changed in others
* Declaring
	*	```c
			union name
			{
				<type> var1;
				<type> var2;
			};
			union name var;
		```
* Using the union members - `var.var1`
* Assigning union members - `var.var1 = value;`


## 11. Typedef - Allows you to make your own variable type from existing ones
* Creating a new type - `typedef <type> new_type_name;`
	* Example - `typedef struct name new_type_name`
* Using a new type - `new_type_name var;`


## 12. Enum - This is a type declaration which consists of constant integer values, if constants are not declared, they take their value based on their position e.g 1st 2nd
* Declaring
	*	```c
			enum enum_type {
				var1-name,
				var2-name = value,
				var3-name
			};
			enum enum_type el;
		```
* Assigning enum var - `el = var1;`
* Using enum vars - `var1-name + 1 = var2-name`


## 13. Typecasting - changes the size and signdness of the thing being converted to the type it is converted to, but the changes only happen for the instruction where casting is used
* Examples
	* `var_name = (type)var_name / var_name;`
	* `if ((type)var_name == 8)`


## 14. Operators in order of evaluation/importance
* Postfix			- `() [] -> . ++ - -`
* Unary				- `+ - ! ~ ++ - - (type)* & sizeof`
* Multiplicative	- `* / %`
* Additive			- `+ -`
* Shift				- `<< >>`
* Relational		- `< <= > >=`
* Equality			- `== !=`
* Bitwise AND		- `&`
* Bitwise XOR		- `^`
* Bitwise OR		- `|`
* Logical AND		- `&&`
* Logical OR		- `||`
* Conditional		- `?:`
* Assignment		- `= += -= *= /= %=>>= <<= &= ^= |=`
* Comma				- `,`




# Features
## Number systems
### Any number in any case(e.g. declaration, list index or memory address) can be represented in any of number systems supported by C
* Decimal - requires no prefix = (e.g. `76`)
* Hexadecimal - requires `0x` prefix(e.g. `0x86`)
* Octal - requires `0` prefix(e.g. `096`)



## Memory Addresses
### To access a memory address - it needs to be assigned(in form of a number) to a pointer variable and then just access it like any pointer(*pointer)
* Create a variable to access a memory address - `type* var = (type*)0xb8000`
* Write to the memory address using the created variable - `*var = 5`
* Read from a memory address using the created variable - `var2 = *var`



## Code blocks
### ; - semicolon separates statements; curly-braces make a block of statements which are executed as different statements, but could be used after things like if and all of them would be executed on condition and not only the first
```c
{
	int i;
	int b;
}
```
Is same as
```c
int i;
int b;
```
But if used after a keyword(e.g. if) in the first example both will belong to condition(execute when true and not execute when false), in the second one only the first statement will belong to the condition



## Linkage
### The c files should be linked together and not infinitly included into each other
Header files should include only function prototypes and defines and are included so the compiler does not give implicit declaration warning:
```c
#define TEST 1
type* func_name(int arg);
```
While C files should contain function defines:
```c
type func(type args)
{
	printf("Helllo");
}
```
Linkage is done by passing multiple c files to the compiler and putting -o <outputfile> at the end, and it will resolve all the references and produce a binary e.g.:
`gcc library.c file.c -o file.o`

Note: headers need to be included in the c files that have defines also, so the compiler will tell if there are mismatches between prototype and the real function defenition



## Header guards
### It could be a problem if heaader gets included several times, because compiler will output that there is a problem with multiple declaration or some other warnings, so header guards exist to stop header from being included several times
```c
#ifndef FILE_H
#define FILE_H
CODE
#endif
```
This is a header guard and it includes the header if a macro is not defined and defines it, so if a header is included second time then the first check will fail as the macro is already defined



## Function pointers
### Function pointers have a ton of purposes and can be used to call both static and global functions
* Function pointer declaration - `type (*name)(type aguments) = &func;`
* Calling function pointers - `name(arguments);`



## Strings Combination
### String combination is when two strings that are put side by side without commas as combined into one by the compiler
* Two examples below do the same thing
	* `char str1 = "Hello""world"`
	* `char str2 = "Hello world"`
* Macros can also be used here
```c
#define MACRO '\001''c'
printf(MACRO"Hello");
```



## Header purpose and function prototypes
### Every c file should have a corresponding header file(e.g. mm.c and mm.h) and headers files should contain(do not put the following stuff in .c files so they stay clean from defines and only contain the code):
* Macros
* Structure defines
* Type defines
* Function prototypes
	* Before any function is defined(e.g. int func(){code}) there should(it is not compulsory by c standard, but is a good practice) be a prototype created for it in the header included into the c file where is defined. The prototype should look same as the define of function, just without the code(e.g. int func();)



## Remove unused variable warning
* Create a statement casting the function variable to void
	* Example
		* `(void)var;`
	* Make it easier with a macro defined like that `#define REMOVE_UNUSED_WARNING(x) (void)(x)`, then use with
		* `REMOVE_UNUSED_WARNING(var);`



## Finding segmentation fault location
1. Compile the C program with -g flag and find the line where bug occurs using gdb
2. Use printf statments to find the causes of the bug if it is not obvious, printf the states of variables at that time
	* If printf does not work, try adding a `fflush(stdout);` after printf - `printf("string"); fflush(stdout);`, becuase [this may cause a problem](https://stackoverflow.com/questions/9469790/execution-of-printf-and-segmentation-fault)



## Calling functions based on strings, numbers or other variables
* To call a function based on content of a variable/string, declare two lists - one with the variables of the needed type and second with the function pointers. In these lists the element string_list[0] should correspond to the function in function_list[0], string_list[1] should correspond to the function in function_list[1] and so on... To use it get the string/variable value from desired location, then loop through variable/string list comparing the value we have to every element in the list, if the value we have matches one of the elements in the list then get the index of that element and call the function pointer at the same index in the function pointers list



## String number insertion escape sequences
* To insert numbers into a string as numbers(as binary which represents the number and not the ASCII code for it's symbol), and not symbols, character escapes are used. There are 2 types of character escapes: hexadecimal(`\x`) and octal`\0`), each of these escapes enables to insert numbers in corresponding forms(in hex from and octal form). Character escapes are put into the string as(space after the number is not required and is put here just for visibility) `"\<type_of_number><number> some stuff in the string"`(e.g. `"\x5F hello"`), but the number inserted after the character escape could be only one byte or less in size(e.g. max hex number is 0xFF, because strings are made of char type which is one byte in size)