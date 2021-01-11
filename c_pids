#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

void printFile(char *filename){
	char buff[200];
	int read_data;
	int file = open(filename, O_RDONLY);

	while((read_data = read(file,buff,200))>0){
		int i;		
		for(i = 0;i<read_data;i++){
			write(STDOUT_FILENO,buff[i],1);
			if((write(STDOUT_FILENO,buff[i],1))<0)	perror("write");	
		}
	}

	if(read_bytes!=0){
		perror("read");
	}
	close(file);
}

int main(int argc, char *argv[]){
	pid_t pid[argc-1];
	int i;

	for(i=0;i<argc;i++){

		pid[i-1] = fork();
		if(pid[i-1]==0)
		prinFile(argv[i]);
		return 0;
		else if (pid[i-1]<0) perror("fork");
	}

	for(i=0;i<argc;i++){
		wait(NULL);
	}
return 0;

}
