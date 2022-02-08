# Contains utility functions


import sys


debug_mode = False
ANSI_ESCAPE = "\033["
ANSI_COLOR_RESET = f"{ANSI_ESCAPE}0m" # reset the fore and backgroup color of the text to default
ANSI_COLOR_FOREGROUND_BLACK = f"{ANSI_ESCAPE}0;30m"
ANSI_COLOR_FOREGROUND_RED = f"{ANSI_ESCAPE}0;31m"
ANSI_COLOR_FOREGROUND_GREEN = f"{ANSI_ESCAPE}0;33m"
ANSI_COLOR_FOREGROUND_WHITE = f"{ANSI_ESCAPE}0;37m"
ANSI_COLOR_FOREGROUND_BLUE = f"{ANSI_ESCAPE}0;34m"


# @brief : cleanly exists from the program
# @param exit_status : tells wether the program should return successfull or unsucessfull exit
def clean_exit(exit_status):
	sys.exit(exit_status) # close the program returning succesfull exit

# @brief : prints debugging information and only when the debugging mode is enabled
def print_debug(string):
	if debug_mode == True:
		print(ANSI_COLOR_FOREGROUND_BLUE)
		print("Debug Info: " + string)
		print(ANSI_COLOR_RESET)
