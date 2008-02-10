#ifndef KYNATIMER_H
#define KYNATIMER_H

#include <cmath>

#include <QDebug>
#include <QTimer>


class KynaTimer : public QTimer
{
	Q_OBJECT;

public:
    KynaTimer();
	void startTimes(int msec,int times);
	double getProgress();
    ~KynaTimer();

private:
	int startCounterValue;
	int counter;

private slots:
	void countUp();

signals:
	void end();

};

#endif
