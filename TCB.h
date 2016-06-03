#include <ucontext.h>
#include <string.h>

// Define a struct tcb with its member
struct tcb {
ucontext_t context;
struct tcb *prev;
int payload;
struct tcb *next;
};

//definition as tcb_t
typedef struct tcb tcb_t;


// initialize the tcb
void init_TCB (tcb_t *tcb, void *function, void *stackP, int stack_size)
// arguments to init_TCB are
//   1. pointer to the function, to be executed
//   2. pointer to the thread stack
//   3. size of the stack
{
memset(tcb, '\0', sizeof(tcb_t));       // wash, rinse
getcontext(&tcb->context);              // have to get parent context, else snow forms on hell
tcb->context.uc_stack.ss_sp = stackP;
tcb->context.uc_stack.ss_size = (size_t) stack_size;
makecontext(&tcb->context, function, 0);// context is now cooked
}


