#include "digitalStopWatch.h"
#include "timeSource.h"

typedef enum{
    stopped,
    started
}State;

struct digitalStopWatch{
    State state;
    TimeSource source;
    const char *name;
};