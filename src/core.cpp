#include "core.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;

vector<dir_object>& dir_object::getSubEntries(){
    return sub_entries;
}

std::filesystem::directory_entry& dir_object::getCurrentEntry(){
    return current_entry;
}










////////////////////////getName of dir entry

string dir_object::getName(){
    string foo=current_entry.path();
    return foo;
}

string getNameOf(dir_object& d){
    string foo=d.getName();
    return foo;
}

string getNameOf(const std::filesystem::directory_entry& d){
    return d.path();
}








/////////////////dir_entry constructors

dir_object::dir_object(string d){
    current_entry=std::filesystem::directory_entry(d);
}

dir_object::dir_object(const dir_object& d){
    this->current_entry=d.current_entry;
    this->sub_entries=d.sub_entries;
}

dir_object::dir_object(const std::filesystem::directory_entry& d){
    this->current_entry=d;
}

dir_object::dir_object(){
    current_entry=std::filesystem::directory_entry(std::filesystem::current_path());
}





/*

    dir_structure


*/

void dir_structure::traverseTree(int depth){
    traverseTree(dir_tree, depth);
}

void dir_structure::traverseTree(dir_object& de, int depth){
    if(depth<0)baseDepth=-depth-2;
    for(const auto& i:std::filesystem::directory_iterator(de.getCurrentEntry())){
        de.getSubEntries().push_back(i);
        //cout<<i.path()<<endl;
    }
    if(depth==1)return;
    for(auto& i:de.getSubEntries()){
        if(i.getCurrentEntry().is_directory()){
            traverseTree(i, depth-1);
        }
    }
}

void dir_structure::showTree(int depth, bool p, bool f, bool s){
    string foo=dir_tree.getName();
    string size="";
    if(s && !dir_tree.getCurrentEntry().is_directory()){
        size+="[size: ";
        size+=to_string(dir_tree.getCurrentEntry().file_size());
        size+=" bytes]\n";
    }
    if(!dir_tree.getCurrentEntry().is_directory() && !p){
        foo.erase(0,foo.find_last_of('/')+1);
        //foo.insert(0, string(4-depth, '\t'));
    }

    cout<<foo<<size<<endl;
    
    if(depth==0)return;
    if(dir_tree.getCurrentEntry().is_directory()){
        for(auto& i:dir_tree.getSubEntries()){
            //cout<<i.getName()<<endl;
            showTree(i, depth-1, p, f, s);
        }
    }
    
}


void dir_structure::showTree(dir_object& de, int depth, bool p, bool f, bool s){
    string foo=de.getName();
    string size="";
    if(s && !de.getCurrentEntry().is_directory()){
        size+="[size: ";
        size+=to_string(de.getCurrentEntry().file_size());
        size+=" bytes]\n";
    }
    if(!de.getCurrentEntry().is_directory() && !p){
        foo.erase(0,foo.find_last_of('/')+1);
        //foo.insert(0, string(4-depth, '\t'));
    }

    foo.insert(0,"├");
    
    if(s && !de.getCurrentEntry().is_directory()){
        size.insert(0,"│");
        for(int i=0;i<baseDepth-depth;i++){
            if(i+1!=baseDepth-depth)size.insert(0," ");
            if(i+1!=baseDepth-depth)size.insert(0,"│");
        }

    }

    for(int i=0;i<baseDepth-depth;i++){
        if(i+1!=baseDepth-depth)foo.insert(0," ");
        if(i+1!=baseDepth-depth)foo.insert(0,"│");
    }

    foo.append("\n");

    if((f && de.getCurrentEntry().is_directory()) ||
        !f)cout<<foo<<size;
    
    if(depth==0)return;
    if(de.getCurrentEntry().is_directory()){
        for(auto& i:de.getSubEntries()){
            showTree(i, depth-1, p, f, s);
        }
    }
    
}


void dir_structure::initDirStructure(){
    baseDepth=-1;
    traverseTree(-1);
    //showTree(-1);
}

void dir_structure::initDirStructure(int d){
    baseDepth=d;
    traverseTree(d);
    //showTree(d);
}


const dir_object& dir_structure::getTreeStem(){
    return dir_tree;
}

int dir_structure::getBaseDepth(){
    return baseDepth;
}


dir_structure::dir_structure(const dir_object& t){
    dir_tree=t;
}

dir_structure::dir_structure(string t){
    dir_tree=dir_object(t);
}

dir_structure::dir_structure(const std::filesystem::directory_entry& t){
    dir_tree=dir_object(t);
}

dir_structure::dir_structure(){
    dir_tree=dir_object(std::filesystem::current_path());
}