#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <cstdio>
#include <time.h>
#include <unordered_map>
#include <sstream>

using namespace std;

unordered_map<string,int> kmap;
int cont;
stringstream dna;

/*
    Divide the string(str) into k-mers of size k
    return the list of the left and right k-1-mer from each k-mer
*/
void k_mer(string str,int k, vector<int> &graph, vector<bool> &starting){
    for(int i=0;i<str.size()-k;++i){
        string temp = str.substr(i,k);
        string tempLeft = temp.substr(0,temp.size()-1);
        string tempRight = temp.substr(1,temp.size());
        if(!kmap.count(tempLeft)) {kmap[tempLeft]=cont;cont++;}
        if(!kmap.count(tempRight)) {kmap[tempRight]=cont; cont++;}
        int to =  kmap[tempRight];
        graph[kmap[tempLeft]] = to;
        starting[to] = false;
    }
}
/*
    Search for the int in the map
*/
string search(int n){
    unordered_map<string,int>::const_iterator it;
    for(it = kmap.begin(); it != kmap.end(); ++it){
        if(it->second == n){
        return it->first;
        }
    }     
}

void parseAux(vector<int> graph,bool visited[],int node,int k){
   	while(true){
      visited[node] = true;
    	dna << search(node).substr(k-2,1);
      int nextNode = graph[node];
      if(visited[nextNode]) cout << "Se ha encontrado un ciclo en el grafo"<< endl;
      if(nextNode != -1){
        node = nextNode;
      }
      else{
        break;
      }
  	}
}

/*
    Return the dna string that the bruijn graph represent
*/
void parse(vector<int>graph,int k, vector<bool> starting){
    clock_t t1,t2;
    t1 = clock();
    int start;
    for(int i=0;i<graph.size();++i){
        if(starting[i]){start = i;break;}
    }
    t2 = clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "Terminado el ordenamiento topológico" << endl;
    cout<<"Tiempo tomado:  " << seconds<<endl;
    cout << "Empieza la reconstrucción" << endl;
    dna << search(start);
    bool visited[graph.size()];
    for(int i=0;i<graph.size();++i) visited[i] = false;
    visited[start] = true;
    parseAux(graph,visited,graph[start],k);
}

main(){
    string str;
    int kmers = 201;
    int size;
  	cin >> size;
  	kmap.reserve(size+100);
  	vector<bool> starting(size,false);
    for(int i=0;i<size;++i) starting[i] = true;
  	vector<int> graph(size,-1);
    clock_t t1,t2;
    t1=clock();
    while(cin >> str){
        k_mer(str,kmers,graph,starting);
    }
    t2=clock();
    float diff ((float)t2-(float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "Grafo creado completamente" << endl;
    cout<<"Tiempo tomado:  " << seconds<<endl;
    t1=clock();
    parse(graph,kmers,starting);
    t2=clock();
    diff = ((float)t2-(float)t1);
    seconds = diff / CLOCKS_PER_SEC;
    cout<<"Tiempo tomado:  " << seconds <<endl;
  	string final_str = dna.str();
    cout << final_str << endl;
}