#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    int fds[2];
    int buf[512];
    pipe(fds); 
    pid_t pid;
    pid = fork();
    int readsize;
    if(pid == 0)
    {
        dup2(fds[1],STDOUT_FILENO);
        execlp("echo", "echo", "hello world", NULL);
        exit(0);
    }
    else if (pid > 0)
    {
     	readsize = read(fds[0], buf, 512);
     	write(STDOUT_FILENO, buf, readsize);      
    }
    close(fds[0]);
    close(fds[1]);
    return 0;

}

