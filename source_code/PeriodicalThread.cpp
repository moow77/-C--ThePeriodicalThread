#include <iostream>  // for cout
#include <stdlib.h>  // for exit
#include <pthread.h>
#include <ctime>

#include "PeriodicalThread.h"

using namespace std;

void* periodical_thread(void*);
void delay();

deque<Runnable*> q_task4pthread;
Runnable *ptr_task4pthread;
int temp_interval;

// the mutex and condition for q_task4pthread
pthread_mutex_t mutex4pthread;
pthread_mutex_t count_mutex4pthread = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var4pthread = PTHREAD_COND_INITIALIZER;

PeriodicalThread::PeriodicalThread() {
	this->thread_num = 0;
	this->pool_size = 1;
	interval = 10;
	temp_interval = interval;
}

PeriodicalThread::PeriodicalThread(int interval) {
	this->thread_num = 0;
	this->pool_size = 1;
	
	if (interval > 0)
		this->interval = interval;
	else
		this->interval = 10;
	
	temp_interval = interval;
}

void PeriodicalThread::AddTask(Runnable* task) {	
	pthread_mutex_lock(&mutex4pthread);
	q_task4pthread.push_back(task);
	pthread_mutex_unlock(&mutex4pthread);

	if (this->thread_num < this->pool_size) {
		++this->thread_num;
		execute();
	} else {
		//cout << "[PeriodicalThread] Try to signal the sleeping thread." << '\n';
		pthread_cond_signal(&condition_var4pthread);
	}
}

void PeriodicalThread::execute() {
	pthread_t thread_id;
	int result = pthread_create(&thread_id, NULL, &periodical_thread, NULL);

	if (result != 0) {
		cout << "Error: Fail to create a thread!!\n" << '\n';
		exit(EXIT_FAILURE);
	}
}

void* periodical_thread(void* input) {
	deque<Runnable*>::iterator start, end;
	while (true) {
		if (!q_task4pthread.empty()) {
			pthread_mutex_lock(&mutex4pthread);
			start = q_task4pthread.begin();
			end = q_task4pthread.end();
			pthread_mutex_unlock(&mutex4pthread);

			delay();
			
			time_t now = time(0);
			// convert now to string form
			char* dt = ctime(&now);
			cout<<"[PeriodicalThread] Start at "<<dt;
			
			for(deque<Runnable*>::iterator iter = start; iter != end; ++iter) {
				(*iter)->run();
			}
		} else {
			// no task need to be executed, waiting for the signal
			pthread_mutex_lock(&count_mutex4pthread);
			pthread_cond_wait(&condition_var4pthread, &count_mutex4pthread);
			pthread_mutex_unlock(&count_mutex4pthread);
		}
	}
	cout << "[PeriodicalThread] Ending the thread pool." << '\n';
}

void delay() {
	time_t t_current = time(0);
	struct tm * current = localtime(&t_current);
	int time4start = temp_interval
			- (60 * current->tm_min + current->tm_sec) % temp_interval;
	sleep(time4start);
}
