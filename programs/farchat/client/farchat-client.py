# The main file of the messenger

import argparse
import config_parser


def parse_cli_arguments():
	parser = argparse.ArgumentParser()

	parser.add_argument("-c", "--config", help="choose a config file location from which the program should read settings instead of using the default config file")

	parsed_arguments = parser.parse_args()

parse_cli_arguments()
global_settings_data = config_parser.global_settings()
global_settings_data.get_json_global_config()