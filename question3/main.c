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
	int  tube1[2];
	int  tube2[2];
	int  tube3[2];
	pipe (tube1);  
	pipe (tube2); 
	pipe (tube3); 
  int* nb;
int* bufnb;
  int* nb2;
int* bufnb2;
  int* nb3;
int* bufnb3;
pid_t* bufpid;
pid_t* bufpid2;
pid_t* bufpid3;
pid_t my_pid;
pid_t last_pid;
pid_t current_pid;

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
			my_pid = getpid();
			close (tube2[0]);
			close (tube3[1]);
			close (tube1[0]);
			close (tube1[1]);
			srand (1);
			srand (time(NULL));//Because i have always the same number i need to seed the random generator
			nb = (int*) malloc (sizeof(int));
			*nb = (rand() % 10);
			printf ("Petit-fils       : Generation du nombre numero %3d\n", *nb);
			bufnb = (int*) malloc (sizeof(int));
			last_pid = -1;
			do {
				last_pid = current_pid;
				read (tube2[1], bufnb, sizeof(int));
				printf ("Petit-fils       : Lecture du nombre %3d \n", *bufnb);
				bufpid = (pid_t*) malloc (sizeof(pid_t));
				read (tube2[1], bufpid, sizeof(pid_t));
				printf ("Petit-fils       : Lecture du pid %d \n", *bufpid);

				if ( *bufnb >= *nb ) {//Replace by >=
					current_pid = *bufpid;
					printf ("Petit-fils       : Battu a l'élection envoi a Pere le nombre %i\n", *bufnb);
					write (tube3[0], bufnb, sizeof(int));
					printf ("Petit-fils       : Envoi du PID %d\n", bufpid);  
					write (tube3[0], bufpid, sizeof(pid_t));
				} else {
					current_pid = my_pid;
					printf ("Petit-fils       : Gagné à l'élection envoi a Pere mon numéro %i\n", *nb);
					write (tube3[0], nb, sizeof(int));
					printf ("Petit-fils       : Envoi de mon PID %d\n", my_pid);  
					write (tube3[0], &my_pid, sizeof(pid_t));
				}
			} while (last_pid == current_pid);
			break;
		default : printf ("Fils       : Je suis le processus fils -> PID = %d\n", getpid()); 
			my_pid = getpid();
			close (tube1[0]);
			close (tube2[1]);
			close (tube3[0]);
			close (tube3[1]);
			srand (time(NULL));//Because i have always the same number i need to seed the random generator
			nb2 = (int*) malloc (sizeof(int));
			*nb2 = (rand() % 10);

			printf ("Fils       : Generation du nombre numero %3d\n", *nb2); 
			bufnb2 = (int*) malloc (sizeof(int));
			bufpid2 = (pid_t*) malloc (sizeof(pid_t));
			do {
				last_pid = current_pid;
				read (tube1[1], bufnb2, sizeof(int));
				printf ("Fils       : Lecture du nombre %3d \n", *bufnb2);
				
				read (tube1[1], bufpid2, sizeof(pid_t));
				printf ("Fils       : Lecture du pid %d \n", *bufpid2);

				if ( *bufnb2 >= *nb2 ) {//Replace by >=
					current_pid = *bufpid2;
					printf ("Fils       : Battu a l'élection envoi a petit fils le nombre %i\n", *bufnb2);
					write (tube2[0], bufnb2, sizeof(int));
					printf ("Fils       : Envoi du PID %d\n", bufpid2);  
					write (tube2[0], bufpid2, sizeof(pid_t));
				} else {
					current_pid = my_pid;
					printf ("Fils       : Gagné à l'élection envoi a petit fils mon numéro %i\n", *nb2);
					write (tube2[0], nb2, sizeof(int));
					printf ("Fils       : Envoi de mon PID %d\n", my_pid);  
					write (tube2[0], &my_pid, sizeof(pid_t));
				}
			} while (last_pid == current_pid);

		}

		break;

	default : printf ("Pere       : Je suis le processus pere -> PID = %d\n", getpid());
		my_pid = getpid();
		close (tube3[0]);
		close (tube1[1]);
		close (tube2[0]);
		close (tube2[1]);
		srand (time(NULL));//Because i have always the same number i need to seed the random generator
		nb3 = (int*) malloc (sizeof(int));
		*nb3 = (rand() % 10);
		printf ("Pere       : Generation du nombre numero %3d\n", *nb3);  
		bufnb3 = (int*) malloc (sizeof(int));
		bufpid3 = (pid_t*) malloc (sizeof(pid_t));
		*bufnb3 = -1;
		do {
			last_pid = current_pid;
				if ( *bufnb3 >= *nb3 ) {//Replace by >=
					current_pid = *bufpid3;
					printf ("Pere       : Battu a l'élection envoi a fils le nombre %i\n", *bufnb3);
					write (tube1[0], bufnb3, sizeof(int));
					printf ("Pere       : Envoi du PID %d\n", bufpid3);  
					write (tube1[0], bufpid3, sizeof(pid_t));
				} else {
					current_pid = my_pid;
					printf ("Pere       : Gagné à l'élection envoi a fils mon numéro %i\n", *nb3);
					write (tube1[0], nb3, sizeof(int));
					printf ("Pere       : Envoi de mon PID %d\n", my_pid);  
					write (tube1[0], &my_pid, sizeof(pid_t));
				}

				read (tube3[1], bufnb3, sizeof(int));
				printf ("Pere      : Lecture du nombre %3d \n", *bufnb3);
				
				read (tube3[1], bufpid3, sizeof(pid_t));
				printf ("Pere       : Lecture du pid %d \n", *bufpid3);
		} while (last_pid == current_pid);
	}

	return 0;
}
