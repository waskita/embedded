#include <stdio.h>
#include <stdlib.h>

#define STATE_ON 1
#define STATE_OFF 0
#define STATE_2 2

int main()
{
    int i;
    int fsm_state=0;
    int fsm_output=0;
    int fsm_counter=0;
    printf("Hello world!\n");
    fsm_state=STATE_OFF;

    for(i=0; i<10; i++)
    {
        fsm(&fsm_state,fsm_output,&fsm_counter);
        printf("%d %d %d\n",i,fsm_state,fsm_counter);
    }
    return 0;
}

int fsm( int *state,int *output,int *counter)
{
    switch(*state)
    {
    case STATE_OFF:
    {
        *state=STATE_ON;
        *counter=0;
        break;
    }
    case STATE_ON:
    {
        if (*counter<1)
        {
            *counter=*counter+1;

//            printf("xxx");
        }
        else
        {
            *state=STATE_OFF;
        }
        break;
    }
    default:
    {
    }
    }
    return 0;
}
