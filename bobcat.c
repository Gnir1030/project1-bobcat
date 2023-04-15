#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILE_SIZE       1024

void readFile(char* buffer, char* readData, int fd){
        int n = 0;
        if( ( fd = open(buffer, O_RDONLY)) < 0){ // not exists files
                warn("%s", buffer);
                exit(1);
        }
        n = read(fd, readData, FILE_SIZE);
        if(n < 0){
                warn("%s", buffer);
                exit(2);
        }
        write(1, readData, n);
        //printf("%d, %d\n", fd, n);
        close(fd);
}

void bobWrite(char* buffer){
        while(1){
                if(scanf("%s", buffer) == EOF){
                        break;
                }
                printf("%s\n",  buffer);
        }
}

int main(int argc, char * argv[]){
        int fd = 0;
        char* readData = (char *)malloc(sizeof(char) * FILE_SIZE);
        char* buffer = (char *)malloc(sizeof(char) * FILE_SIZE);
        //char * writeData = (char *)malloc(sizeof(char) * FILE_SIZE);
        if(argc == 1)
                bobWrite(buffer);
        else if(argc > 1)
        {
                int i = 0;
                while( ++i < argc){
                        if(strcmp(argv[i], "-") == 0){
                                bobWrite(buffer);
                        }
                        else
                                readFile(argv[i], readData, fd);
                }
        }
        free(readData);
        free(buffer);
        return EXIT_SUCCESS;
}
