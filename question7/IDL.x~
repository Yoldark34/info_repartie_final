struct data
{
	unsigned int process;
	unsigned int timestamp;
	char action[99];
};
typedef struct data data;

struct reponse
{
	int errno;
};

typedef struct reponse reponse;
program SIGNAL
{
version VERSION_UN
{
reponse SEND_SIGNAL (data) = 0;
}
	= 1;
}
= 0x20000001; 
