#include "date_wrapper/Dummy.h"

Dummy::Dummy(int val) :
    value{val}
{
}

int Dummy::getValue() const
{
    return value;
}
