#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "node.h"

struct Node {
    int id;
    int ext;
    //int *intr;
    int bck;
    //node struct
};

main (int argc, char *argv[])
{
    
}