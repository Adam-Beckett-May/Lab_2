/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <Adam Beckett May (100487239), Robert Kocovski (100536625), Daniel Ola (100523811), Andrew Lau (100522457)>
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
    char buffer2[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    const char s[2] = " ";
    char *token;
    char cwd[1024] = { 0 };
    char shell_path[1024] = { 0 };

    // Parse the commands provided using argc and argv

    // Perform an infinite loop getting command input from users
    if (getcwd(cwd,sizeof(cwd)) != NULL) {
      printf("%s:$ ", cwd);
    }
    strcpy(shell_path,cwd);

    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {

        strcpy(buffer2, buffer);    //will need a copy of buffer for echo command

	// Perform string tokenization to get the command and argument
        token = strtok(buffer, s);
	strcpy(command, token);
	token = strtok(NULL, s);    //get argument
	if (token != NULL) {
	   strcpy(arg, token);
           arg[strlen(arg) - 1] = '\0';
        }
	else
	{
	   strcpy(arg, " ");          //  there is no argument
	   command[strlen(command) - 1] = '\0';   //need to dispose of newline character

        }



        // Check the command and execute the operations for each command

        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
            if (strcmp(arg, " ") == 0){        // if arg is empty do not change directory
               printf("%s:$ ", cwd);           //print prompt
            }
            else if (chdir(arg) == -1) {           //change directory
               printf("Could not change directory...\n");
               printf("%s:$ ", cwd);
             }

            else  {                          // copy new directory and print prompt

	      strcpy(cwd, arg);
              printf("%s:$ ", cwd);

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
            printf("Press Enter to exit pause");
            while (getchar() != '\n')       //loop till newline character entered
               ;
            printf("%s:$ ", cwd);
         }

	//command for echo
         else if (strcmp(command, "echo") == 0)
         {

                for (int i = 5; i < BUFFER_LEN; i++) {  //get only argument portion of buffer

		printf("%c",buffer2[i]);
                }
                printf("%s:$ ", cwd);
         }

        //command for environ
        else if (strcmp(command, "environ") == 0)
        {
          printf("PWD=%s\n",cwd);
          printf("SHELL=%s",shell_path);
          printf("/myshell\n");
          printf("%s:$ ", cwd);
         }
         //command for help
        else if (strcmp(command, "help") == 0)
        {
            system("more /home/osboxes/readme");
	    printf("%s:$ ", cwd);
        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
            printf("%s:$ ", cwd);
        }
        strcpy(arg, "");
    }

    return EXIT_SUCCESS;
}
