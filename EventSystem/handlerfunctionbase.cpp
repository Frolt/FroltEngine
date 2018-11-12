#include "handlerfunctionbase.h"


void HandlerFunctionBase::exec(Event *event)
{
    call(event);
}
