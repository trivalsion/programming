# Contains functions common for the whole program


import sys
import datetime


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
log_file_path = "./farchat.log" # add a default path for log file
log_file_fd = None


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
	if log_file_fd != None: # close the log file before exiting
		log_file_fd.close()

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
	global log_file_fd # use the global keyword so the global log_file_fd variable is used instead of local
	output_string = None
	now = datetime.datetime.now()

	if log_type == LOG_TYPE_NORMAL:
		output_string = f"{now.strftime('%Y-%m-%d %H:%M:%S')} [Normal Log]: {string}\n"

	if log_location == LOG_LOCATION_STDOUT:
		print(output_string)
	elif log_location == LOG_LOCATION_FILE:
		if log_file_fd != None: # if the log file is open, write to it
			log_file_fd.write(output_string)
		else: # else open the log file
			log_file_fd = open(log_file_path, "w")
			log_file_fd.write(output_string)

	return 0
