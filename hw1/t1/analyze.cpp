/*
*	File: 		analyze.cpp
*
*	Course:		EECE 494
*	Description:
*
*	Team:		Nick Adams
*			Oscar Lee
*			Catherine Wang
*			Jack Wu
*
*/



/* ---- Include Files ------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

#include "task.h"
#include "scheduling.h"

using namespace std;

/* ---- Public Constants and Types ---------------------------------------- */
typedef struct
{
	double exec_time;
	double relative_deadline;
	double period;
} task_t;
/* ---- Public Variables --------------------------------------------------- */
unsigned int num_tasks = 0;
task_t *task_set = NULL;
task_t *exec_task = NULL;

/* ---- Public Function Prototypes ----------------------------------------- */
void usage ();

/* ---- Private Constants and Types ---------------------------------------- */
/* ---- Private Variables -------------------------------------------------- */
/* ---- Private Function Prototypes ---------------------------------------- */
/* ---- Functions ---------------------------------------------------------- */	



int main (int argc, char *argv [])
{	

	Task task(0.0,0.0,0.0);
	list<Task> list;
	
	list.push_back(task);
	Scheduling schedule(list);
	 
	
	FILE *file;           
   	char line[80];
  	char *tok;
	int i=0, j;

	if(argc != 2) usage();

	// Get Number of Tasks in the Set
	file = fopen (argv[1], "rt");  
	if(file == NULL) return 0;
	while(fgets(line, 80, file) != NULL) num_tasks++;
	num_tasks -= 2;		
   	fclose(file); 

	task_set = (task_t *) malloc (num_tasks * sizeof(task_t));

	// Fill Task Set
	file = fopen (argv[1], "rt");  
	if(file == NULL) return 0;
	while(fgets(line, 80, file) != NULL) 
	{
		tok = strstr(line, "begin");
		if(tok) continue;
		tok = strstr(line, "end");
		if(tok) continue;

		tok = strtok(line, " ");	
		j = 0;	
		while (tok != NULL)
		{
			if(j > 2) exit(0);
			
			switch(j) 
			{
				case 0:	task_set[i].exec_time = atof(tok);
					break;

				case 1:	task_set[i].relative_deadline = atof(tok);
					break;

				case 2:	task_set[i].period = atof(tok);
					break;

				default: 
					break;
			}
			tok = strtok(NULL, " ");	
			j++;
		}
		i++;
	}
   	fclose(file); 	


	for(i=0 ; i<num_tasks ; i++) 
	{
		printf("[%i]: exec_time(%.2f) ", i, task_set[i].exec_time);
		printf("relative_deadline(%.2f) ", task_set[i].relative_deadline);
		printf("period(%.2f)\n", task_set[i].period);
	}

	return 0;
}


/*
* usage
*
* @desc:
*
*/
void usage ()
{
	fprintf(stderr, "\nUsage: analyze [input_file]\n\n");
}
