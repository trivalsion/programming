# To Do
* Implement the fconsole and integrate it into the client
* Implement P2P client networking part
* Implement some unit tests, testing framework



# Features
## Not Implemented
* Implement unit tests as they are necessary in such a large application
* The server listening for incoming messages should listen for multiple messages at once(multithreading) and place them to the right contacts message storage file, only show the messages when the user accesses the contact or issues a command to show unread messages/notifications
	* The client could use select for handling multiple connections, while it would be good that the server(not the P2P one) would be multithreaded
* The messages for each client should be stored in a seperate file and should have a standard format and a \r\n after every message
* Embedd a custom management system where all of the sent data could be automatically added to a central management system database on the server


## Implemented
* Have seperate folders for client code and server code
* Have one script to start both client and the server, it should start client by default and server if the `--server` argument is passed to it



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
* Controlling the application - all control of the client and server application should be done using a command line prompt built into application(so not bash, but instead the application interface itself would be a command prompt(fconsole))
	* The fconsole code should be in a seperate folder in the root package and should be common for both server and client. The fconsole code would have some function that either server or client(depending on which is started) would call and pass a list of commands and corresponding functions to it, there should be a certain format for these passed functions which would be called by fconsole commands(e.g. func(command, argumentd_list)), the format is needed so all functions accept the same arguments.
		* Make the fconsole instance a class so all the lists of commands, functions... would be assigned through class methods to it specifically
		* Commands should not have any attributes and can only have arguments(e.g. `display <messages>`)
	* Add the ability to use scripts



# Resources
* [Argparse Documentation - Command Line Argument parsing](https://docs.python.org/3/library/argparse.html)
	* [Argparse HOWTO](https://docs.python.org/3/howto/argparse.html)
* [JSON Libraray Documentation](https://docs.python.org/3/library/json.html)
	* [RealPython JSON Tutorial](https://realpython.com/python-json/)