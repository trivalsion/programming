# Contains initial client code


import farchat_src.fconsole.fconsole as fconsole
import farchat_src.core.common as common
import json


# @brief : creates the display config file for the client
def create_fconsole_display_config():
	default_display_config = {
		"contacts" : [],
		"chats" : [],
		"discovered_clients" : [],
	}

	display_config_write_fd = open(common.fconsole_display_config_file_path, "w")
	json.dump(default_display_config, display_config_write_fd) # dump the default configuration into the config file
	display_config_write_fd.close()


# @brief : initializes the farchat client code
def start_client():
	command_name_to_function_dict = fconsole.get_common_fconsole_commands()

	# Initialize and run fconsole
	client_fconsole_instance = fconsole.FConsoleInstance(command_name_to_function_dict)
	client_fconsole_instance.run_console()