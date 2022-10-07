#include "core.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;



int main(int argc, char* argv[]){

    string input_path=std::filesystem::current_path();
    int input_depth=-1;
    bool input_show_full_path=false;
    bool input_show_only_folders=false;
    bool input_show_size=false;
    //the first argumant is path
    //-d depth
    //-p show full path
    //-f show only folders
    //-s show size
    if(argc>1){
        for(int i=1;i<argc;i++){
            if(argv[i-1][1]=='d')input_depth=atoi(argv[i]);
            else if(argv[i][1]=='p')input_show_full_path=true;
            else if(argv[i][1]=='f')input_show_only_folders=true;
            else if(argv[i][1]=='s')input_show_size=true;
            else if(argv[i][0]!='-')input_path=argv[i];
        }
    }

    dir_structure ds(input_path);
    ds.initDirStructure(input_depth);
    ds.showTree(input_depth, 
    input_show_full_path, 
    input_show_only_folders,
    input_show_size);

    return 0;
}
