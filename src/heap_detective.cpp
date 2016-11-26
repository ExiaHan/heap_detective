#include <string>
#include <iostream>
#include "Tokenizer.h"
#include "Detective.h"

using namespace std; 


int main() 
{
	Detective obj;

	obj.get_sinks("samplers/example1.c");
	cout << "collect end\n"; 
	obj.view_sinks();	
	cout << "view end\n"; 

	exit(0);
}

