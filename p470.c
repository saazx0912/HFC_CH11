#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error(char *msg){
    fprintf(stderr ,"%s: %s\n",msg ,strerror(errno));
    exit(1);
}

int main(){
    int listener_d = socket(PF_INET , SOCK_STREAM , 0);

    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int c = bind(listener_d , (struct sockaddr *) &name  , sizeof(name));
    if( c == -1){
        error("Can't bind to socket");
    }

    if(listen(listener_d ,10)){ //長度10的佇列，前10個可以等待，第11，12...會被告知伺服器過於忙碌
        error("Can't listen");
    }

    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect_d = accept(listener_d , (struct sockaddr *) &client_addr , &address_size); //連接描述子
    if(connect_d == -1){
        error("Can't open sceondary socket");
    }

    char *msg = "Internet Knock-Knock Protocol Server \r\nVersion 1.0\r\nKnock! Knock!\r\n> ";
    if(send(connect_d ,msg ,strlen(msg) , 0) == -1){
        error("send");
    }
}