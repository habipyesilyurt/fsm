#include "samplemachine.h"

//state declarations
STATE_DECLARE(StPing);
STATE_DECLARE(StPong);
STATE_DECLARE(StInitial);


extern void sample_fsm_put(SampleMachine *me, void *p_event_data, uint16_t event_size);

static void __api_put(SampleMachine *me, void *p_event_data, uint16_t event_size);

/*!
 * \brief SampleMachineInit Initialize a state machine
 * \param me State machine structure allocated by caller
 * \return  returns the state machine pointer
 *
 * Simply initializes a state machine making required binding and setting the initial state
 */
FsmStateMachine *SampleMachineInit(SampleMachine *me)
{
    //make api bindings
    me->api.put = __api_put;
    //set the initial state
    me->api.currentState = STATE(StInitial);
    return &me->api;
}


static void __api_put(SampleMachine *me, void *p_event_data, uint16_t event_size)
{
    sample_fsm_put(me, p_event_data, event_size);
}



//state machine
void enterPing(FsmStateMachine *me)
{
    printf("Ping entered\r\n");
}

void enterPong(FsmStateMachine *me)
{
    printf("Pong entered\r\n");
}

void tickEventHandler()
{
    printf("Tick event triggered\r\n");
}



STATE_BEGIN(StPong, NO_STATE())
ADD_TRIGGER(TrEnter, NO_STATE(), enterPong)
ADD_TRIGGER(TrTick, STATE(StPing), tickEventHandler)
STATE_END(0)

STATE_BEGIN(StPing, NO_STATE())
ADD_TRIGGER(TrEnter, NO_STATE(), enterPing)
ADD_TRIGGER(TrTick, STATE(StPong), tickEventHandler)
STATE_END(0)

STATE_BEGIN(StInitial, NO_STATE())
ADD_TRIGGER(TrTick, STATE(StPing), NO_ACTION())
STATE_END(0)

