# Main network manager of the chat client


import socket

HOST = "0.0.0.0" # listen on a specified port on all addresses, 0.0.0.0 would mean all addresses
FARCHAT_P2P_PORT = 65524


class P2Pconnection:
	def __init__(self):
		self.start_p2p_server()
		self.start_p2p_device_search()

	def start_p2p_server(self):
		p2p_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create an IPv4(AF_INET) TCP(SOCK_STREAM) socket
		p2p_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # SOL_SOCKET is the level on which option should be set and means socket level, SO_REUSEADDR option being set to 1 makes it so that server can use it's requested port without waiting if no one else is using it now
		# make the server concurrent

	def start_p2p_device_search(self):
		pass



class ClientToServerConnection:
	def __init__(self):
		pass
