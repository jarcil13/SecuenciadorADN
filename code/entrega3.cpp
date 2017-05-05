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
unordered_map<int,string> kmap2;
int cont;
stringstream dna;
int startGlobal = -1;
int endGlobal = -1;

/*
    Divide the string(str) into k-mers of size k
    return the list of the left and right k-1-mer from each k-mer
*/
void k_mer(string str,int k, vector<int> &graph, vector<int> &graphInv, vector<bool> &starting){
    for(int i=0;i<str.size()-k;++i){
        string tempLeft = str.substr(i,k-1);
        string tempRight = str.substr(i+1,k-1);
        if(!kmap.count(tempLeft)) {kmap[tempLeft]=cont;cont++;}
        if(!kmap.count(tempRight)) {kmap[tempRight]=cont; cont++;}
        int to =  kmap[tempRight];
        int from = kmap[tempLeft];
        kmap2[to] = tempRight;
        kmap2[from] = tempLeft;
        graph[from] = to;
        graphInv[to] = from;
        starting[to] = false;
    }
}
/*
    Search for the int in the map
*/
string search(int n){
    return kmap2[n];   
}

void parseAux(vector<int> graph,bool visited[],int node,int k,stringstream &cadena){
   	while(true){
      visited[node] = true;
      cadena << search(node).substr(k-2,1);
      int nextNode = graph[node];
      if(visited[nextNode]) cout << "Se ha encontrado un ciclo en el grafo"<< endl;
      if(nextNode != -1){
        node = nextNode;
      }
      else{
        endGlobal = node;  
        break;
      }
  	}
}

void parseAuxInv(vector<int> graph,bool visited[],int node,int k,stringstream &cadena){
   	while(true){
      visited[node] = true;
      cadena << search(node).substr(0,1);
      int nextNode = graph[node];
      if(visited[nextNode]){cout << "Se ha encontrado un ciclo en el grafo"<< endl;break;}
      if(nextNode != -1){
        node = nextNode;
      }
      else{
        startGlobal = node;
        break;
      }
  	}
}

/*
    Return the dna string that the bruijn graph represent
*/
string parse(vector<int>graph,vector<int> graphInv, int k, vector<bool> starting){
    int start;
    stringstream cadenaDer;
    bool visited[graph.size()];
    for(int i=0;i<graph.size();++i) visited[i] = false;
    if(startGlobal==-1){
        for(int i=0;i<graph.size();++i){
            if(starting[i]){start = i;break;}
        }
        startGlobal = start;
        visited[start] = true;
        dna << search(start);
        parseAux(graph,visited,graph[start],k,dna);
    }
    if(endGlobal!=-1 and graph[endGlobal]!=-1){
        start = graph[endGlobal];
        visited[start] = true;
        parseAux(graph,visited,start,k,cadenaDer);
        dna << cadenaDer.str();
    }
    stringstream cadenaIzq;
    if(startGlobal!=-1 and !starting[startGlobal]){
        parseAuxInv(graphInv,visited,graphInv[startGlobal],k,cadenaIzq);
        string auxiliar(cadenaIzq.str());
        string strAux(auxiliar.rbegin(), auxiliar.rend());
        cadenaIzq.str(""); cadenaIzq << strAux;
        cadenaIzq << dna.str();
        dna.str("");
        dna << cadenaIzq.str();
    }
    return dna.str();
}

main(){
    string str;
    int kmers = 205;
    int size;
  	cin >> size;
  	kmap.reserve(size+100);
    kmap2.reserve(size+100);
  	vector<bool> starting(size,false);
    for(int i=0;i<size;++i) starting[i] = true;
  	vector<int> graph(size,-1);
    vector<int> graphInv(size,-1);
    string str_final;
    int lines = 0;
    clock_t t1, t2;
    t1 = clock();
    while(cin >> str){
        k_mer(str,kmers,graph,graphInv,starting);
        lines++;
        if(lines%15==0){       
            str_final = parse(graph,graphInv,kmers,starting);
            if(str_final.size()>=size-5) break;
        }
    }
    t2 = clock();
    float diff((float)t2 - (float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "Grafo creado completamente" << endl;
    cout << "Tiempo necesitado:  " << seconds << endl;
    cout << str_final << endl;
}