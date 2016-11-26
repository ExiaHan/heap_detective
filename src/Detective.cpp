#include "Tokenizer.h"
#include "Detective.h"
using namespace std;

void Detective::get_sinks(string FileName)
{
	string line;
	ifstream file;

	size_t pos=0,pos2=0;
	int line_counter=0,found_char=0,count_functions=0;

	file.open(FileName);

		if(file.fail())
		{
			cout << "Error in open file!";
			file.clear();
			return;
		}
	

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

				while(count_functions != (signed int)heap_in.size())
				{
						
					if(line.find(heap_in[count_functions])!=string::npos)
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

				
// collect sinks			
	
				while(pos2!=array.size())
				{
											
					if( line.find(array[pos2].var_name)!=string::npos )
					{
						Tokenizer str;
						string token;
						str.set(line);
						token = str.next();

						sink makestruct = {token,line,line_counter,false,false};
						array[pos2].sinks.push_back(makestruct);
						

					}
					pos2++;
				}	
				pos2=0;

			}			
// collect sinks of free
/*
			pos2=pos-1;

			while(pos2)
			{
				count_functions=0;
				
				while(count_functions!=(signed int)heap_out.size())
				{
					if(!heap_out[count_functions].empty())
					{
						
						if( line.find(heap_out[count_functions],0)!=string::npos) 
						{
							if((signed int)line.find(array[pos2].var_name)!=-1)
							{
								sink makestruct2 = {array[pos2].var_name,line,line_counter,false,false};
								array[pos2].sinks.push_back(makestruct2);			
							}	
						}
					}
			
					count_functions++;
				}

	
				pos2--;
			}
*/
			found_char=0;	
			line_counter++;
		}


	file.close();
}

void Detective::view_sinks()
{
	size_t x=0,y=0;

	cout << "View sinks::\n";	

	while(x != array.size()-1)
	{
		cout << "Var name: " << array[x].var_name << "\n";			
		cout << "line: " << array[x].line_number << ":" << array[x].line << "\n";			
		cout << "Sinks: \n";

		while(y != array[x].sinks.size()-1)
		{
			cout << "\t Var name: " << array[x].sinks[y].value << "\n";			
			cout << "\t line: " << array[x].sinks[y].line_number << ":" << array[x].sinks[y].line << "\n";
			cout << "\t Taint: " << ((array[x].sinks[y].taint==true)?"true":"false") << "\n";	
			cout << "\t In Loop: " << ((array[x].sinks[y].inloop==true)?"true":"false") << "\n";
			y++;
		}

		y=0;
			
		x++;
	}


}
