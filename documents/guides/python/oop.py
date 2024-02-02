## Summary of python oop
# Most detailed Python OOP article/tutorial - https://realpython.com/python3-object-oriented-programming/
# Video Tutorial - https://www.youtube.com/watch?v=JeznW_7DlB0
# Explanation of main stuff in Python's OOP - https://python.swaroopch.com/oop.html


## Glossary
# Class - class is something like a template of a type of an object, variables and functions are always defined/decalred as a certain class instance(in python declaration of variables is done with assignment operator - "="), so when some variable or function is declared with a certain class type, it becomes an instance of a class. A class is defined in python with the following code syntax: "class <class-name>: ".
# Object - any variable or function in python is an object, object in terms of programming is a instance of a certain class(or in other words class "template")
# Method - is a function inside of a class(object) which is called with "<object>.<method>"


## Classes Basics
from re import M


class Car: # defining of a class - "class <class-name>: "
	# "self" - it is a reference to the class instance(object) itself and is a reserved name("self" is), it has to be declared as a first argument when declaring any method because it allows you to access the class instance's data from the method and also python always with out consent will pass it as the first argument when calling any method.
	def __init__(self, car_name): # __init__ is a special method name, if a class contains method named __init__(and it should), then when a class instance is created("<var_name> = <class_name>()") this method would be called immidiatly(it is intended for setting up class instances with data). __init__ method could also have arguments and they would be passed to the () when creating the class instance
		self.name = car_name # "self.<var_name> = <value>" saves the variable value inside a class instance under <var-name> so it could be later retrieved with "class.<var_name>" syntax. The argument and self.<var> names don't have to match and the argument is not even required to declare a variable in the class instance.

	def output_car_name(self):
		print(self.name)

	def change_car_name(self, new_car_name):
		self.name = new_car_name

my_car = Car("Python Car") # creating an instance of a class with "<var_name> = <class_name>()" and passing an argument to it as it is required by the __init__ method
my_car.output_car_name() # calling the class's method
my_car.change_car_name("Python Car, Model 10") # calling the class's method and passing an argument to it
my_car.output_car_name()
print(my_car.name) # printing a value of a class-wide variable with "<object>.<variable>"


## Class Inhertance - class inheritance is when one class(usually called child class) takes/inherits all methods(methods like __init__ are also inherited) and variables from another class(usually called parent class) and then usually adds it's own methods/variables also. When interacting with an object(class instance) you interact with the child class as you would with a parent/normal class with first declaring it("<var_name> = <class_name>()") and then using it("<object>.<method>"). Child class instances allows you to access(<class_name(parent or child)>.<method/var>) any method or varible that was declared in parent class "template" and everything that was declared in child's own class template, but the parent class can't access stuff that was only declared in a child method. If a child class has a variable or method named the same as one in it's parent class, then this child's method or variable overwrites the parent's one and each time the variable or method from the child class would be used, it would be the child's own and not parent's that would be used. There may be many childs of childs of childs... classes
class Truck: # you do not have to do anything for a class to become parent class, it becomes parent when some other class includes it as it's parent with "class <class_name>(<parent_class>):"
	def __init__(self, truck_name):
		self.name = truck_name

	def output_truck_name(self):
		print(self.name)

class Pickup(Truck): # this class inherits all methods and variables of Truck class and so this class's instances would have access to them, to make one class become child of another and inherit everything from it do "class <class_name>(<parent_class>):"
	def set_cargo_area_size(self, cargo_area_size): # this is child's method, instances of parent class would only have parent's methods and variables, instance of this child class would have access to all parent methods and variables and to this method
		self.cargo_area_size = int(cargo_area_size)

	def output_cargo_area_size(self):
		print(self.cargo_area_size)

class Dump(Truck):
	def __init__(self, truck_name):
		super().__init__(truck_name) # the super() is a reserved name which corresponds to the parent class of the current class, here when we call a method from the parent class with "super().<method_name>", we do this because otherwise, declaring an __init__ method(or any other method which is already present in parent class) in the child class would just overwrite the method inherited from the parent class, instead with "super().<method_name>" we first run the contents of the <method_name> method of the parent and only then python runs what is in the child's <method_name> method. If you use "super()" and it's method needs an argument, you should first get the argument using the child class's method and then pass it to the "super()"'s method with (argument)
		self.name = "Dump model " + self.name

	def output_truck_name(self): # this method in the child class has the same name as a method in parent class, which means that it overrides the parent's method and will be ran instead when a method with this name is called from the class instance
		print(f"Company: Python Dump, {self.name}")

print("\n")
my_pickup = Pickup("Python Truck")
my_pickup.output_truck_name() # using a method parent class's method from a child class instance just like any other method
my_pickup.set_cargo_area_size("5000") # using child only method
my_pickup.output_cargo_area_size()
my_pickup.output_truck_name()

my_dump = Dump("Python Dump")
my_dump.output_truck_name()


## Class attributes - class variables that could be changed on all class instances simultaneously
class Rocket:
	gravity = 9.8 # varibles declared in the body of the class without self.<var_name>(class attributes) make it possible to change their value for all class instances at once and not only for one. To change the value of this variable in all instances of a class use "<class_name>.<var_name> = <data>", to change the value of the variable only in one class instance use "<instance_variable(Declared with <var_name> = <class_name>())>.<var_name> = <data>"

	def __init__(self):
		pass

	@classmethod # "@classmethod" should be put above declarations of methods that modify all class instances at once and not only their own instance
	def change_global_var(cls): # "cls" is a reserved name(similar to "self" in terms of usage) which corresponds to a class, so basically all instances of a class, this means that when changing class attribute variable's value with "cls.<var_name> = <data>" the value of the variable changes in all instances of the class. To use "cls" in a method: declare it the first argument of the method, put "@classmethod" on the line above class declaration, then just use it with "cls.<var_name> = <data>"
		cls.global_test_var = 7

print("\n")
rocket1 = Rocket() # creating an instance of a class
rocket2 = Rocket()

Rocket.gravity = 1.62 # change class attribute value in all class instances
rocket1.gravity = 3.721 # change class attribute only in this instcance of the class
print(f"Gravity: {rocket1.gravity}, {rocket2.gravity}")


## Static methods - methods that could works without an instance of the class(and subsequently their are called static because they cannot change the instance of a class). Static classes are used for organisational reasons so that you could group functions into classes, but at the same time won't be required to create class instances to use these functions. Static methods should not have the "self" argument passed to them. Classes could have multiple methods of different types and a class could simoultaneously have a static and normal methods, just static methods would have "@staticmethod" above their declaration
class Info:
	@staticmethod # "@staticmethod" should be put above declarations of static methods(which do not require an instance of this class to be present)
	def vehicles_present(arg): # arguments here are just for an example, they are not required to have a static class, only thing that is required is no "self" as an argument and "@staticmethod" above
		print(f"Vehicles present: {arg}")

print("\n")
Info.vehicles_present("Cars, Trucks, Rockets") # here a static method is called, this is done by just writing "<class_name>.<static_method_name>()"", just like a normal method, but using class name instead of class instance name
