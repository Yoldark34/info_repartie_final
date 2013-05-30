#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main (int argc, char** argv)
{
	pid_t pidFils;
	pid_t pidPetitFils;  
	int  tube1 [2];
	int  tube2 [2];
	int  tube3 [2];
	pipe (tube1);  
	pipe (tube2); 
	pipe (tube3); 


	pidFils = fork ();

	switch (pidFils)
	{
	case -1 : perror ("Pere       : Pb pour creer le processus fils : ");
		break;
	case  0 : pidPetitFils = fork ();
		switch (pidPetitFils)
		{
		case -1 : perror ("Fils       : Pb pour creer le processus petit-fils : ");
  			break;
		case  0 : printf ("Petit-fils : Je suis le processus petit-fils -> PID = %d\n", getpid());
		close (tube2[0]);
		close (tube3[1]);
		close (tube1[0]);
		close (tube1[1]);
			break;
		default : printf ("Fils       : Je suis le processus fils -> PID = %d\n", getpid()); 
		close (tube1[0]);
		close (tube2[1]);
		close (tube3[0]);
		close (tube3[1]);
		}

		break;

	default : printf ("Pere       : Je suis le processus pere -> PID = %d\n", getpid());               
		close (tube3[0]);
		close (tube1[1]);
		close (tube2[0]);
		close (tube2[1]);
	}

	return 0;
}
