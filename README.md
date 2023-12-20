# Simple_Shell_In_Unix_Terminal_In_C

--FIRST PART--
The first part of the project is a simple command parsing in the shell. The shell will execute the task as a single command. Before waiting for input(data that is stored in the buffer), the user writes a shell prompt and when the command completes, the shell should print another prompt through a child process. 

We make use of Linux system calls in the provided source code. Some are programs and others are built-in. Some examples of built-in commands besides ls are cd and exit. The shell is initialized to show the user that the shell is loaded with system print command. Next, per the task instructions, read PATH environment variable, search the directory with a detailed list of files using the “ls” command. We use system function calls read(), fork(), execv(), wait(). Again, the shell is initialized, command line read and parsed. After, child process is created by using fork(), wait for the child process to terminate, and finally exit the shell. The condition variable notifies the waiting thread when to enter its critical section. This is important to note that synchronization occurs within the kernel space and when conducting part two of the lab, it is at the user level.

 --SECOND PART--
The second part pertains to refining the parsing logic with the use of the environment variable to search for commands. When the exercise is done, the shell should be able to execute simple commands then exit. 

Using the POSIX threading extensions—pthread.h—this is the protocol for synchronization and IPC(interprocess communication). Pthreads and its subset are executed for real-time process control. We can compile and run the source code without modification. Saying, that we run the source code without modification, there is no need to reimplement any binaries that already exist, such as the “ls” command for example. The processes are launched and scheduled accordingly.

When the multi-threaded program starts executing, the main() function is running. Next, the id for the created thread is declared using pthread_t. Then a child process is created by calling the “pthread_create()”. After the thread is created, the thread function will execute the command. Both threads share and work on the environment variable(s). Next, parent thread waits for the child thread to exit using the pthread_join(threadId[i], NULL) system function. This blocks the calling thread until the thread-specific data has been executed.

All of this runs concurrently with the first thread reading information from the command line and the second thread executing data from the first thread. 

