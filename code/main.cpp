#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>

using namespace std;
typedef pair<string,int> psi; //pair string-int
map<string,int> kmap;
vector<list<int> > graph; 
/*
    Divide the string(str) into k-mers of size k
    return the list of the left and right k-1-mer from each k-mer
*/
list<string> k_mer(string str,int k){
    list <string> group;

    for(int i=0;i<str.size()-k;++i){
        string temp = str.substr(i,k);
        string tempLeft = temp.substr(0,temp.size()-1);
        string tempRight = temp.substr(1,temp.size());
        if(kmap.find(tempLeft)!=kmap.end()) kmap.insert(psi(tempLeft,kmap.size()));
        if(kmap.find(tempRight)!=kmap.end()) kmap.insert(psi(tempRight,kmap.size()));
        group.push_back(tempLeft); group.push_back(tempRight);
    }
    return group;
}

/*
    Create a bruijn graph from the k-mers
    return the graph
*/
void create_graph(list<string> group){
    list<string>::const_iterator iterator;
    for (iterator = group.begin(); iterator != group.end(); ++iterator) {
        if(graph.size()<=kmap[*iterator]){ //Si el grafo no contiene ese entero, entonces lo agrego
            list<int> temp;                     
            graph.push_back(temp);                  //Agrego una lista vacía al grafo
            int pos = kmap[*iterator]; ++iterator;  //Guardo la posición de la lista
            graph[pos].push_back(kmap[*iterator]);  //Agrego el arco
        }else{
            int pos = kmap[*iterator]; ++iterator;
            graph[pos].push_back(kmap[*iterator]);
        }
    }
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
    //while(cin>>str){
        cin >> str;
        list<string> group = k_mer(str,3);
        create_graph(group);
   // }
    //after doing a lot of bruijn
    cout << "-------------------" << endl;
    
    list<string>::const_iterator iterator = graph[0].begin(),
    cout << graph[0][*iterator]; 
    for(int i=1;i<graph.size();++i){
        cout << graph[i][*iterator];
    }

    //string dna = parse(final_graph);
}