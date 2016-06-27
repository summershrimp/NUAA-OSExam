#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    int fd1[2], fd2[2];
    char buf[512]; 
    int i, sum = 0;
    int p1, p2;
    pipe(fd1);
    pipe(fd2);
    pid_t pid_a = -1, pid_b = -1;
    
    pid_a = fork();
    
    if(pid_a > 0)
    {
    	pid_b = fork();
    }
    
    if(pid_a == 0)
    {
    	for (i=0;i<51;++i)
    	    sum += i;
        write(fd1[1], &sum, sizeof(int));
        exit(0);   		
    }
    
    if(pid_b == 0)
    {
        for (i=51; i< 101; ++i)
            sum += i;
        write(fd2[1], &sum, sizeof(int));
        exit(0);
    }
    
    read(fd1[0], &p1, sizeof(int));
    read(fd2[0], &p2, sizeof(int));
    
    printf("%d\n", p1 + p2);  
    
    
    return 0;
}
