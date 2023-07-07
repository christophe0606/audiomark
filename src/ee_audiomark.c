#include <stdio.h>
#include "ee_audiomark.h"

#include "scheduler.h"
#include "cg_status.h"

char *spxGlobalHeapPtr;
char *spxGlobalHeapEnd;
long  cumulatedMalloc;

int
ee_audiomark_initialize(void)
{
    printf("Memory alloc summary:\n");
    int err = init_scheduler();
    return(err);
}

void
ee_audiomark_release(void)
{
    free_scheduler();
}


int
ee_audiomark_run(void)
{
    int error;
    uint32_t nbSched=scheduler(&error);
    
    if (error != CG_STOP_SCHEDULER)
    {
      return(error);
    }
    else
    {
        return 0;
    }
}

