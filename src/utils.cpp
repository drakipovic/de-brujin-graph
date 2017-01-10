#include "utils.h"
#include "sais.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>


std::string read(std::string path, int& num_stop_nodes){
  bool isFirst = true;
  num_stop_nodes = 0;
  std::ifstream file(path);
  std::string str;
  std::string line; 
  while (getline( file, line )){
    std::istringstream iss(line);
    if (isFirst){
        isFirst = false;
        continue;
    }
    else if (line.at(0)=='>' && !isFirst){
        num_stop_nodes ++;
        str.append("#");
        continue; 
    }
    else{
        str.append(line);
    }
  }
  str.append("$");
  num_stop_nodes ++;
  return str;
}


char* create_bwt(std::string in, std::vector<int>& suffix_array){
    int n = suffix_array.size();
    char *bwt = (char*)malloc(n*sizeof(char));

    for(int i = 1; i < n; ++i){
	
        bwt[i] = suffix_array[i] > 0 ? in[suffix_array[i]-1] : '$';
    }

    char* ret = bwt;
    return ret;
}


std::vector<int> create_suffix_array(std::string s){
    unsigned char *s_cp = new unsigned char[s.size()+1];
    strcpy((char *)s_cp, s.c_str());

    int n = s.size() + 1;
    int *sa = (int*)malloc(n * sizeof(int));
    int ret = sais(s_cp, sa, n);

    if(ret < 0) std::cout << "Something went wrong!" << std::endl;

    std::vector<int> sa_v;
    for(int i = 0; i < n; ++i){
        sa_v.push_back(sa[i]);
    }

    return sa_v;
}


std::vector<int> create_lcp(std::string s, std::vector<int>& sa){
    int n = s.size();
    std::vector<int> lcp(n+2, 0);
    std::vector<int> rank(n+1, 0);

  
    for(int i = 0; i <= n; ++i) rank[sa[i]] = i;

    int k = 0;
    for(int i = 0; i <= n; ++i){

        int j = sa[rank[i]-1];
        while(i+k < n && j+k < n && s[i+k] == s[j+k]) ++k;
     
        lcp[rank[i]] = k;

        if(k) --k;
    }
    
    lcp[1] = -1;
    lcp[n+1] = -1;
    
    return lcp;
}


std::map<char, int> create_c(char* bwt, int n){
    int a = 0, c = 0, g = 0, t = 0;

    for(int i = 1; i < n + 1; ++i){
        if(bwt[i] == '#') ++a;
        if(bwt[i] < 'C') ++c;
        if(bwt[i] < 'G') ++g;
        if(bwt[i] < 'T') ++t;
    }

    std::map<char, int> C;
    C['$'] = 0;
    C['#'] = 1;
    C['A'] = a+1;
    C['C'] = c;
    C['G'] = g;
    C['T'] = t;

    return C;
}

std::vector<int> create_lf(char* bwt, std::map<char, int> C){
    int n = strlen(bwt);
    std::vector<int> lf(n);
    
    for (int i = 1; i<n; i++){
        char c = bwt[i];
        if (c == '$'){
            lf[i] = 1;
        }
        C[c] +=1;
        lf[i] = C[c];
        //std::cout << i << "  " << lf[i] << '\n';
    }
    return lf;
}
 
