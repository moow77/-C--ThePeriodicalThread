#include <queue>
#ifndef RUNNABLE
#define RUNNABLE
#include "Runnable.h"
#endif

using namespace std;

class PeriodicalThread {
private:
	int pool_size, thread_num, interval;
	void execute();
	
public:
	PeriodicalThread();
	PeriodicalThread(int);
	void AddTask(Runnable* );
};
