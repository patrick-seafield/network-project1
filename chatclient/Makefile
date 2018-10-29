chatclient : connect.o run_client.o
	cc -o chatclient chatclient.c connect.o run_client.o

connect.o : connect.h
	cc -c connect.c

run_client.o : constants.h run_client.h
	cc -c run_client.c

clean :
	rm chatclient connect.o run_client.o

