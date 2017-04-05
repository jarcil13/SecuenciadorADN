#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;


/*
    Divide the string(str) into k-mers of size k
    return the list of the left and right k-1-mer from each k-mer
*/
list<string> k_mer(string str,int k){
    list <string> group;
    return group;
}

/*
    Create a bruijn graph from the k-mers
    return the graph
*/
vector<list<string> > create_graph(list<string> group){
    vector<list<string> > graph;
    return graph;
}

/*
    Add the actual graph to the graph created from the others strings
*/
void add_graph(vector<list<string> > graph, vector<list<string> > final_graph){

}

/*
    Return the dna string that the bruijn graph represent
*/
string parse(vector<list<string> > graph){
    return "";
}


main(){
    string str;
    vector<list<string> > final_graph;
    while(cin>>str){
        list<string> group = k_mer(str,99);
        vector<list<string> > bruijn = create_graph(group);
        add_graph(bruijn,final_graph);
    }
    //after doing a lot of bruijn
    string dna = parse(final_graph);
}