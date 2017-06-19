# basic_chat_RC-1-2017

English:

Implementation of the command line app nhem3, that provides a basic chat service. The app assembles and transmit packages between the client and the server. and vice versa in a session. What is typed in one side is echoed in the other side screen.

Server side:
% nhem3 -S [port][-t]
Client side:
% nhem3 host [port][-t]

-S [port]
Server mode, listening on [port], if not specified by the user, the default port is selected (33333)

host [port]
host that will be connected on [port], if not specified by the user, the default port is selected (33333)

-t
use TCP protocol; if not present, use UDP protocol (default)

This is a project for the course Redes de Computadores (Computer Networks), lectured in the first semester of 2017

# Compiling instructions
After cloning the repo, use "cmake [repo folder]" to generate a makefile for the program, then, compile it with make

# Call example
./nhem3 -S 33345 -t

./nhem3 localhost 33345 -t

./nhem3 localhost 33333 -u

# Bugs and limitations

-There isn't support for parallel connections.

-If the client inputs a command like "CTRL + C", that command will be sent to the server program running on the terminal and then executed on the server terminal.
