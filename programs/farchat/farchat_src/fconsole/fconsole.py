# The main file for fconsole which would be imported into other files as a module


import farchat_src.core.common as common

FUNCTION_RETURN_STATUS_SUCCESS = 0
FUNCTION_RETURN_STATUS_FAIL = -1
FUNCTION_RETURN_STATUS_QUIT = -2


# Represents an instabce if fconsole
class ConsoleInstance:
	# @brief : receives the vaules required for class initialization
	# @param command_name_to_function_dict : a dictionary where function name strings correspond to functions themselves(function "pointers") declared in "def function(command_name, argument_list)" format and which return a tuple of (<function_return_status>, <function_return_data>) where <function_return_status> is the a number representing how the command ended and FUNC_RETURN_STATUS_* defines should be used at the place of <function_return_status> in the tuple; <function_return_data> in the tuple is any data that the function wants to return(e.g. display : dispaly_func)
	def __init__(self, command_name_to_function_dict):
		self.command_name_to_function_dict = command_name_to_function_dict

	# @brief : runs the console loop which gets and executes user commands
	# @return : returns 0 on success, and -1 on fail
	def run_console(self):
		while True:
			self.get_input()
			command_return_tuple = self.execute_input()
			if command_return_tuple == -1:
				command_return_tuple = None
				common.output_error(f"Command not found - {self.input_command_name}", common.ERROR_TYPE_NORMAL)
			elif type(command_return_tuple) is tuple:
				if command_return_tuple[0] == FUNCTION_RETURN_STATUS_QUIT:
					return 0
				self.command_return_tuple = command_return_tuple

	# @brief : gets the input string from the user and interprets it
	def get_input(self):
		user_input = input("farchat > ")
		tokenized_user_input = user_input.split(" ") # split the string into list by spaces

		self.input_command_name = tokenized_user_input[0]
		self.input_argument_list = tokenized_user_input[1:] # have all elements except the first one because the first one it the command itself
		return

	# @brief : executes the command
	# @param input_command_name : the string with the name of the function
	# @param input_argument_list : a list of strings with commad line arguments
	# @return : -1 on fail, tuple returned by command on success
	def execute_input(self):
		if self.input_command_name not in self.command_name_to_function_dict:
			return -1 # return -1 if no command is found
		else:
			command_return_tuple = self.command_name_to_function_dict[self.input_command_name](self.input_command_name, self.input_argument_list)

		return command_return_tuple # return the tuple returned by the function if the function was found