//
//  main.c
//  lab2
//
//  Created by Anisha Halwai on 14/09/21.
//  Copyright © 2021 Anisha Halwai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "unp.h"

int term;
pid_t all[100];
void sig_chld(int signo);
int main(int argc, const char * argv[]) {
	// insert code here...
	int n=0; //number of children to be swap
	pid_t p;
	Signal(SIGCHLD,sig_chld);
	
	printf("Number of children to spawn: ");
	scanf("%d",&n);
	printf("Told to spawn %d children\n",n);
	
	//create n number of
	for(int i=0;i<n;i++){
			fflush(stdout);
			p=fork();

			if(p==-1){
				perror( "fork() failed\n" );
				return EXIT_FAILURE;
			}
			//child process

			if(p==0){
				srand(getpid());
				int sleep_time = rand()%5;
				printf("Child PID %d dying in %d seconds.\n",getpid(),sleep_time);
				sleep(sleep_time);
				printf("Child pid %d terminating\n",getpid());
				exit(0);
			}
//			//parent
			if(p>0){
				printf("Parent spawned child PID %d\n",p);
			}
	}
	
	int t=0;
	while(t<n){
		sleep(10);
		printf("Parent sees child PID %d has terminated.\n",all[t]);
		t++;
	}
	
	return 0;
}

void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;
	
	
	while ((pid = waitpid(-1, &stat, WNOHANG))>0){
		all[term]=pid;
		term++;
	}
	
	return;
}
