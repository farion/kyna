#include "kynatimer.h"

KynaTimer::KynaTimer()
 : QTimer()
{
	connect(this,SIGNAL(timeout()),this,SLOT(countUp()));
}



KynaTimer::~KynaTimer()
{
}

void KynaTimer::countUp()
{
	counter--;
	if(counter<=0){
		stop();
		emit end();
	}
}

void KynaTimer::startTimes(int msec, int times)
{
	startCounterValue=times;
	counter=times;
	start(msec);
}

double KynaTimer::getProgress()
{
	if(startCounterValue-counter==0)
		return 0.0;
	return (double) (startCounterValue-counter) / (double) startCounterValue;
}


