#include <stdlib.h>
#include <stdio.h>

int main(void)
{   
	char *ch_ptr = NULL;

	ch_ptr = malloc(100);
	int i=0;

	free(ch_ptr);
	
	ch_ptr = malloc(500);

	return 0;

}
