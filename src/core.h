/*
    core is meant to store code needed to extract directory_entries and store them in memory with information about them
    it also provides data needed for front end of the cli


*/
#include <filesystem>
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include <algorithm>


using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

class dir_object{
    std::filesystem::directory_entry current_entry;
    vector<dir_object>sub_entries;

public:
    vector<dir_object>& getSubEntries();
    std::filesystem::directory_entry& getCurrentEntry();
    
    string getName();
    string getNameOf(const dir_object& d);
    string getNameOf(const std::filesystem::directory_entry& d);

    dir_object(const dir_object& d);
    dir_object(string d);
    dir_object(const std::filesystem::directory_entry& d);
    dir_object();
};

class dir_structure{
    dir_object dir_tree;
    int baseDepth;

    

    void showTree(dir_object& de, int depth, bool p, bool f, bool s);//if -1 then recursion is infinite

    void traverseTree(dir_object& de, int depth);

    void traverseTree(int depth);

public:
    void showTree(int depth, bool p, bool f, bool s);//if -1 then recursion is infinite
    const dir_object& getTreeStem();
    void initDirStructure();
    void initDirStructure(int d);
    int getBaseDepth();

    dir_structure(const dir_object& t);
    dir_structure(string t);
    dir_structure(const std::filesystem::directory_entry& t);
    dir_structure();
};

