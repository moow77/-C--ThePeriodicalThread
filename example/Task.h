#ifndef RUNNABLE
#define RUNNABLE
#include "Runnable.h"
#endif

class Task : public Runnable {
private:
	int task_num, thread_num;
public:
	Task(int);
	void setThreadNum(int);
	void action();
};
