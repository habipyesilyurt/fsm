#include "fsm.h"

/*!
 * \brief fsm_dispatch_event state trigger
 * \param machine State machine that tis state is contained by
 * \param p_event_data Data to be passed to the trigger handling
 * \param event_size Size of the trigger data
 */
void fsm_dispatch_event(FsmStateMachine *machine, void *p_event_data, uint16_t event_size)
{
    UNUSED(event_size);
    FsmState resultState = 0;
    FsmEventData *eventData = (FsmEventData *)p_event_data;

    do{
        if(resultState)
        {
            machine->currentState(machine, TrExit);
            machine->currentState = resultState;
            resultState = machine->currentState(machine, TrEnter);
        }
        else {
            resultState = (FsmState)machine->currentState(machine, eventData->trigger);
        }
    }while(resultState);
}

