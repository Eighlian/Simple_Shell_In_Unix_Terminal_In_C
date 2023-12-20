#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define WHITESPACE " ,\t\n"
#define BUFFER_SIZE 1000
#define MAX_ARGS 64
#define MAX_ARG_LEN 16



//initialize with loaded screen to show user that the shell has been loaded.
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


//This is the prompt that will act as a txt/cmd line.
void printPrompt()
{
    printf("Simple-Shell$  ");
}
	//getter function for the paths of current dir
char *getPath()
{
       char *path = getenv("PATH");
	   //returns the paths of type char.
       		 return strdup(path);
}

//main.. this starts the shell. while true get commands and search.. 
//if command is found fork() execute command and return back to main aka parent loop.
int main(int argc, char **argv)
{

	//initialize or show that the shell is running
	init_shell();
	//while true run the shell and wait for commands
    while (1)
    {
        // Output the prompt that is shown to enter commands 
        printPrompt();

// ############################## Get Input SECTION ########################################


        // read input and send it to the buffer.
        char buffer[BUFFER_SIZE] = {};
        //get the input from stdin and put into buffer.
        fgets(buffer, BUFFER_SIZE, stdin);

 		//get the command.
        char *current_cmd = strtok(buffer, WHITESPACE);
		//save command to current_cmd temp char.
        char *command = current_cmd;
		//if command is NULL continue waiting.
        if (command == NULL)
        {
            continue;
        }

        // array of command args.
        char *args[MAX_ARGS];
        // set first space to the command.
        args[0] = command;

        // go through the array and keep track with arg_index.
        size_t arg_index = 0;

        // While not at the end of curent_cmd
        while (current_cmd != NULL)
        {
			//keep reading 
            current_cmd = strtok(NULL, WHITESPACE);
			//increment.
            args[++arg_index] = current_cmd;
        }

        // pointer paths getPaths.
        char *paths = getPath();

        // 0 or 1 true or false
        int path_found = 0;

        // keep track of each path.
        char *current_path = strtok(paths, ":");
        // executable path
        char *executable_path;
			
			//while there are paths to search
          while (current_path != NULL)
        {
           // keep adding and going through paths.
            executable_path = strdup(current_path);
			// slash for paths.
            strcat(executable_path, "/");
            strcat(executable_path, command);

            // if the path exe is good ==0
            if (access(executable_path, X_OK) == 0)
            {
                // Set path_found will equal 1 which means found.
                path_found = 1;
                // break get out of loop
                break;
            }
			
			//reset the current_path to null.
            current_path = strtok(NULL, ":");

        }

        	//if path could not be found then return 
        if (path_found == 0)
        {	
			//command could not be found.
            printf("CMD not valid!\n");
            continue;
        }

// ############################## Fork SECTION ########################################
        // create the fork so the command can run.
        pid_t pid = fork();
		
		//if pid ==0
        if (pid == 0)
        {
            // run command with args.
            execv(executable_path, args);
            // child run
			//exit
            exit(0);
        }
        else
        {
            // parent wait to finish child.
            wait(NULL);
        }
    }

    return 0;
}
