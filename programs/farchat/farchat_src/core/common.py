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
		print(ANSI_COLOR_FOREGROUND_BLUE) # set the font color to be blue
		print("Debug Info: " + string)
		print(ANSI_COLOR_RESET) # reset the color of the text

# @brief : outputs error messages and can do extra steps depending on the error type
# @param error_string : the string which should be outputted in the case of an error
# @param error_type : a number indicating error type, use ERROR_TYPE_* constants for that
def output_error(error_string, error_type):
	if error_type == ERROR_TYPE_NORMAL:
		print(ANSI_COLOR_FOREGROUND_RED)
		print(f"Error: {error_string}", file=sys.stderr) # write the error output to stderr
		print(ANSI_COLOR_RESET)
		return
	if error_type == ERROR_TYPE_WARNING:
		print(ANSI_COLOR_FOREGROUND_MAGENTA)
		print(f"Warning: {error_string}", file=sys.stderr)
		print(ANSI_COLOR_RESET)
		return
	if error_type == ERROR_TYPE_FATAL:
		print(ANSI_COLOR_FOREGROUND_RED)
		print(f"Fatal: {error_string}", file=sys.stderr)
		print(ANSI_COLOR_RESET)
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
