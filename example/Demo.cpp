#include "ThreadPool.h"
#include "PeriodicalThread.h"
#include "Task.h"

int main() {
	Task *task1 = new Task(1);
	Task *task2 = new Task(2);
	Task *task3 = new Task(3);

	PeriodicalThread *pool = new PeriodicalThread();
	pool->AddTask(task1);
	pool->AddTask(task2);
	pool->AddTask(task3);
	
	for(;;);
}
