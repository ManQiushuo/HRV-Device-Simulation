#include "hrvtable.h"

HRVtable::HRVtable()
{
    cohTable<<90<<40<<95<<45<<90<<40<<85<<35<<90<<40;
    incTable<<40<<90<<20<<110<<60<<80<<50<<100<<30<<85;
    cohScoreTable<<0.2<<0.7<<1.6<<2.4<<3.8<<5.7<<6.6<<7.3<<4.4<<6.7;
    incScoreTable<<0.5<<1.9<<0.4<<3.1<<6.3<<2.2<<0.5<<0.3<<0.8<<0.9;
}

int HRVtable::cohGetAt(int index){ return cohTable[index]; }

int HRVtable::incGetAt(int index){ return incTable[index]; }

float HRVtable::cohScoreGetAt(int index){ return (float) cohScoreTable[index]; }

float HRVtable::incScoreGetAt(int index){ return (float) incScoreTable[index]; }

