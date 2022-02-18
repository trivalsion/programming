# The main application of the farchat program


import argparse
import farchat_src.core.common as common
import farchat_src.client.farchat_client as fcc
from .core.config_parser import global_configuration


server_mode = False # by default farchat works in client mode


def parse_cli_arguments():
	parser = argparse.ArgumentParser()

	parser.add_argument("--config", help="choose a config and log folder location that program should use instead of the default one")
	parser.add_argument("--debug", default = "1", help="run the program in debug mode")
	parser.add_argument("--server", default = "1", help="starts farchat in server mode")

	parsed_arguments = parser.parse_args()

	if parsed_arguments.debug == "1":
		common.debug_mode = True
	if parsed_arguments.server == "1":
		global server_mode
		server_mode = True
	if parsed_arguments.config:
		common.main_data_folder_path = parsed_arguments.config
	return

def start_farchat():
	parse_cli_arguments()

	common.set_data_paths()
	common.create_data_paths()

	global_config_data = global_configuration()
	global_config_data.get_json_global_config()

	if server_mode == True:
		pass # call a function to start server mode
	else: # start client by default, unless server mode is on
		fcc.start_client()
