#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>

int main() {

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address = {
                AF_INET,
                htons(6697),
                0
	};
        

	
        connect(sockfd, &address, sizeof(address));


        // stdin - 0 
        
        struct pollfd pfds[2] = {
                {
                        0,
                        POLLIN,
                        0
                },
                {
                        sockfd,
                        POLLIN,
                        0
                }
        };

        for (;;) {
                
                char buffer[256] = { 0 };
                poll(pfds, 2, 45000);



                if (pfds[0].revents & POLLIN) {
                        read(0, buffer, 255);
                        send(sockfd, buffer, 255, 0);
                }
                else if (pfds[1].revents & POLLIN) {
                        if(recv(sockfd, buffer, 255, 0) == 0) {
                                return 0;
                        }
                        printf("%s\n", buffer);
                }
        }
        return 0;

}


