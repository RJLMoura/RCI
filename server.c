//SERVER TCP

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <netdb.h>
//#include "node.h"

#define PORT "59000"

//number of nodes
int node_nmbr = 0;
//array with anchor id
int anc[2];

struct node {
    int id;
    int net;
    int ip;
    int port;
    struct node *ext;
    struct node *bck;
    struct node *intr;
};
//array of nodes
struct node no_ar[100];

void join_tree(int id, int net) {

    struct node* no_ptr = malloc(sizeof(struct node));
    no_ptr->intr = calloc(100, sizeof(struct node));
    printf("ola\n");
    no_ptr->id=id;
    no_ptr->net=net;
    //caso primeiro no
    if(node_nmbr == 0){
        no_ar[id] = *no_ptr;
        no_ptr->bck = no_ptr;
        node_nmbr++;
        anc[0] = id;
        printf("adeus\n");
    }
    //caso segunda ancora
    else if(node_nmbr == 1){
        no_ar[id] = *no_ptr;
        no_ptr->bck = no_ptr;
        node_nmbr++;
        no_ptr->ext = &no_ar[0];
        no_ptr->ext->ext = &no_ptr;
        anc[1] = id;
    }

    return;
}


int main()
{
struct addrinfo hints, *res;
int fd, newfd, errcode;
ssize_t n,nw;
struct sockaddr addr; 
socklen_t addrlen;
char *ptr, buffer[128];

if((fd=socket(AF_INET,SOCK_STREAM,0))==-1) 
{
     exit(1);
    //error
}


memset(&hints,0,sizeof hints);

hints.ai_family=AF_INET;    //IPv4
hints.ai_socktype=SOCK_STREAM;  //TCP socket
hints.ai_flags=AI_PASSIVE;

if((errcode=getaddrinfo(NULL, PORT, &hints, &res))!=0)
    /*error*/
    exit(1);

if(bind(fd,res->ai_addr,res->ai_addrlen)==-1) {
    /*error*/
    printf("ERROR\n");
    exit(1);
}

if(listen(fd,5)==-1)
    /*error*/
    exit(1);
int net=0, id=0;
while(1){
    addrlen=sizeof(addr);

    if((newfd=accept(fd,&addr,&addrlen))==-1)
        /*error*/
        exit(1);
    

    while((n=read(newfd,buffer,128))!=0){
        if(n==-1)
        /*error*/
        exit(1);

        printf("n: %ld\n", n);

        
        ptr=&buffer[0];
        while(n>0){
            
            if((nw=write(newfd,ptr,n))<=0)
            /*error*/
            exit(1);

            int i=0;
    for(i=nw; i<strlen(buffer); i++)
    {
        buffer[i] = 0;
    }

    

        printf("nw: %ld\n", nw);
        printf("buffer: %s\n", &buffer);

    net=0;
    id=0;
    char func[12], command[12];
    sscanf(buffer,"%s %d %d", func, &net, &id);

    struct node no_ptr;

    no_ptr.id=id;

    if(strcmp(func, "join")==0){
        printf("joinado\n");
        join_tree(id, net);
    }

    if(strcmp(func, "leave")==0){
        printf("Leavado\n");
        //leave_tree();
    }

    n-=nw; ptr+=nw;
        }
}
close(newfd);
}
freeaddrinfo(res);
close(fd);
exit(0);
}