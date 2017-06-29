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

-If the client inputs a command like "CTRL + C" on a TCP connection, that command will be sent to the TCP server program running on the terminal and then executed on the server terminal.

# Project decisions and solutions
Portuguese:
-O programa foi dividido da seguinte maneira:
	-A main.c trata da entrada do usuário e a interpreta, rodando as respectivas funções de servidor ou cliente com os argumentos de entrada fornecidos pelo usuário, tratando e exibindo mensagens de erro caso haja algum argumento incorreto ou argumento essencial faltando.

	-O common.c (e .h), inclui as bibliotecas comuns a serem utilizadas tanto pelo cliente e servidor, bem como variáveis globais e funções comuns. As funções presentes nela tratam possíveis erros de execução no programa, exibindo uma mensagem indicando a causa do erro e fechando os sockets de cliente e servidor se necessário. Ela também cuida de uma possível situação de timeout, exibindo a mensagem indicando que ocorreu esse timeout e fechando os sockets de cliente e servidor se necessário.

	-Tanto para o cliente e servidor, no inicio de cada função é criado um sinal de alarme para identificar um possível timeout, nas funções que podem causar um bloqueio do programa é executada uma função alarm com uma variável global TIMEOUT que indica o tempo até o timeout do programa. Caso o alarme seja esgotado a função que cuida do timeout em common.c indica que ocorreu esse timeout, fecha os sockets se necessário e termina o programa.

	-O client.c (e .h), trata de rodar o lado do cliente. A conexão pode ser feita utilizando UDP ou TCP, ambas com suas respectivas funções.
		-A conexão TCP segue o seguinte caminho (realizando um teste em cada uma dessas funções para identificar se ela foi executada com sucesso ou não): cria o socket -> identifica o servidor -> complementa as informações desse servidor (incluindo a porta e mais algumas informações) -> realiza a conexão -> entra em um loop para mandar as mensagens na conexão persistente -> espera o ACK do servidor -> ao sair fecha o socket criado

		-A conexão UDP segue o seguinte caminho (realizando um teste em cada uma dessas funções para identificar se ela foi executada com sucesso ou não): cria o socket -> identifica o servidor -> complementa as informações desse servidor (incluindo a porta e mais algumas informações) -> pede uma mensagem a ser enviada -> espera o ACK do servidor -> sai 

	-O server.c (e .h) trata de rodar o lado do servidor. A conexão pode ser feita utilizando UDP ou TCP, ambas com as suas respectivas funções.
		-A conexão TCP segue o seguinte caminho (realizando um teste em cada uma dessas funções para identificar se ela foi executada com sucesso ou não): cria o socket do servidor -> complementa as informações do servidor (como a porta a ser utilizada) -> associa o servidor ao socket -> entra em um loop esperando uma conexão com um cliente -> aceita uma conexão a conexão com o cliente -> entra no loop de mensagens com esse cliente -> lê as mensagens recebidas do cliente (e as mostra na tela) -> envia um ACK -> caso o cliente queira fechar a conexão ele o faz e envia um ACK -> volta a esperar conexões com outros clientes -> caso não haja mais clientes novos até o timeout, fecha o socket e encerra o programa.

		-A conexão UDP segue o seguinte caminho (realizando um teste em cada uma dessas funções para identificar se ela foi executada com sucesso ou não): cria o socket do servidor -> complementa as informações do servidor (como a porta a ser utilizada) -> associa o servidor ao socket -> entra em um loop esperando mensagens de clientes -> caso receba uma, mostra a mensagem na tela e envia um ACK -> volta a esperar mais mensagens -> caso não haja mais mensagens até o timeout, sai do loop, fecha o socket e encerra o programa.
