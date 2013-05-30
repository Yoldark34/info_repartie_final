struct data
{
	unsigned int pid1;
	unsigned int pid2;
	unsigned int valeur;
};
typedef struct data data;

program IDL
{
version VERSION_UN
{
void NOTIFIER_RECEPTION (data D) = 0;
}
	= 1;
}
= 0x20000001; 
