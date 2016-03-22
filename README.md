# The thread pool executing tasks periodically in C++
This is the thread pool in C++ with a similar feature as Java API schedulAtFixedRate. With this thread pool, programmers can put some tasks in it and make these tasks be executed periodically. The source code of it is in the folder “source_code”.

# How to use it
Please refer to the example code in the example folder. When the example code is executed, it will show the message similar as below.

[PeriodicalThread] Start at Mon Mar 21 16:08:30 2016

[Task] task 1 is running

[Task] task 2 is running

[Task] task 3 is running

[PeriodicalThread] Start at Mon Mar 21 16:08:40 2016

[Task] task 1 is running

[Task] task 2 is running

[Task] task 3 is running

# The next step
I am keeping improving this thread pool for making it better. If you have any suggestion for it, please tell me without hesitation.
