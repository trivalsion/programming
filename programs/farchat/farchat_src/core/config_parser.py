# Parses the configuration files for the messenger

import json
import pathlib
import os

# config_directory = pathlib.Path.home()


class global_configuration:
	config_file = "./config.json" # later replace it with "{config_directory}/.config/farchat/config.dat"
	default_global_config_json_data = {
		"first_time_startup" : True,

		"users" : [
			{
				"username" : None,
				"real_name" : None,
				"email" : None,
				"user_description" : None,
			}
		]
	}

	def __init__(self):
		pass

	# @brief : creates the json config file and fills it with default contents
	# @param global_config_file_path : the path where the config file should be created
	@classmethod
	def create_json_global_config(cls, global_config_file_path):
		global_config_file = open(global_config_file_path, "w")

		json.dump(cls.default_global_config_json_data, global_config_file) # dump the default configuration into the config file

		global_config_file.close()
		return

	# @brief : reads contents from the config file, if the file does not exist it will create it and fill with default config
	# @param global_config_file_path : the path where the config file should be created, by default a default path is used
	def get_json_global_config(self, global_config_file_path=config_file):
		if os.path.isfile(global_config_file_path) == False: # if the configuration file does not exist
			self.create_json_global_config(global_config_file_path)
			return

		global_config_file = open(global_config_file_path, "r")

		data = json.load(global_config_file) # load the config file

		global_config_file.close()