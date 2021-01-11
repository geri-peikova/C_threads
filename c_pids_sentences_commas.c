#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void printFile(char *filename){
    int commas = 0;
    int sentences = 0;
    char buff[200];
    int read_bytes;
    int fd = open(filename,O_RDONLY);
    char previouschar = '.';
    
    while((read_bytes = read(fd, buff, 200)) > 0) {
        int i;
        for(i = 0; i < read_bytes; i++){
            if (buff[i] == '.' && previouschar != '.' ){
                sentences++;
            }else if(buff[i] == ','){
                commas++;
            }
            previouschar = buff[i];

            if((write(STDOUT_FILENO, &buff[i], 1)) < 0) {
                perror("write");
            }
        }
    }

    if(read_bytes != 0){
            perror("read");
        }
    close(fd);

    printf("\nCommas: %d\nSentences: %d\n", commas, sentences);
}

int main(int argc, char *argv[]){
    pid_t array_pids[argc - 1];
    int i;

    for(i = 1; i < argc; i++){
        array_pids[i - 1] = fork();

        if(array_pids[i - 1] == 0){
            printFile(argv[i]);
            return 0;
        }else if (array_pids[i - 1] < 0){
            perror("fork");
        }
    }   

    for(i = 1; i < argc; i++){
        wait(NULL);
    }
    return 0;
}
