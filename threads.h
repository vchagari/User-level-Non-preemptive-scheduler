#include "q.h"

tcb_t *Q;
int threads=0;

void start_thread(void (*function)(void))
{ // begin pseudo code
//allocate a stack (via malloc) of a certain size (choose 8192)
void *stackP = malloc(8192);
//allocate a TCB (via malloc)
tcb_t *tcb = (tcb_t *) malloc(sizeof(tcb_t));
//call init_TCB with appropriate arguments
init_TCB (tcb,function, stackP, 8192);
tcb->payload = ++threads;
//call addQ to add this TCB into the “RunQ” which is a global header pointer
AddQueue(&Q,tcb);

//printf("\n\tThread %d",threads);
DisplayQ(&Q);
//end pseudo code
}

void run()
{
ucontext_t parent;     // get a place to store the main context, for faking
getcontext(&parent);
swapcontext(&parent, &(Q->context));  // start the first thread
}


void yield() // similar to run
{
DisplayQ(&Q);
//rotate the run Q;
tcb_t *curr = Q;
tcb_t *RunQ = RotateQ(&Q);
//swap the context, from previous thread to the thread pointed to by runQ
//printf("\nswitching from Thread %d to Thread %d",curr->payload,RunQ->payload);
swapcontext(&(curr -> context), &(RunQ->context));
}

