#include <string>
#include <iostream>
#include "Tokenizer.h"
#include "Detective.h"

using namespace std; 


int main(int argc, char* argv[]) 
{

	if(argc < 2) 
	{
		std::cerr << "Please Follow the command to run: ./bin/heap_detective DIRECTORY_NAME_to_audit" << std::endl;
		cout << "\n Heap Detective version 0.2 \n";
		exit(0);	
	}

	try {
		Detective *obj= new Detective;
		obj->set_target_path(argv[1]);
		obj->get_all_sinks();
		cout << "collect end\n"; 
		obj->view_sinks();	
		cout << "view end\n"; 
        	obj->clear_sinks();
		delete obj;

	} catch (const char* msg) {

		cerr << msg << endl;
	}


	exit(0);
}

