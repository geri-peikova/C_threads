#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

 
int read_text();
int write_text();
void modify();

int size[9] = {10, 20, 20, 20, 4, 20, 1, 3, 20};
char text[9][11] = {"Header: ", "Title: ", "Artist: ", "Album: ", "Year: ", "Comment: ", "Zero-Byte: ", "Track: ", "Genre: "};
 
 
int main()
{
    int pid = fork();
    while(1)
    {
        if (pid == 0)
        {
            read_text();
        }
        else
        {
            write_text();
        }
    }
    return 0;
}


 
int read_text()
{
    char buff[30];
    memset(buff, '\0', sizeof(buff));
    int file = open("song.mp3", O_RDONLY);
    if (file < 0)
    {
        perror("Could not open file!");
        return -1;
    }
 
    lseek(file, -128, SEEK_END);
 
    for(int count = 0; count < 9; count++){
    	read(file, buff, sizeof(char) * size[count]);
        printf("%s %s\n", text[count], buff);
        memset(buff, '\0', sizeof(buff));
    }
    
 
    if (close(file) < 0)
    {
        perror("Could not close file!");
        return -1;
    }
 
    return 0;
}




 
int write_text()
{
    char buff[30] = " \0";
    int file = open("song.mp3", O_RDWR);
    if (file < 0)
    {
        perror("Could not open file!");
        return -1;
    }
 
    lseek(file, -128, SEEK_END);
 
    modify(buff, 3);
    write(file, buff, sizeof(char) * 3);
    printf("Header: %s\n", buff);
    memset(buff, '\0', sizeof(buff));
    
    for(int count = 1; count < 9; count++){
    	modify(buff, size[count]);
        write(file, buff, sizeof(char) * size[count]);
    }
 
 
    if (close(file) < 0)
    {
        perror("Could not close file!");
        return -1;
    }
 
    return 0;
}




 
void modify(char *word, int size)
{
    for (int c = 0; c < size; c++)
    {
        char text = (char)('A' + (rand() % 26));        
        word[c] = text;
    }
}






