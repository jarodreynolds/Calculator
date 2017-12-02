#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "help.h"
#define SIZE 255

int helpOrQuit(char *string)
{
	// Check the string for h or q 
	char letter_h = 'h';
	char letter_q = 'q';
	char *h_result = strchr(string, letter_h);
	char *q_result = strchr(string, letter_q);
	
	// If h detected, print help message, and begin calculator again.
	if (h_result != NULL)
	{
		help();
		return 1;
	}
	
	// If q detected, print goodbye message and end function
	if (q_result != NULL)
	{
		printf("Goodbye!\n");
		exit(1);
	}
	
}
