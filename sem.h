#include "threads.h"

//Create Semaphore Data structure
struct semaphore {
int values;
tcb_t *semQ;
};

typedef struct semaphore semaphore_t;

//Initialize semaphore with the specified value
void InitSem(semaphore_t *S,int val)
{
    InitQueue(&(S->semQ));
    S->values=val;
}

// Semaphore wait and block process in the Q
void P(semaphore_t *S)
{
    S->values--;
    if(S->values<0)
    {
        AddQueue(&(S->semQ),DelQueue(&Q));
        swapcontext(&(S->semQ->prev->context),&(Q->context));
    }

}

//  Takes a PCB out of the semaphore queue and puts it into the run queue.
void V(semaphore_t *S)
{
    S->values++;
    if(S->values <= 0){
    AddQueue(&Q,DelQueue(&(S->semQ)));
	}
	yield();   //"yields" to the next runnable process

}
