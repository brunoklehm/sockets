#include <netinet/in.h>
#include <stdio.h>
#include <string.h> /* strlen */
#include <sys/socket.h>
#include <arpa/inet.h> /* inet_addr */
#include <unistd.h> /* close */

int main(int argc, char *argv[])
{
    int socket_desc, c, new_socket;
    struct sockaddr_in server, client;

    /* start a new socket */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Não foi possível criar o socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; /* listen to any IP of the machine */
    server.sin_port = htons(8888);

    /* binds the socket to the port informed */
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        printf("Erro ao fazer o bind\n");
    }

    printf("Bind efetuado. \n");

    /* listen */
    listen(socket_desc, 3);

    /* accept incoming connections */
    printf("Aguardando conexões...\n");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c);
    
    if (new_socket < 0)
    {
        printf("Erro ao aceitar conexão\n");
        return 1;
    }
    char *client_ip = inet_ntoa(client.sin_addr);
    int client_port = ntohs(client.sin_port);

    printf("Conexão aceita do client %s:%d\n", client_ip, client_port);

    return 0;
}