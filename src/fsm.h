#ifndef DOOR_H
#define DOOR_H
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

#define NO_ACTION() 0
#define UNUSED(x) (void)x
#define NO_STATE() 0


typedef struct FsmStateMachine FsmStateMachine;
typedef void (*function_fsm_event_put)(FsmStateMachine *machine, void *p_event_data, uint16_t event_size);

typedef void* (*FsmState)(FsmStateMachine *me, int trigger);
typedef void (*FsmAction)();

struct FsmStateMachine{
    function_fsm_event_put put;
    FsmState currentState;
};


struct FsmEventData{
    int trigger;
};
typedef struct FsmEventData FsmEventData;

enum FsmTranstitions{
    TrTransition,
    TrEnter,
    TrExit,
    TrUserTransition
};
typedef enum FsmTranstitions FsmTranstitions;

/*!
* \brief Declares a state. Simply state function prototype for compiler
* @param state name of the state
*/
#define STATE_DECLARE(state) static void *state##Handler(FsmStateMachine *me, int trigger)

/*!
* \brief Defines a state function name
* @param state name of the state
*/
#define STATE(state) state##Handler

/*!
 * \brief Begins a state
 * @param state name of the state
 * @param parentState Although not implemented, this argument added to definition for future improvements to support hierarchical fsm
 *
 * Simply defines state function, initializes its parent state and opens switch case for transitions
 */
#define STATE_BEGIN(state, parentState) static void *state##Handler(FsmStateMachine *me, int trigger)\
    {\
        switch(trigger) {


/*!
  * \brief Ends a state
  * @param x a function to be called in default case.
  *
  * Simply calls a function if it is present and returns the parent state meaning pass control to parent state
  * since this trigger si not handled here
  */
#define STATE_END(x) \
            default: \
                if(0 != x)\
                    ((FsmState)x)(me, trigger);\
                break;\
            } \
            return 0;\
        }


/*!
  * Adds a trigger handlig code piece to state
  * @param name Name of the trigger. An enumation value or integer value
  * @param nState Next state of the transition. O means no transition is needed.  \ref STATE() macro should be used to convert state name to function
  * @param action A function to handle transition
  */
#define ADD_TRIGGER(name, nState, action)\
    case name :\
    if(action != NO_ACTION() )\
    {\
        ((FsmAction)action)();\
    }\
    return (void *)nState;\
    break;

void fsm_dispatch_event(FsmStateMachine *machine, void *p_event_data, uint16_t event_size);

#ifdef __cplusplus
}
#endif

#endif //DOOR_H
