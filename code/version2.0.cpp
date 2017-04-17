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

/*!
* Class about generating DNA secuence using bruijn graph.
* @author Santiago Passos and Juan David Arcila
* @version 1.0.0 15/04/2017
*/
class bruijnDNAReconstructure
{

  private:
    unordered_map<string, int> kmap;
    int cont;
    stringstream dna;
    int kmers;

  public:
    /**
    * Class Constructor.
    * @param size maximun size of the graph.
    **/
    bruijnDNAReconstructure(int size)
    {
        kmers = 201;
        kmap.reserve(size + 100);
    }

    /**
     * Divide the string(str) into k-mers of size k
     * @param str string to k-mer
     * @param graph Graph bruijn
     * @param starting vector to define the starting node
     * @return the list of the left and right k-1-mer from each k-mer
     **/
    void k_mer(string str, vector<int> &graph, vector<bool> &starting)
    {
        for (int i = 0; i < str.size() - kmers; ++i)
        {
            string tempLeft = str.substr(i, kmers - 1);
            string tempRight = str.substr(i+1, kmers -1);
            if (!kmap.count(tempLeft))
            {
                kmap[tempLeft] = cont;
                cont++;
            }
            if (!kmap.count(tempRight))
            {
                kmap[tempRight] = cont;
                cont++;
            }
            int to = kmap[tempRight];
            graph[kmap[tempLeft]] = to;
            starting[to] = false;
        }
    }
    /**
     * Search for the int in the map
     * @param n int to search
     * @return key of the value n in the map
     **/
    string search(int n)
    {
        unordered_map<string, int>::const_iterator it;
        for (it = kmap.begin(); it != kmap.end(); ++it)
        {
            if (it->second == n)
            {
                return it->first;
            }
        }
    }

    /**
    * Aux funtion to make the parse in the rest of the graph
    * @param graph graph bruijn
    * @param visited vector usted to detected cycles in the graph
    * @param node actual node to read
    **/
    void parseAux(vector<int> graph, bool visited[], int node)
    {
        while (true)
        {
            visited[node] = true;
            dna << search(node).substr(kmers - 2, 1);
            int nextNode = graph[node];
            if (visited[nextNode])
                cout << "Se ha encontrado un ciclo en el grafo" << endl;
            if (nextNode != -1)
            {
                node = nextNode;
            }
            else
            {
                break;
            }
        }
    }

    /**
     * Return the dna string that the bruijn graph represent
     * @param graph graph bruijn
     * @param starting vector usted in topological search
     **/
    void parse(vector<int> graph, vector<bool> starting)
    {
        clock_t t1, t2;
        t1 = clock();
        int start;
        for (int i = 0; i < graph.size(); ++i)
        {
            if (starting[i])
            {
                start = i;
                break;
            }
        }
        t2 = clock();
        float diff((float)t2 - (float)t1);
        float seconds = diff / CLOCKS_PER_SEC;
        cout << "Tiempo tomado:  " << seconds << endl;
        cout << "Empieza la reconstrucción" << endl;
        dna << search(start);
        bool visited[graph.size()];
        for (int i = 0; i < graph.size(); ++i)
            visited[i] = false;
        visited[start] = true;
        parseAux(graph, visited, graph[start]);
    }

    /**
    * Get the final DNA string from the stringstream
    * @return String final DNA
    **/
    string getDNA()
    {
        return dna.str();
    }
};

main()
{
    int size;
    string str;
    cin >> size;
    vector<bool> starting(size, false);
    for (int i = 0; i < size; ++i)
        starting[i] = true;
    vector<int> graph(size, -1);
    clock_t t1, t2;
    bruijnDNAReconstructure *bruijn = new bruijnDNAReconstructure(size);
    t1 = clock();
    while (cin >> str)
    {
        bruijn->k_mer(str, graph, starting);
    }
    t2 = clock();
    float diff((float)t2 - (float)t1);
    float seconds = diff / CLOCKS_PER_SEC;
    cout << "Grafo creado completamente" << endl;
    cout << "Tiempo necesitado:  " << seconds << endl;
    t1 = clock();
    bruijn->parse(graph, starting);
    t2 = clock();
    diff = ((float)t2 - (float)t1);
    float seconds2 = diff / CLOCKS_PER_SEC;
    cout << "Cadena DNA formada" << endl;
    cout << "Tiempo necesitado:  " << seconds2 << endl;
    cout << "TIEMPO TOTAL " << seconds + seconds2 << " SEGUNDOS" << endl;
    cout << "tamaño del ADN generado " << size << endl; 
    cout << bruijn->getDNA() << endl;

}