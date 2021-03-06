#include <limits.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/*!
 * Class to make the DNA search with BooyerMoore
 * @author Santiago Passos and Juan David Arcila
 * @version 1.0.0 15/04/2017
 **/
class Boyer{

  int maxlength = 0;
  int max_gen;
  int gen_count = 0;
  stringstream gen;
public:
   /**
     * Constructo fro the class
     * @param num numbers to be searched 
     **/
   Boyer(int num){
    max_gen = num;
   }
   /**
     * Usefull fucion to get a max int
     * @param a number a
     * @param b number b
     * @return the max number
     **/
  int max(int a, int b){
    return (a > b) ? a : b;
  }

  /**
    * Funcion to know if the number of Genes is completed
    * @return bool true if it's completed
    **/
  bool is_complete(){
    return max_gen==gen_count;
  }

  /**
    * The preprocessing function for Boyer Moore's bad character heuristic
    * @param *str pointer to the string to evaluate
    * @param size length of the string
    * @param badchar vectro to make the Boyer Moore's bad character heuristic
    **/
  void badCharHeuristic(char *str, int size, vector<int> badchar){
    int i;
    // Initialize all occurrences as -1
    for (i = 0; i < maxlength; ++i)
      badchar[i] = -1;
    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
      badchar[(int) str[i]] = i;
  }

  /**
    * Driver program, funcion to search a pattern
    * @param *pat pointer to the string pattern
    * @param *txt pointer to the text
    **/
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

 /**
   * Funcion that search DNA gen from a DNA secuence
   * @param cadena string of DNA
   * @return string of DNA gen
   **/ 
  string searchGen(string cadena){
    maxlength = cadena.size();
    char ADN[cadena.length()];
    strcpy(ADN, cadena.c_str());
    vector<int> vect_ini;
    vector<int> vect_fin;
    search(ADN,"atg",vect_ini);
    vector<string> codonsStop = {"taa", "tag", "tga"};
    for(string a : codonsStop){
      char pat[3];
      for(int i=0;i<a.size();++i) pat[i] = a[i];
      search(ADN,pat,vect_fin);
    }
    sort(vect_fin.begin(),vect_fin.end());
    int inicial = vect_ini[0];
    bool keep = true;
    gen_count = 0;
    for(int pos : vect_ini){
        if(is_complete()) break;
        if(pos<inicial) continue;
        else inicial = pos;
        for(int posF : vect_fin){
            if(is_complete()) break;
            if(posF<inicial+198) continue;
            if((posF-inicial)%3==0){
                gen << cadena.substr(inicial,posF+3-inicial) << endl;
                gen_count++;
                inicial = posF + 3;
                break;
            }
        }
    }
    return gen.str();
  }
};