# Main FConsole code file, it is the only fconsole module(py) file that should be included into modules beyond this folder(package)


import farchat_src.core.common as common
import farchat_src.fconsole.common_fconsole_commands as fc_funcs
import farchat_src.fconsole.fconsole_defines as fc_defines


# @brief : returns the dictionary of strings to functions containing the default commands common for both fconsole client and server
# @return : dict of command-named strings to corresponding functions
def get_common_fconsole_commands():
	return fc_funcs.command_name_to_function_dict


# Represents an instance of fconsole
class FConsoleInstance:
	# @brief : receives the vaules required for class initialization
	# @param command_name_to_function_dict : a dictionary where command-named strings correspond to functions that execute the command(function "pointers"):
		# Declared in "def function(command_name, argument_list)" format
		# Return a tuple of (<function_return_status>, <function_return_data>)(e.g. "display" : dispaly_func)
			# <function_return_status>  - number representing how the command ended, FUNC_RETURN_STATUS_* defines should be used here instead of manually writing numbers
			# <function_return_data> - any data that the function wants to return
	def __init__(self, command_name_to_function_dict):
		self.command_name_to_function_dict = command_name_to_function_dict

	# @brief : runs the console loop which gets and executes user commands
	# @return : returns 0 on success, and -1 on fail
	def run_console(self):
		while True:
			self.get_input()
			if self.execute_input() == -1:
				common.output_error(f"Command not found - {self.input_command_name}", common.ERROR_TYPE_NORMAL)
			elif type(self.command_return_tuple) is tuple:
				if self.command_return_tuple[0] == fc_defines.FUNCTION_RETURN_STATUS_QUIT:
					return 0 # quit successfully if function returned quit status
			else:
				common.output_error("Function's return value is in an inappropriate object as it should be a tuple", common.ERROR_TYPE_NORMAL)

	# @brief : gets the input string from the user and interprets it
	def get_input(self):
		user_input = input("[fconsole] ")
		tokenized_user_input = user_input.split(" ") # split the string into a list by spaces

		self.input_command_name = tokenized_user_input[0]
		self.input_argument_list = tokenized_user_input[1:] # have all elements except the first one because the first one it the command itself
		return

	# @brief : executes the command
	# @param input_command_name : the string with the name of the function
	# @param input_argument_list : a list of strings with commad line arguments
	# @return : -1 on fail, 0 on success
	def execute_input(self):
		if self.input_command_name not in self.command_name_to_function_dict:
			self.command_return_tuple = None # set the return tuple to none if the command does not exist
			return -1 # return -1 if no command is found
		else:
			self.command_return_tuple = self.command_name_to_function_dict[self.input_command_name](self.input_command_name, self.input_argument_list) # run the function corresponding to the command and get the tuple it returned

		return 0