#include "Tokenizer.h"
#include "Detective.h"
using namespace std;

void Detective::get_sinks(string FileName)
{
	string line;
	ifstream file;

	int line_counter=0,found_char=0;
	short count_functions=0;
	size_t pos=0,pos2=0;

	file.exceptions(ifstream::failbit | ifstream::badbit);


	try {
		file.open(FileName);

		while(getline(file, line))
		{

/*
 **TODO add LOOP detector to insert loop element at struct sink..
*/


// collect startpoint	 
	
			found_char = line.find_first_of('=');

			if(found_char!=-1)
			{
				count_functions=0;

				while(count_functions != 7)
				{
						
					if((signed int)line.find(heap_in[count_functions])!=-1)
					{
						Tokenizer str;
						string token;
						str.set(line);
						token = str.next();
      		
 						array.push_back(startpoint());
						array[pos].sinks.push_back(sink());
						array[pos].var_name = token;
						array[pos].line = line;
						array[pos].line_number = line_counter;
						pos++;
					}

					count_functions++;
				}

				pos2=pos-1;
// collect sinks
				
				while(pos2)
				{
											
					if( (signed int)line.find(array[pos2].var_name)!=-1 )
					{
						Tokenizer str;
						string token;
						str.set(line);
						token = str.next();

						sink makestruct = {token,line,line_counter,"false"};
						array[pos].sinks.push_back(makestruct);
					}
					pos2--;
				}	
			}			

// collect sinks of free
			pos2=array.size()-1;

			while(pos2)
			{
				count_functions=0;

				while(count_functions!=5)
				{

					if((signed int)line.find(heap_out[count_functions])!=-1 && (signed int)line.find(array[pos2].var_name)!=-1)
					{
						sink makestruct = {array[pos2].var_name,line,line_counter,"false"};
						array[pos].sinks.push_back(makestruct);				
					}

					count_functions++;
				}
		
		
				pos2--;
			}



			found_char=0;	
			line_counter++;
		}
	} catch (const ifstream::failure& e) {
    		cerr << "error in file" << endl;
	};
	file.close();
}
