# Main network manager of the chat client


import socket
import farchat_src.core.common as common

HOST = "0.0.0.0" # listen on a specified port on all addresses, 0.0.0.0 would mean all addresses


class P2Pconnection:
	def __init__(self):
		self.start_p2p_server()
		self.start_p2p_device_search()

	def start_p2p_server(self):
		p2p_server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create an IPv4(AF_INET) TCP(SOCK_STREAM) socket
		p2p_server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # SOL_SOCKET is the level on which option should be set and means socket level, SO_REUSEADDR option being set to 1 makes it so that server can use it's requested port without waiting if no one else is using it now
		p2p_server_socket.bind((HOST, common.FARCHAT_SERVER_P2P_PORT)) # bind to the farchat server port on all available IPs
		p2p_server_socket.listen(1) # make the socket listening/server
		# continue the multithreaded webserver from here


	def start_p2p_device_search(self):
		pass



class ClientToServerConnection:
	def __init__(self):
		pass
