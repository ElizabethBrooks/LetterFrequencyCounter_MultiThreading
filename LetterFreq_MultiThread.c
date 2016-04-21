#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include <string.h>

#define THREAD_NUMBER 26 //Number of threads
#define LETTER_NUMBER 26 //Number of letter in the English alphabet

//Global variables for counter letter frequency with multithreading
int letterFreq[LETTER_NUMBER];
pthread_mutex_t threadList[THREAD_NUMBER]; //Allow mutual exclusion of common variables

void * thread_letters(char* fileNameInput)
{
	//Initialize variables for file reading
	int ch;
	int j=0;
	FILE* txtFile = fopen (fileNameInput, "rt"); 
	//Create threads for counting letter frequency
	if (txtFile) 
	{
		while ((ch = getc(txtFile)) != EOF) 
		{
	    		ch = fgetc(txtFile);
	    		if (ch == EOF) break; //End of file or read error (typically -1)
	    		//Assuming ASCII "letters" are "a to z", upper and lower case are included
	    		if ('a' <= ch && ch <= 'z') //Lower case letters
			{
				j = ch-’a’;
				pthread_mutex_lock(&threadList[j]); //Lock the variable
				letterFreq[j]++;
				pthread_mutex_unlock(&threadList[j]); //Unlock the variable
				}
	    		} else if ('A' <= ch && ch <= 'Z') //Upper case letters
			{
				j = ch-’A’;
				pthread_mutex_lock(&threadList[j]); //Lock the variable
				letterFreq[j]++;
				pthread_mutex_unlock(&threadList[j]); //Unlock the variable
				}
			} //End else, if
			//Clear the buffer
			fflush(stdout);
		} //End while
		fclose(txtFile); //Close the text file
	} //End if	
	//End thread process
	pthread_exit(NULL);
} //End thread_letters

int main(void)
{
	//Initialize variables
	char fileName[100];
	//Request user to input text file name
	printf("Please enter the text file name, type, and path: \n");
	scanf("%s",&fileName);	
	//Divide the input text file into pieces for multiple thread processes

	//Create threads for counting letter frequency
	int Error = pthread_create(&threadList[i],NULL,thread_letters,fileName);
	if (Error)
	{
		printf("Error creating thread...\n");
		exit(-1);
	}
	//Combine threads
	for(int l=0; l<THREAD_NUMBER; l++)
	{
		pthread_join(threadList[l],(void **)0);
	}
	//Print results to the screen
	//printf("letterFreq is currently:%d\n",letterFreq);	
	//End of program return statement
	return 0;
} //End main
