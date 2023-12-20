#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define BUFFER_SIZE 1000
#define MAX_COUNT 10 // Change MAX_COUNT as per maximum number of commands possible


// ##############################  Thread function  ########################################
void ThreadFunc(char *command)
{
    int ret = 0;

    //debugging to show errors or success
   /* if (NULL == command)
    {
        printf("ERROR::Input pointer argument is NULL\n");
        return;
    }
    if ('\0' == command[0])
    {
        printf("ERROR::Input command string is EMPTY\n");
        return;
    }

    
    if (0 != ret)
    {
        printf("ERROR::system(%s) failed. errno=%d\n", command, errno);
    }
    else
    {
        printf("SUCCESS::system(%s) succeeded\n", command);
    }
    */
   //system command
   ret = system(command);
}


//This is the prompt that will act as a txt/cmd line.
void printPrompt()
{
    printf("Simple-Shell$  ");
}
//This runs once the shell has started. It acts as initialization.
void init_shell() {
    printf("******************************************************************************\n");
    printf("  #####                                    #####                              \n");
    printf(" #     # # #    # #####  #      ######    #     # #    # ###### #      #      \n");
    printf(" #       # ##  ## #    # #      #         #       #    # #      #      #      \n");
    printf("  #####  # # ## # #    # #      #####      #####  ###### #####  #      #      \n");
    printf("       # # #    # #####  #      #               # #    # #      #      #      \n");
    printf(" #     # # #    # #      #      #         #     # #    # #      #      #      \n");
    printf("  #####  # #    # #      ###### ######     #####  #    # ###### ###### ###### \n");
    printf("******************************************************************************\n");
    printf("\n");
	printf("Group Members: Bradley Allen, Januario Fuentes, Adam Burris\n\n");

}


// ##############################  Main function  ########################################
int main () 
{
    //show initialization
    init_shell();
    //while shell is running
    while(1)
    {

    //show shell prompt
    printPrompt();
    //get input
    char buffer[BUFFER_SIZE] = {};
    fgets(buffer, BUFFER_SIZE, stdin);
    //send the buffer to command.
    char* command[] = {buffer, NULL};
    //declare  variables
    int i = 0;
    int count = 0;
    int ret = 0;
    pthread_t threadId[MAX_COUNT]; // Change MAX_COUNT as per maximum number of commands possible

    //while the command is not null
    while (NULL != command[i])
    {
        //create pthread to run function.
        ret = pthread_create(&threadId[i], NULL, (void *(*)(void *))ThreadFunc, (void *)command[i]);
        if (0 != ret)
        {
            //printf("ERROR::pthread_create() failed for command %s. errno = %d\n", command[i], errno);
        }
        else
        {
            //printf("SUCCESS::pthread_create() succeeded for command %s\n", command[i]);
            count++; // update i
        }
        i++;//increment.
    }

    // pthread_join to wait till all thread are finished
    for (i = 0; i < count; i++)
    {
        pthread_join(threadId[i], NULL);
    }

    //count = 0 to restart amount of threads.
    count =0;

    }

    return 0;
}
