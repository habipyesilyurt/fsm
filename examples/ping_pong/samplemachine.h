#ifndef SAMPLEMACHINE_H
#define SAMPLEMACHINE_H
#include "fsm.h"

#ifdef __cplusplus
extern "C"{
#endif

enum TestTransitions{
    TrTick = TrUserTransition,
};
typedef enum TestTransitions TestTransitions;
typedef struct SampleMachine SampleMachine;
struct SampleMachine{
    FsmStateMachine api;
};

FsmStateMachine *SampleMachineInit(SampleMachine* me);

#ifdef __cplusplus
}
#endif

#endif // SAMPLEMACHINE_H
