#include <iostream>
#include <vector>
#include <string>
#include "graph.cpp"
#include "boyer.cpp"
#include <fstream>
#include <cstdlib>
using namespace std;

#define size 20100

/**
  * Main of the program
  * @param argc number of args, always must to be 2 
  * @param argv array of args, first position the number of gens, second the path.
  * @return exit state of the programa by OS definition
  **/
int main(int argc, char* argv[]){
    int gen_num = atoi(argv[1]);
    ifstream file;
    Boyer *boyer = new Boyer(gen_num);
    string str, str_final, gen;
    file.open(argv[2]);
    Bruijn *bruijn = new Bruijn();
    vector<bool> starting(size, false);
    for (int i = 0; i < size; ++i) starting[i] = true;
    vector<int> graph(size,-1);
    vector<int> graphInv(size,-1);
    int lines = 0;
    while(file >> str){
        bruijn->k_mer(str,graph,graphInv,starting);
        lines++;
        if(lines%100==0){       
            str_final = bruijn->parse(graph,graphInv,starting);
            gen = boyer->searchGen(str_final);
            cout << gen;
            if(boyer->is_complete()) break;
            for(int i=0;i<300;++i) cout << "|";
            cout << endl;
        }
    }
    if(boyer->is_complete()) {cout << "Numero de genes entregado completamente";}
    else{ cout << "Numero de genes no entregado completamente";}
    file.close();
}