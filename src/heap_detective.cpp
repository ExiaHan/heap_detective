// coded by CoolerVoid
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
		cout << "\n heap_detective version 0.32 \n";
		exit(0);	
	}

	try {
		// Tokenize and collect routes of Heap calls
		Detective *obj = new Detective;
		obj->set_target_path(argv[1]);
		obj->get_all_sinks();
		cout << "Collect action done\n"; 

		// Show Heap routes
		obj->view_sinks();	
		cout << "\n>>-----> View end\n";

		// Double free vulnerability finder
		cout << "\n>>-----> Start double free analyser\n";
		obj->double_free();	

		// Use after free vulnerability finder
		cout << "\n>>-----> Start use after free analyser\n"; 
		obj->use_after_free();	

		// liberate all heap memory 
        	obj->clear_sinks();
		delete obj;

	} catch (const char* msg) {

		cerr << msg << endl;
	}


	exit(0);
}

