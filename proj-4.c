/*
Title:                CSE 430 - Operating Systems Spring 2015 Project #4
Project Description:  Implement the Readers and Writers Problem using semaphores and mutex

Author:               Kaushik Baruri (1207833857) , Vamsi Reddy (1207778100)
Version:              V1.0
*/

// producer consumer solution
#include <stdio.h>
#include <stdlib.h>
#include "sem.h"
#include <unistd.h>
#define sleeptime 4
#define N 5

semaphore_t *mutex;
semaphore_t *rsem;
semaphore_t *wsem;
int wwc,wc,rwc,rc,global_IDR=0,global_IDW=0;
int readerno,writerno;

void reader_entry(int ID)
{
    printf("\t\t\t\t[Reader %d:] \t Trying to read \n",ID);
    P(mutex);
    if(wwc>0 || wc>0)
    {
        printf("\t\t\t\t[Reader %d:] \t Blocking for writer\n", ID);
        rwc++;                      // increment waiting reader count
        V(mutex);                   // Let other processes use the mutex
        P(rsem);                    // Sleep on rsem
        rwc--;                      // program now has mutex and rsem, block , go
                                    // into CS
    }
    rc++;
    if (rwc>0)
        V(rsem);                    // If a reader is waiting wake up one reader => Cascade
    else
        V(mutex);
}

void reader_exit(int ID)
{
    P(mutex);
    rc--;                           // I am no longer a reader
    if  (rc==0 && wwc>0)
    {
        V(wsem);                    // if it was the last reader, and there are waiting writers, open
        printf("[Reader %d:] \t Exited\n", ID); }
    else
    {
        V(mutex);                   // the w_sem door for them.
        printf("[Reader %d:] \t Exited\n", ID); }
}

void writer_entry(int ID)
{
    printf("\t\t\t\t[Writer %d:] \t Trying to write \n",ID);
    P(mutex);
    if(rc>0 || wc>0)
    {
        printf("\t\t\t\t[Writer %d:] \t Blocking for other readers or writers\n", ID);
        wwc++;                      // increment waiting writers
        V(mutex);                   // Lets go to the mutex since i will be blocked
        P(wsem);                    // wait in my line, when i wake up i DON'T need a P(mutex) since i've been given it by the waking process.
        wwc--;                      // I'm no longer waiting
    }
    wc++;                           // increment writers
    V(mutex);
}

void writer_exit(int ID)
{
    printf("[Writer %d:] \t Exited\n", ID);
    P(mutex);
    wc--;
    if(rwc>0)
    {
        V(rsem);                   // Lets all reader go
    }
    else if (wwc>0)
    {
        V(wsem);                   // then i let another writer go
    }
    else
    {
        V(mutex);                  //lastly i give up mutex
    }
}

void reader()
{
    int ID;
    P(mutex);
    ID=++global_IDR;
    V(mutex);
    while(1)
    {
        reader_entry(ID);
        printf("[Reader %d:] \t ***READING***\n",ID);
        fflush(stdout);
        sleep(sleeptime);
        reader_exit(ID);
    };
}

void writer()
{
    int ID;
    P(mutex);
    ID=++global_IDW;
    V(mutex);
    while(1)
    {
        writer_entry(ID);
        printf("[Writer %d:] \t ***WRITING***\n",ID);
        fflush(stdout);
        sleep(sleeptime);
        writer_exit(ID);
    };
}


int main()
{
    int reader_count=5;
    int writer_count=3;
    int counter;
    // Create queue for rsem, wsem and mutex
    rsem = (struct semaphore*) malloc(sizeof(struct semaphore));
    wsem = (struct semaphore*) malloc(sizeof(struct semaphore));
    mutex = (struct semaphore*) malloc(sizeof(struct semaphore));
    // Initialize rsem, wsem and mutex
    InitSem(rsem,2);
    InitSem(wsem,1);
    InitSem(mutex,1);
    printf("***********************Starting %d readers and %d writers****************************\n",reader_count,writer_count);
    // Start readers and writers
    for (counter=0;counter<reader_count;counter++)
        start_thread(reader);

    for (counter=0;counter<writer_count;counter++)
    start_thread(writer);

    run();
    return 0;

}
