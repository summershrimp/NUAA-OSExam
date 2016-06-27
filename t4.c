#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t s1_signal = PTHREAD_COND_INITIALIZER;
pthread_cond_t s2_signal = PTHREAD_COND_INITIALIZER;
int t1_gone = 0, t2_gone = 0, t3_gone = 0;
pthread_mutex_t s1_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t s2_mutex = PTHREAD_MUTEX_INITIALIZER;

void *T1_entry(void *arg)
{
    pthread_mutex_lock(&s1_mutex);

    sleep(2);
    puts("T1");

    t1_gone = 1;
    pthread_cond_broadcast(&s1_signal);
    pthread_mutex_unlock(&s1_mutex);

    return NULL;
}

void *T2_entry(void *arg)
{
    pthread_mutex_lock(&s1_mutex);
    while(!t1_gone)
        pthread_cond_wait(&s1_signal, &s1_mutex);
    pthread_mutex_unlock(&s1_mutex);
    
    sleep(1);
    puts("T2");
    
    pthread_mutex_lock(&s2_mutex);
    t2_gone = 1;
    pthread_cond_signal(&s2_signal);
    pthread_mutex_unlock(&s2_mutex);
    
    return NULL;
}

void *T3_entry(void *arg)
{
    pthread_mutex_lock(&s1_mutex);
    while(!t1_gone)
        pthread_cond_wait(&s1_signal, &s1_mutex);
    pthread_mutex_unlock(&s1_mutex);
     
    sleep(1);
    puts("T3");
    
    pthread_mutex_lock(&s2_mutex);
    t3_gone = 1;
    pthread_cond_signal(&s2_signal);
    pthread_mutex_unlock(&s2_mutex);

    return NULL;
}

void *T4_entry(void *arg)
{
    pthread_mutex_lock(&s2_mutex);
    while(!t2_gone || !t3_gone)
        pthread_cond_wait(&s2_signal, &s2_mutex);
        
    puts("T4");
    
    pthread_mutex_unlock(&s2_mutex);
    return NULL;
}



int main(void)
{
    pthread_t t1,t2,t3,t4;
    pthread_create(&t1, 0, T1_entry, NULL);
    pthread_create(&t2, 0, T2_entry, NULL);
    pthread_create(&t3, 0, T3_entry, NULL);
    pthread_create(&t4, 0, T4_entry, NULL);
    
    pthread_join(t4, NULL);
    return 0;
}
