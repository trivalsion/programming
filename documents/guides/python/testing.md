# Testing code in python(e.g. unit tests)
## Resources
* [Full Python testing guide](https://realpython.com/python-testing/)
* [Testing guide and testing implementation explanation](https://towardsdatascience.com/the-importance-of-testing-your-python-code-9b1262d009dc)


## Information
* What tests should do - tests should call a function and supply it with different kinds of arguments and then check if it returns the correct value depending on the input values, the tests should test:
	* Edge cases(e.g. very high and very low numbers)
	* Incorrect input to see how it deals with it(e.g. supplying a string when a number is required)
	* The input which is used most often
* When to write a test - tests should be written for large methods, classes(test if the interaction of methods within the class is ok) and functions
* Where to write tests - tests should be located in seperate files in a seperate folder; there should be a seperate test_*.py file for each py file which is being tested; there should be some sort of automated script that would run all `test_*.py` files


## Implementation
### [Unit Test Library](https://docs.python.org/3/library/unittest.html)
* Description: The built-in and easiest library for testing is `unittest`
* Example for testing a program that has `core.py` and `gui.py` files
	* `core.py` example contents
		* 	```python
			def multiplication(a, b):
				return a * b
			def division(a, b):
				return a / b
			```
	1. It is recommended to make a `test/` folder in the project directory so test files do not clutter the source code
	2. Create `test_core.py`(it is important that files have the test_ prefix) file in `test/` directory
	3. Fill the file for testing `core.py`(`test_core.py`) with the testing code
		* 	```python
			import core # import the core.py so the methods from it are imported and could be accessed/called by the test_core.py
			import unittest

			class TestCore(unittest.TestCase): # the class could be named anything, but it is important it inherits from unittest.TestCase
				def setUp(self): # setUp(named exactly like this) method is not required, but if it is present in the class, code in it will run before every test method
					print("Start test")

				def tearDown(self): # tearDown(named exactly like this) method is not required, but if it is present in the class, code in it will run after every test method
					print("End test")

				def test_multiplication(self): # the test methods could be named anything, but they SHOULD have a "test_" prefix in their name
					expected_result = 4 # the variables are supplied to assertEqual method just for convinience, the function call and expected result could be supplied to it directly as arguments without using intermidate variables
					answer = core.multiplication(2, 2) # call to the function with selected input arguments, to then compare it's return value with the expected value
					self.assertEqual(answer, expected) # assertEqual is a method inherited from unittest.TestCase, it compares it's first argument(which should be the return value of function) and second(which should be the expected value) and if they are not equal it prints out that the test failed. There are multiple different methods similar to assertEqual in unittests - https://docs.python.org/3/library/unittest.html#assert-methods

				def test_division(self):
					expected_result = 3
					answer = core.division(6, 2)
					self.assertEqual(answer, expected)

			if __name__ == "__main__": # this if statement checks if the module is run directly(python <module>) and not imported into another module and if it is than it calls the main function from unit test which should call all of the tests and output runtime info...
				unittest.main()

			# There is also "assertRaises" method to test if a particular exception occured
			```

### Assert keyword
* Description - a python built-in keyword for fast small tests, if it's argument results in False, it raises an exception
* Example
	* 	```python
		def multiplication(a, b):
				return a * b
		def division(a, b):
			return a / b

		assert multiplication(1, 2) == 2 # the keyword outputs an AssertionError exception if it's argument is False which in this case will be if the comparasion fails
		assert division(2, 1) == 2, "Division function malfunctions" # error text could be supplied as a string after the comma after the comparasion, this text will be outputted if the assertion fails(values not equal in this case)
