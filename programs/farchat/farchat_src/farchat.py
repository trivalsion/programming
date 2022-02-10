# The main application of the farchat program


import argparse
import farchat_src.core.common as common
import farchat_src.client.farchat_client as fcc
from .core.config_parser import global_configuration


server_mode = False # by default farchat works in client mode


def parse_cli_arguments():
	parser = argparse.ArgumentParser()

	parser.add_argument("-c", "--config", help="choose a config file location from which the program should read settings instead of using the default config file")
	parser.add_argument("--debug", default = "1", help="run the program in debug mode")
	parser.add_argument("--server", default = "1", help="starts farchat in server mode")

	parsed_arguments = parser.parse_args()

	if parsed_arguments.debug == "1":
		common.debug_mode = True
	elif parsed_arguments.server == "1":
		global server_mode
		server_mode = True
	return

def start_farchat():
	parse_cli_arguments()
	global_config_data = global_configuration()
	global_config_data.get_json_global_config()

	if server_mode == True:
		pass # call a function to start server mode
	else: # start client by default, unless server mode is on
		fcc.start_client()
