/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "IDL.h"

void *
notifier_reception_1_svc(data *argp, struct svc_req *rqstp)
{
	static char * result;

	printf("Le processus %d à reçu un message envoyé de %d avec la valeur %d\n", argp->pid1, argp->pid2, argp->valeur); 

	return (void *) &result;
}
