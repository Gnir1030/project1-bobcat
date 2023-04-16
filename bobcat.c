#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILE_SIZE       1024

void readFile(char* buffer, char* readData, int fd, int* exitState){
        int n = 0;
        if( ( fd = open(buffer, O_RDONLY)) < 0){ // not exists files
                warn("%s", buffer);
                *exitState = 1;
        }
        else{
                while( (n = read(fd, readData, FILE_SIZE)) != 0){
                        if(n < 0){
                                warn("%s", buffer);
                                *exitState = 1;
                                break;
                        }
                        write(1, readData, n);
                }
        }

        close(fd);
}

void bobWrite(char* buffer){
        int n = 0;
        while(1){
                if( (n = read(0, buffer, FILE_SIZE)) == 0){
                        break;
                }
                write(1,  buffer, n);
        }
}

int main(int argc, char * argv[]){
        int fd = 0, exit = 0;
        int* exitState = &exit;
        char* readData = (char *)malloc(sizeof(char) * FILE_SIZE);
        char* buffer = (char *)malloc(sizeof(char) * FILE_SIZE);
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
                                readFile(argv[i], readData, fd, exitState);
                }
        }
        free(readData);
        free(buffer);
        return exit;
}
