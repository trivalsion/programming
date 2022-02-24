# Contains fconsole commands common for both the client and server


import farchat_src.fconsole.fconsole_defines as fc_defines
import farchat_src.core.common as common
import os


def fconsole_list(command_name, arguments_list):
	pass

# @brief : displays json from display.json settings file in a formatted manner
def fconsole_display(command_name, arguments_list):
	if os.path.isfile(common.fconsole_display_config_file_path) == True:
		common.opened_file_descriptors_dict["fconsole_display_config_file_read_fd"] = open(common.fconsole_display_config_file_path, "r")
	else:
		common.output_error("Display config file is missing", common.ERROR_TYPE_NORMAL)
		return fc_defines.FUNCTION_RETURN_STATUS_FAIL


# @brief : quits the farchat
def fconsole_quit(command_name, arguments_list):
	return (fc_defines.FUNCTION_RETURN_STATUS_QUIT, 0)


command_name_to_function_dict = {"list" : fconsole_list, "display" : fconsole_display, "quit" : fconsole_quit}