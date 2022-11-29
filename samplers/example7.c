#include <stdlib.h>
#include <stdio.h>

static char special(char * test)
{   
	char *ch_ptr = NULL;

	ch_ptr = malloc(100);

	int i=0;
	i=1000;

	free(ch_ptr);	
	ch_ptr = malloc(500);
	ch_ptr=NULL;

	return " ";
}


int main(void)
{   
	char *ch_ptr = NULL;

	ch_ptr = malloc(100);
	int i=0;

	free(ch_ptr);
	
	ch_ptr = malloc(500);

	return 0;

}
