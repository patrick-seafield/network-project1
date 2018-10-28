chatclient : connect.o run_client.o run_client_ec.o
	cc -o chatclient chatclient.c connect.o run_client.o run_client_ec.o

connect.o : connect.h
	cc -c connect.c

run_client.o : constants.h run_client.h
	cc -c run_client.c

run_client_ec.o : constants.h run_client_ec.h
	cc -c run_client_ec.c

clean :
	rm chatclient connect.o run_client.o run_client_ec.o
