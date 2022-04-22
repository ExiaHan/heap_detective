#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) 
{
	int *array = NULL;
        char *array3 = NULL;

	array = new int[100];

	delete [] array;

	array=(int *)2;
   
	short int x=0;

	array3=realloc(400);

	while(x!=10)
	{
		array3='1';
		x++;
		free(array3);
	}

	

	return 0;
}

