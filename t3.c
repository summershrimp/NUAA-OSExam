#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


typedef struct {
    int from;
    int to;
    int ans;
} Arg;


void *calc(void *arg)
{
    Arg *p = arg;
    int i;
    p->ans = 0;
    for(i = p->from; i<= p->to; ++i)
    	p->ans += i;
    return NULL;
}

int main(void)
{
    pthread_t ths[10];
    Arg args[10];
    int i, sum=0;    
    for(i = 0; i< 10; ++i)
    {
    	args[i].from = i*10 + 1;
    	args[i].to = (i+1) * 10;
    	pthread_create(ths + i, 0, calc, args + i); 
    }
    
    for(i = 0; i< 10; ++i)
        pthread_join(ths[i], NULL);
    
    for(i = 0; i<10; ++i)
        sum += args[i].ans;
    
    printf("%d\n", sum);    
    return 0;
}

