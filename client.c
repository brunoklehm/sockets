#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;

    /* AF_INET - IPv4, SOCK_STREAM - tcp, 0 - IP */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

    if (socket_desc == -1)
    {
        printf("Não foi possível criar o socket");
        return 1;
    }

    /* server to connect */
    server.sin_addr.s_addr = inet_addr("172.217.28.132");
    server.sin_family = AF_INET; /* IPv4 */
    server.sin_port = htons(80);

    /* connect to server */
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Erro ao conectar-se\n");
        return 1;
    }

    printf("Conectado.\n");

    return 0;
}