#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) 
{
	int *array = new int[100];
	delete [] array;

	array=(int *)2;
   

	return 0;
}

