#include <iostream>
#include <vector>
#include "graph.cpp"
#include "boyer.cpp"

using namespace std;

main(){
    int size;
    string str;
    cin >> size;
    vector<bool> starting(size, false);
    for (int i = 0; i < size; ++i) starting[i] = true;
    vector<int> graph(size,-1);
    vector<int> graphInv(size,-1);
    Bruijn *bruijn = new Bruijn(size);
    Boyer *boyer = new Boyer();
    string str_final, gen;
    int lines = 0;
     while(cin >> str){
        bruijn->k_mer(str,graph,graphInv,starting);
        lines++;
        if(lines%15==0){       
            str_final = bruijn->parse(graph,graphInv,starting);
            if(str_final.size()>=size-1){
                gen = boyer->searchGen(str_final);
                cout << gen;
                break;
            }
        }
    }
}