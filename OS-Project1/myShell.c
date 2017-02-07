/*--------------*********************************^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*********************************--------------/*
                                                 University of Texas at Dallas--Computer Science Program
                                                       CS 5348 Operating Systems Concepts Fall 2016
                                                                         Project 1
                                                   submission by Uday Singh & Shashank Chandrashekhara
                                               Please see Project-1.doc for more information on the project
                                                                  Compile with: gcc test1.c
/*--------------*********************************^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*********************************--------------*/

#include <sys/signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*                                               *******************************************************                                               /*
                                                         The below code is the Tokenizer block.
                                            It parse the array of command[] into arguments by tokenizing it
/*                                               *******************************************************                                               */
void  Tokenizer(char *command, char **argv)
{
char *token;//a character pointer to hold the token returned after tokenizing the command string
int i=0;//integer i to track the arguments in *argv[],//initialize the number of arguments passed to 0
token = strtok(command," ");//The first token is returned by using strtok() which resides in string.h header file
   while( token != NULL )//while the strtok() returns tokens that aren't null
   {
      argv[i]= token;//assign address of *token to argv[]
      i++;//and increament the argv[]
      token= strtok(NULL, " ");//to return the next token from the command[]
   }
   argv[i]='\0';//terminate the argv[] with '\0'
}

/*                                               *******************************************************                                               /*
                         The below code is the execution block.It creates a new process and lets the child execute the user’s command,
                                          waits for the child to terminate and then goes back to beginning of the loop.

/*                                               *******************************************************                                               */
int execute(char **argv, int count)
{
pid_t pid;//Variable to take the return from the fork() system call
    {//if argument is not equal to null
                pid=fork();//execute a fork() call and collect the returned process id in variable pid
                if(pid<0)
                {//if pid is less then 0
                    printf("fork failed");//then the fork system call has failed to execute
                }
                else if(pid==0)
                {//else if pid is equal to 0
                if(execvp(*argv,argv)<0)
                    {
                        printf("exec failed\n");
                    }//make a exec system call over arguments in *argv[], and display "exec failed" if the it returns less then 0
                }
                else
                {
                    if(waitpid(NULL)>=0)//wait for the child to return, if it return greater then equal to 0, then the process has executed successfuly
                    {
                        return ++count;// increment the counter for total number of commands executed
                    }
                    printf("Child Exited\n");//prints child exited after each child exit
                }
            }

}
int main(){
/*                                               *******************************************************                                               /*
                                                                Variable declaration block
/*                                               *******************************************************                                               */
char command[1000];//this is the string that reads the command typed on the keyboard  terminated by '\n'
/* The array below will hold the arguments: argv[0] is the command.argv[1] is the 1st aurgument to the command and so on */
char *argv[50];
int count=0;//this variable counts total number of commands executed

printf("/* **************^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^***************** /*\n");
printf("                University of Texas at Dallas--Computer Science Program\n");
printf("                     CS 5348 Operating Systems Concepts Fall 2016\n");
printf("                                        Project 1\n");
printf("                  submission by Uday Singh & Shashank Chandrashekhara\n");
printf("              Please see Project-1.doc for more information on the project\n");
printf("                                Compile with: gcc test1.c\n");
printf("/* ***************^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^**************** */\n");
/*                                               *******************************************************                                               /*
                                    Infinite shell loop, It executes in a loop until user types exit on the keyboard.
                                               Itreads the command typed on the keyboard  terminated by \n
/*                                               *******************************************************                                               */
while(1) //Infinite loop
{
printf("Please type the command-->");//Prompts the user for the command
gets(command);//takes the command entered in command variable
Tokenizer(command, argv);//This function calles the tokenizer() defined above
/*                                               *******************************************************                                               /*
                                The below code is the exit block.If the command typed is exit, then your program terminates
                                after printing the total number of commands executed just before the program was terminated.

/*                                               *******************************************************                                               */

if(*argv!=NULL && strcmp(*argv,"exit") == 0)//Checks if argument passed is equal to exit, we are checking if argv is null because otherwise the propram will error out
                                            //when null is compared to "exit, if nothing is entered.
{
    printf("Number of commands fired = %d\n",count);//returns total number of commands executed
    break;//breaks out of the infinite loop
}
else
    {//else if argument is not exit
    if(*argv!=NULL)
          count=execute(argv,count);//This function calls the execute() function which is the fork+exec block the program
    else printf("No Input Entered\n");//displays No Input Entered if nothing is entered int the console
    }//else ends
}//while loop ends
}//end of program
