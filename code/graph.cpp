#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <cstdio>
#include <time.h>
#include <unordered_map>
#include <sstream>

using namespace std;

/*!
* Class about generating DNA secuence using bruijn graph.
* @author Santiago Passos and Juan David Arcila
* @version 1.0.0 15/04/2017
*/
class Bruijn
{

  private:
    unordered_map<string,int> kmap;
    unordered_map<int,string> kmap2;
    int cont;
    stringstream dna;
    int kmers;
    int startGlobal = -1;
    int endGlobal = -1;

  public:
    /**
      * Class Constructor.
      * @param size maximun size of the graph.
      **/
    Bruijn(int size)
    {
        kmers = 201;
        kmap.reserve(size + 100);
        kmap2.reserve(size + 100);
    }

    /**
      * Divide the string(str) into k-mers of size k
      * @return the list of the left and right k-1-mer from each k-mer
      * @param str string to k-mer
      * @param graph Graph bruijn
      * @param starting vector to make the topological search
      **/
    void k_mer(string str,vector<int> &graph, vector<int> &graphInv, vector<bool> &starting){
        for(int i=0;i<str.size()-kmers;++i){
            string tempLeft = str.substr(i,kmers-1);
            string tempRight = str.substr(i+1,kmers-1);
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
    /**
      * Search for the int in the map
      * @param n int to search
      * @return key of the value n in the map
      **/
    string search(int n){
        return kmap2[n];   
    }
    /**
      * Aux funtion to make the parse in the rest of the graph
      * @param graph graph bruijn
      * @param visited vector usted to detected cycles in the graph
      * @param node actual node to read
      **/
    void parseAux(vector<int> graph,bool visited[],int node,stringstream &cadena){
        while(true){
            visited[node] = true;
            cadena << search(node).substr(kmers-2,1);
            int nextNode = graph[node];
            if(visited[nextNode]) cout << "Se ha encontrado un ciclo en el grafo"<< endl;
            if(nextNode != -1) node = nextNode;
            else{endGlobal = node;break;}
        }
    }

    /**
      * Aux fuction called by parse
      * @param graph graph bruijn
      * @param visited vector usted to detected cycles in the graph
      * @param node actual node to read
      **/
    void parseAuxInv(vector<int> graph,bool visited[],int node,stringstream &cadena){
        while(true){
            visited[node] = true;
            cadena << search(node).substr(0,1);
            int nextNode = graph[node];
            if(visited[nextNode]){cout << "Se ha encontrado un ciclo en el grafo"<< endl;break;}
            if(nextNode != -1)node = nextNode;
            else{startGlobal = node;break;}
        }
    }
    /**
      * Given a the Bruijn convert a string DNA 
      * @return the dna string that the bruijn graph represent
      * @param graph graph bruijn
      * @param starting vector usted in topological search
      **/
    string parse(vector<int>graph,vector<int> graphInv,vector<bool> starting){
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
            parseAux(graph,visited,graph[start],dna);
        }
        if(endGlobal!=-1 and graph[endGlobal]!=-1){
            start = graph[endGlobal];
            visited[start] = true;
            parseAux(graph,visited,start,cadenaDer);
            dna << cadenaDer.str();
        }
        stringstream cadenaIzq;
        if(startGlobal!=-1 and !starting[startGlobal]){
            parseAuxInv(graphInv,visited,graphInv[startGlobal],cadenaIzq);
            string auxiliar(cadenaIzq.str());
            string strAux(auxiliar.rbegin(), auxiliar.rend());
            cadenaIzq.str(""); cadenaIzq << strAux;
            cadenaIzq << dna.str();
            dna.str("");
            dna << cadenaIzq.str();
        }
        return dna.str();
    }
};