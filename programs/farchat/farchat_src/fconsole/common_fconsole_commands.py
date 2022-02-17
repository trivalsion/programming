# Contains fconsole commands common for both the client and server


import farchat_src.fconsole.fconsole_defines as fc_defines


def fconsole_list(command_name, arguments_list):
	pass

# @brief : displays json from display.json settings file in a formatted manner
def fconsole_display(command_name, arguments_list):
	pass

# @brief : quits the farchat
def fconsole_quit(command_name, arguments_list):
	return (fc_defines.FUNCTION_RETURN_STATUS_QUIT, 0)


command_name_to_function_dict = {"list" : fconsole_list, "display" : fconsole_display, "quit" : fconsole_quit}