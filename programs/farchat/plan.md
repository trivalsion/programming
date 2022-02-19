# To Do
* Implement standard fconsole command's functions
	* `Display` - there should be a json file(fconsole_display.json) in a specific format in the config directory from where the display could read what it can display. When `display` is invoked, it should be supplied with a CLI argument telling it what category it should display, `display` should check the json file for such category and if it is available then look what kind of info is in there(list, dict...) and output it in a formatted way
	* `List` - similar to display, but instead it should list stuff from global variables and config files of other parts of the program(e.g. contacts.txt)
	* `Sent`
* Implement fconsole command's specific to the P2P client like `connect <client>` the fconsole client should add these commands to the existing dictionary with default commands that would then be passed to fconsole instance and not create a new dict for them(because then the default commands would not be available)
* Implement P2P client networking part and test it with 2 P2P clients(seperate devices) finding each other on the network and then communicating
* Implement unit tests

## Finished ToDos
* Change all code to use only one config directory that could be set through CLI args or the default value could be used instead



# Software Architecture
## Glossary
* P2P-Server - when farchat clients communicate in P2P mode they should be able to both send and recieve data, and to recieve data they need a port running in listening mode which would recieve the messages, this would be the P2P server
* Static-Server - farchat server that only serves as a sever, relaying messages between different farchat clients, responding to commands...
* FConsole - the fconsole is the name for the command line prompt which is the interface of farchat client and server

## Info
* Networking
	* Network architecture - Program should support several types of network architecture
		* P2P - the program should support finding and chatting with clients on the local network without using a server, making it peer to peer
		* Client-Server - the program should support having the server keep track of clients on the current network and be the relay which will recieve message from one client and then transfer them to another
		* Maybe later implement it so that server would store all messages and have the client authorize and then the server will send him all of the files with his messages
		* Mixed(Client-Server + P2P) - obtain information about present clients from the server, use server for some commands... but use P2P when talking to other clients(do not relay messages through the server)
	* Servers and clients talking - static-server and p2p-server should use the same port, while when non-server port initiate a connection(send data first and not respond to some data) then they can use any port and send data to the specified server port, when a server responds to the connection it should use the server port to send data as it was the port where the message arrived
	* Discovery of other devices on the network running farchat(both server and client) - the devices discovery should work by getting the currnet device's IP, subnetmask and then sending an "are you there" request to farchat server port to all IP addresses in the subnetmask's IP range, farchat clients should respond to this with a message telling they are there, their user information and that they are clients; servers should respond telling they are there, tell information about them and say that they are a server
	* The server listening for incoming messages should listen for multiple messages at once(multithreading) and place them to the right contacts message storage file, only show the messages when the user accesses the contact or issues a command to show unread messages/notifications
		* The client could use select for handling multiple connections, while it would be good that the server(not the P2P one) would be multithreaded
* Controlling the application - all control of the client and server application should be done using a command line prompt built into application(so not bash, but instead the application interface itself would be a command prompt(fconsole))
	* The fconsole code should be in a seperate folder in the root package and should be common for both server and client
		* The fconsole instance class would have a method that server and client(depending on which is started) would call to pass a dictionary of commands and corresponding functions to it, there should be a certain format for these passed functions which would be called by fconsole commands(e.g. func(command, argumentd_list)), the format is needed so all functions accept the same arguments.
		* Make the fconsole instance a class so all the lists of commands, functions... would be assigned through class methods to it specifically
		* Create standard commands for fconsole in py file in fconsole folder so that server and client do not have to reinvent the wheel and have some standard commands. The lists with functions and strings should be stored in main fconsole file so that farchat client could use them or clone and edit after importing fconsole py file
			* Make the ability to edit these commands somehow so for example display could be adopted for client and server by creating a variable in both client and server which would contain acceptable options to display(e.g. chats and contacts for client)
		* Commands should not have any attributes and can only have arguments(e.g. `display <messages>`)
	* Add the ability to use scripts
* Code architecture
	* Have one common module(.py) which would start both the server and client. It should start client by default and server if the `--server` argument is passed to it
	* Folders for client and server code should be seperate and modules common between them should be seperated into folders of their own
	* The messages for each client should be stored in a seperate file and should have a standard format and a \r\n after every message
	* All extra files(logs and configs) should be stored in one folder that could be chosen with `--config` argument, create subfolders for logs and configs in this main folder
* Extended functionality
	* Embedd a custom management system into farchat server where all of the data sent through configured farchat server could be automatically added to a central management system database on the server



# Resources
* [Argparse Documentation - Command Line Argument parsing](https://docs.python.org/3/library/argparse.html)
	* [Argparse HOWTO](https://docs.python.org/3/howto/argparse.html)
* [JSON Libraray Documentation](https://docs.python.org/3/library/json.html)
	* [RealPython JSON Tutorial](https://realpython.com/python-json/)