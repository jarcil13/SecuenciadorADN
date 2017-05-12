#include <limits.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Boyer{

  int maxlength = 0;
  stringstream gen;
public:

  int max(int a, int b){
    return (a > b) ? a : b;
  }

  // The preprocessing function for Boyer Moore's bad character heuristic
  void badCharHeuristic(char *str, int size, vector<int> badchar){
    int i;
    // Initialize all occurrences as -1
    for (i = 0; i < maxlength; ++i)
      badchar[i] = -1;
    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
      badchar[(int) str[i]] = i;
  }

  /* Driver program to test above funtion */
  void search(char *txt, char *pat, vector<int> &indices){
    int m = strlen(pat);
    int n = strlen(txt);
    vector<int> badchar(maxlength,0);
    badCharHeuristic(pat, m, badchar);
    int s = 0; // s is shift of the pattern with respect to text
    while (s <= (n - m)){
      int j = m - 1;
      while (j >= 0 && pat[j] == txt[s + j]) j--;
        if (j < 0){   
        indices.push_back(s);
        s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        }
        else  s += max(1, j - badchar[txt[s + j]]);
      }
  }

  string searchGen(string cadena){
    maxlength = cadena.size();
    char ADN[cadena.length()];
    strcpy(ADN, cadena.c_str());
    vector<int> vect_ini;
    vector<int> vect_fin;
    search(ADN,"atg",vect_ini);
    search(ADN,"taa",vect_fin);
    search(ADN,"tag",vect_fin);
    search(ADN,"tga",vect_fin);
    sort(vect_fin.begin(),vect_fin.end());
    int inicial = vect_ini[0];
    for(int pos : vect_ini){
        if(pos<inicial) continue;
        else inicial = pos;
        for(int posF : vect_fin){
            if(posF<inicial+200) continue; // se suma 4 para que mínimo haya un codón en el gen
            if((posF-inicial)%3==0){
                gen << cadena.substr(inicial,posF+3-inicial) << endl;
                inicial = posF + 3;
                break;
            }
        }
    }
    return gen.str();
  }
};
