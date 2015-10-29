/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    const char s[2] = " ";
    char *token;
    char cwd[1024] = { 0 };

    // Parse the commands provided using argc and argv
    
    // Perform an infinite loop getting command input from users
    if (getcwd(cwd,sizeof(cwd)) != NULL) {
      printf("%s:$ ", cwd);
    }
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument
	printf("%s:$ ", cwd);  
	
        token = strtok(buffer, s);
	
	strcpy(command, token);
	token = strtok(NULL, s);
	if (token != NULL) {
	   strcpy(arg, token);
           arg[strlen(arg) - 1] = '\0';
	}
	else 
	{
	   strcpy(arg, " ");
	   command[strlen(command) - 1] = '\0';
        }
	
	

	//printf("command: %s    arg:  %s\n", command, arg);

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
            if (chdir(arg) == -1) {
               printf("Could not change directory...\n");
               printf("%s:$ ", cwd);
             }
            else {
	      strcpy(cwd, arg);
            }
        }

        // other commands here...
        
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }

        // clr command -- Clear the screen
        else if (strcmp(command, "clr") == 0)
        {
            for (int i = 0; i < 80; i++) {
	       printf("\n");
            }
            printf("%s:$ ", cwd);
         }

         // dir command -- List the contents of a directory
         else if (strcmp(command, "dir") == 0 )
         { 
           DIR *dp;
           struct dirent *ep;
           if (strcmp(arg, " ") == 0 ) 
              dp = opendir("./");
           else
              dp = opendir(arg);
           if (dp != NULL) {
              while (ep = readdir (dp))
                 puts (ep->d_name);

              (void) closedir(dp);
            }
           else {
              printf("Couldn't open the directory\n");
              
           }
           printf("%s:$ ", cwd);
         }
         //pause command
         else if (strcmp(command,"pause") == 0 )
         {
            while(getchar() != '\n');
               
         }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
    }
    return EXIT_SUCCESS;
}
