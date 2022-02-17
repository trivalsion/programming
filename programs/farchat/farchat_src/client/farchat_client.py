# Contains initial client code


import farchat_src.fconsole.fconsole as fconsole


# @brief : initializes the farchat client code
def start_client():
	command_name_to_function_dict = fconsole.get_common_fconsole_commands()

	# Initialize and run fconsole
	client_fconsole_instance = fconsole.FConsoleInstance(command_name_to_function_dict)
	client_fconsole_instance.run_console()