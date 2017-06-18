#include "Tokenizer.h"
#include "Detective.h"
using namespace std;


void Detective::set_target_path(string path)
{
	const bool showHiddenDirs = false;
    	DIR *path_dir;
    	struct dirent *tmp;
    	path_dir = opendir(path.c_str());

    	if(path_dir != NULL)	
        	while((tmp = readdir(path_dir)) != NULL)
		{
            		if(showHiddenDirs ? (tmp->d_type==DT_DIR && string(tmp->d_name) != ".." && string(tmp->d_name) != "." ) : (tmp->d_type==DT_DIR && strstr(tmp->d_name,"..") == NULL && strstr(tmp->d_name,".") == NULL ) )
                		set_target_path(path+tmp->d_name+"/");
            		
            		if(tmp->d_type==DT_REG)
               			files_path.push_back(path+tmp->d_name);
            		
        	}

    	closedir(path_dir);
}

void Detective::get_all_sinks()
{
	size_t len_list=files_path.size(),x=0;

	while(x != len_list)
	{
		get_sinks(files_path[x]);
		x++;
	}
}


void Detective::get_sinks(string FileName)
{
	string line;
	ifstream file;

	bool test=false;
	size_t pos2=0,pos3=0,line_counter=1,found_char=0,count_functions=0;

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

			if(found_char!=string::npos)
			{
				count_functions=0;

				test=false;

				while(count_functions != heap_in.size())
				{
						
					if(line.find(heap_in[count_functions])!=string::npos)
					{
						Tokenizer str;
						string token;
						str.set(line);
						token = str.next();
      		
 						array.push_back(startpoint());
						array[pos].filename = FileName;
						array[pos].var_name = token;
						array[pos].line = line;
						array[pos].line_number = line_counter;
						test=true;
						pos3=pos;
						pos++;
					}

					count_functions++;
				}

				
// collect sinks			
				if(test==false)						
					if( line.find(array[pos3].var_name)!=string::npos )
					{
						Tokenizer str;
						string token;
						str.set(line);
						token = str.next();

						sink makestruct = {token,line,line_counter,false,false};
						array[pos3].sinks.push_back(makestruct);
					}

			}			
// collect sinks of free
			pos2=0;

			while(pos2!=array.size())
			{
				count_functions=0;
				
				while(count_functions!=heap_out.size())
				{
					if(!heap_out[count_functions].empty())
						if ( (line.find(heap_out[count_functions],0)!=string::npos) && (line.find(array[pos2].var_name)!=string::npos) )
						{
							sink makestruct2 = {array[pos2].var_name,line,line_counter,false,false};
							array[pos3].sinks.push_back(makestruct2);
							goto END_VIEW_DETECTIVE;			
						}	
			
					count_functions++;
				}

				pos2++;
			}

			END_VIEW_DETECTIVE:

			found_char=0;	
			line_counter++;
		}


	file.close();
}

void Detective::view_sinks()
{
	size_t x=0,y=0;

	while(x != array.size())
	{

		cout << "\nHeap:action::\n:::::::::::::::::::::::\n";	
		cout << "File path: " << array[x].filename << "\n";			
		cout << "Var name: " << array[x].var_name << "\n";			
		cout << "line: " << array[x].line_number << ":" << array[x].line << "\n";			
		cout << "Sinks: \n";

		while(y != array[x].sinks.size())
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
