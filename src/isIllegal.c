#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isIllegal(char *string)
{
	// Go through every element in the string. Return 1 if any letter other than e is found.
	// Return 2 if zero is found immediately after a division sign.
	for (int i = 0; i < strlen(string); ++i)
	{
		if (isalpha(string[i]))
		{
			if (string[i] != 'e')
				return 1;
		}
		if (string[i] == '0' && string[i-1] == '/')
			return 2;
	}
	
}
