#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../utils/messages.h"
#include "../utils/utils.h"

int main(int argc, char *argv[]){
    int fd_pipe;
    if(argc < 2){
        write(STDERR_FILENO, BOOT_ERROR, sizeof(BOOT_ERROR));
        _exit(1);
    }

    char* command = argv[1];
    if(strcmp(command, "execute") == 0){
        if(argc < 4){
            write(STDERR_FILENO, EXECUTE_USAGE, sizeof(EXECUTE_USAGE));
            _exit(1);
        }
        int time = atoi(argv[2]);
        char *option = argv[3];
        if(strcmp(option, "-u") == 0){
            char** program = parseProgram(argv[4]);
            char request[BUFSIZ] = "execute\n";
            char timestr[12];
            sprintf(timestr, "%d\n", time);
            strcat(request, timestr);
            int i = 0;
            while(program[i]){
                strcat(request, program[i]);
                strcat(request, " ");
                i++;
            }
            fd_pipe = open(PIPE_READ_PATH, O_WRONLY);
            strcat(request, LIMITADOR_MENSAGENS);
            write(fd_pipe, request, strlen(request));
            close(fd_pipe);

            char response[BUFSIZ];

            fd_pipe = open(PIPE_WRITE_PATH, O_RDONLY);
            read(fd_pipe, response, sizeof(response));
            close(fd_pipe);

            write(STDOUT_FILENO, response, strlen(response));
        }
        else if(strcmp(option, "-p") == 0){
            char** pipeline = parsePipeline(argv[4]);

            char request[BUFSIZ] = "executep\n";
            char timestr[12];
            sprintf(timestr, "%d\n", time);
            strcat(request, timestr);
            int i = 0;
            while(pipeline[i]){
                strcat(request, pipeline[i]);
                strcat(request, "\n");
                i++;
            }
            strcat(request, LIMITADOR_MENSAGENS);
            fd_pipe = open(PIPE_READ_PATH, O_WRONLY);
            write(fd_pipe, request, strlen(request));
            close(fd_pipe);

            char response[BUFSIZ];

            fd_pipe = open(PIPE_WRITE_PATH, O_RDONLY);
            read(fd_pipe, response, sizeof(response));
            close(fd_pipe);

            write(STDOUT_FILENO, response, strlen(response));
        }
        else{
            write(STDERR_FILENO, EXECUTE_USAGE, sizeof(EXECUTE_USAGE));
            _exit(1);
        }
    }
    else if(strcmp(command, "status") == 0){
        fd_pipe = open(PIPE_READ_PATH, O_WRONLY);
        char request[BUFSIZ];
        strcpy(request, command);
        strcat(request, LIMITADOR_MENSAGENS);
        write(fd_pipe, command, strlen(command)); // Pedido de estado ao servidor
        close(fd_pipe);

        char response[BUFSIZ];

        fd_pipe = open(PIPE_WRITE_PATH, O_RDONLY);
        read(fd_pipe, response, sizeof(response)); // Espera pela resposta que foi processada pelo servidor
        close(fd_pipe);

        write(STDOUT_FILENO, response, strlen(response));
    }
    else if(strcmp(command, "close") == 0){
        fd_pipe = open(PIPE_READ_PATH, O_WRONLY);
        char request[BUFSIZ];
        strcpy(request, command);
        strcat(request, LIMITADOR_MENSAGENS);
        write(fd_pipe, command, strlen(command)); // Pedido de estado ao servidor
        close(fd_pipe);
    }
    else{
        write(STDERR_FILENO, ARGS_ERROR, sizeof(ARGS_ERROR));
        _exit(1);
    }
    return 0;
}