# Contains utility functions


import sys


# @brief : cleanly exists from the program
# @param exit_status : tells wether the program should return successfull or unsucessfull exit
def clean_exit(exit_status):
	sys.exit(exit_status) # close the program returning succesfull exit

# @brief : prints debugging information and only when the debugging mode is enabled
def print_debug():
	pass