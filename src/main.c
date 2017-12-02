#include <stdlib.h>
#include <stdio.h>
#include "calc.h"

int main() 
{
	// Print welcome message
	printf("Simple Calculator\n");
	
	// Infinite loop, running calculator until quit/exit triggered.
	for (;;)
	{
		calc();
	}
	
	return 0;
}
