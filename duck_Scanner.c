#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void printBanner(void);

#define MAX_PORT 65535

int main(int argc, char **argv){

    if(argc < 2){
        printf("\033[31;1m[!] Usage: %s <host>\033[0m\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in connection;
    char *ipAdress = argv[1];
    int sockfd = 0, port = 1, result = 0;

    memset(&connection, 0, sizeof(connection));
    connection.sin_family = AF_INET;

    if(inet_pton(AF_INET, ipAdress, &connection.sin_addr) <= 0 ){
        printf("\033[31;1m[-] Error finding IP address.\n");
        exit(EXIT_FAILURE);
    }

    printBanner();

    for(port; port <= MAX_PORT; ++port){

        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if(sockfd == -1){
            break;
        }

        connection.sin_port = htons(port);

        result = connect(sockfd, (struct sockaddr *) &connection, sizeof(connection));

        if(result == 0){
            printf("\033[32;1m[+] Open port was found: %d\n", port);
            close(sockfd);
            continue;
        }

    }

    printf("\033[32;1m[!] The scan is complete!\n");

    return 0;
}

void printBanner(void){

    printf("\n\n\n\n\t\033[33;1m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡶⠿⠿⠷⣶⣄⠀⠀⠀⠀⠀\n");
    printf("\t   ⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁⠀⠀⢀⣀⡀⠙⣷⡀⠀⠀⠀    \n");
    printf("\t  ⠀⡀⠀⠀⠀⠀⠀⢠⣿⠁⠀⠀⠀⠘⠿⠃⠀⢸⣿⣿⣿⣿    \n");
    printf("\t ⣠⡿⠛⢷⣦⡀⠀⠀⠈⣿⡄⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⠟  \n");
    printf("\t⢰⡿⠁⠀⠀⠙⢿⣦⣤⣤⣼⣿⣄⠀⠀⠀⠀⠀⢴⡟⠛⠋⠁⠀ \n");
    printf("\t⣿⠇⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠈⣿⡀⠀⠀⠀     \n");
    printf("\t⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡇⠀⠀          [ Duck Scanner! ]\n");
    printf("\t⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡇⠀              [ By Uzu! ]\n");
    printf("\t⠸⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠀⠀⠀⠀         [ Version: 1.0 ]\n");
    printf("\t ⠀⠹⣷⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣰⡿⠁\n");
    printf("\t  ⠀⠉⠙⠛⠿⠶⣶⣶⣶⣶⣶⠶⠿⠟⠛⠉⠀⠀⠀⠀⠀\n\n\n\n");

}
