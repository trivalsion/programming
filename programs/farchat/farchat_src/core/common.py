# Contains functions common for the whole program


import sys
import datetime
import os


ANSI_ESCAPE = "\033["
ANSI_COLOR_RESET = f"{ANSI_ESCAPE}0m" # reset the fore and backgroup color of the text to default
ANSI_COLOR_FOREGROUND_BLACK = f"{ANSI_ESCAPE}0;30m"
ANSI_COLOR_FOREGROUND_RED = f"{ANSI_ESCAPE}0;31m"
ANSI_COLOR_FOREGROUND_GREEN = f"{ANSI_ESCAPE}0;33m"
ANSI_COLOR_FOREGROUND_WHITE = f"{ANSI_ESCAPE}0;37m"
ANSI_COLOR_FOREGROUND_BLUE = f"{ANSI_ESCAPE}0;34m"
ANSI_COLOR_FOREGROUND_MAGENTA = f"{ANSI_ESCAPE}0;35m"

ERROR_TYPE_NORMAL = 1
ERROR_TYPE_WARNING = 2
ERROR_TYPE_FATAL = 3

LOG_TYPE_NORMAL = 1
LOG_LOCATION_FILE = 1
LOG_LOCATION_STDOUT = 2

FARCHAT_SERVER_P2P_PORT = 65524


debug_mode = False
main_data_folder_path = "./farchat" # the path of the folder which would store the logs and configs subfolders !!!!! CHANGE THIS PATH TO "$HOME/.config/farchat" on linux and "Users/<user>/farchat" on windows

main_log_folder_path = "" # the path of the folder in which all log related files and folders should be stored
main_config_folder_path = "" # the path of the folder in which all config related files and folders should be stored

main_log_file_path = os.path.join(main_log_folder_path, "farchat.log")
main_log_file_fd = None


# @brief : prints a string to the terminal, but adds the ability to select it's fore and back ground colors, colors will be reset immidiatly after the string is printed
# @param string : the string that should be printed
# @param fg_color : ANSI sequence for setting the needed foreground color, to leave the default color supply "" on the place of this argument
# @param bg_color : ANSI sequence for setting the needed background color, to leave the default color supply "" on the place of this argument
# @param fd : where the string will be outputted, by default it will be set to stdout, but any valid file descriptor could be supplied here
# @return : returns what the print() function returns
def color_print(string, fg_color, bg_color, fd=sys.stdout):
	return print(fg_color + bg_color + string + ANSI_COLOR_RESET, file=fd) # first go the ANSI sequences which tell the terminal to set fore and background colors, then goes the string, after string there goes ANSI reser sequence so the fore and background colors are reset after the string is printed; print's file argument specifies the file descriptor to which the string should be printed

# @brief : cleanly exists from the program
# @param exit_status : tells wether the program should return successfull or unsucessfull exit
def clean_exit(exit_status):
	if main_log_file_fd != None: # close the log file before exiting
		main_log_file_fd.close()

	sys.exit(exit_status) # close the program returning succesfull exit

# @brief : prints debugging information and only when "debug_mode" is True
# @param string : the debug message that should be displayed
def output_debug(string):
	if debug_mode == True:
		color_print("Debug Info: " + string, ANSI_COLOR_FOREGROUND_BLUE, "")

# @brief : outputs error messages and can do extra steps depending on the error type
# @param error_string : the string which should be outputted in the case of an error
# @param error_type : a number indicating error type, use ERROR_TYPE_* constants for that
def output_error(error_string, error_type):
	if error_type == ERROR_TYPE_NORMAL:
		color_print(f"Error: {error_string}", ANSI_COLOR_FOREGROUND_RED, "", fd=sys.stderr)
		return
	if error_type == ERROR_TYPE_WARNING:
		color_print(f"Warning: {error_string}", ANSI_COLOR_FOREGROUND_MAGENTA, "", fd=sys.stderr)
		return
	if error_type == ERROR_TYPE_FATAL:
		color_print(f"Fatal: {error_string}", ANSI_COLOR_FOREGROUND_RED, "", fd=sys.stderr)
		clean_exit() # exit in case of a fatal error

# @brief : outputs a log string
# @param string : the string which should be outputted with the log
# @param log_type : the type of log, use LOG_TYPE_* constants here
# @param log_location : where the log should be outputted to, use LOG_LOCATION_* constants here
# @return : 0 on success, -1 on fail
def output_log(string, log_type, log_location):
	global main_log_file_fd # use the global keyword so the global main_log_file_fd variable is used instead of local
	output_string = None
	now = datetime.datetime.now()

	if log_type == LOG_TYPE_NORMAL:
		output_string = f"{now.strftime('%Y-%m-%d %H:%M:%S')} [Normal Log]: {string}\n"

	if log_location == LOG_LOCATION_STDOUT:
		print(output_string)
	elif log_location == LOG_LOCATION_FILE:
		if main_log_file_fd != None: # if the log file is open, write to it
			main_log_file_fd.write(output_string)
		else: # else open the log file
			main_log_file_fd = open(main_log_file_path, "w")
			main_log_file_fd.write(output_string)

	return 0

# @brief : creates all of the config folder and files whos paths this module provides in global variables
def create_data_paths():
	if os.path.exists(main_data_folder_path) == True:
		if os.path.isdir(main_data_folder_path) == True:
			if os.path.exists(main_config_folder_path) == True:
				if os.path.isdir(main_config_folder_path) == True:
					pass
				else:
					output_error("The chosen config path is a file and farchat requires choosing a folder or an unexistant path", ERROR_TYPE_FATAL)
			else:
				os.mkdir(main_config_folder_path)

			if os.path.exists(main_log_folder_path) == True:
				if os.path.isdir(main_log_folder_path) == True:
					pass
				else:
					output_error("The chosen log path is a file and farchat requires choosing a folder or an unexistant path", ERROR_TYPE_FATAL)
			else:
				os.mkdir(main_log_folder_path)
		else:
			output_error("The chosen data path is a file and farchat requires choosing a folder or an unexistant path", ERROR_TYPE_FATAL)
	else:
		os.makedirs(main_data_folder_path)
		os.mkdir(main_config_folder_path)
		os.mkdir(main_log_folder_path)

	return

# @brief : this function sets several global variable's values with file and directory paths, the vars are not set directly(during variable creation) because they depend on a main_data_folder_path variable that could be updated and they would need to be updated with it, so instead first runs the function that could update the main_data_folder_path and then runs this functions which assigns all variables dependant on it, so in case main_data_folder_path was changed, all of these vars use it's new value
def set_data_paths():
	global main_log_folder_path
	global main_config_folder_path

	main_log_folder_path = os.path.join(main_data_folder_path, "log")
	main_config_folder_path = os.path.join(main_data_folder_path, "config")
