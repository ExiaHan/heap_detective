#include <string>
#include <iostream>
#include "Tokenizer.h"
#include "Detective.h"

using namespace std; 


int main() 
{
	Detective obj;

	obj.set_target_path("samplers/");
	obj.get_all_sinks();
	cout << "collect end\n"; 
	obj.view_sinks();	
	cout << "view end\n"; 

	exit(0);
}

