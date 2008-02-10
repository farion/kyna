#include "kynabuff.h"
#include "kynaunit.h"

KynaBuff::KynaBuff ( int buffType, int value, KynaUnit *unit )
{
	this->buffType = buffType;
	this->unit = unit;
	this->value = value;
}

int KynaBuff::getValue()
{
	return value;
}

void KynaBuff::setValue ( int value )
{
	this->value += value;
}

int KynaBuff::getType()
{
	return buffType;
}

