//created: Nov 28, 2016
//authors: Dino Rakipovic, Tena Perak, Katarina Matic
#include "utils.h"
#include "sais.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

std::string read(const std::string& path, int& num_stop_nodes){
  bool isFirst = true;
  num_stop_nodes = 0;
  std::ifstream file(path);
  std::string str;
  std::string line; 
  int h = 1;
  while (getline( file, line )){
    std::istringstream iss(line);
    if (isFirst){
        isFirst = false;
        continue;
    }
    else if (line.at(0)=='>' && !isFirst){
        num_stop_nodes ++;
        str += (char) 1;
        ++h; // '#'
        continue; 
    }
    else{
        str.append(line);
    }
  }
  str += (char) 0; // '$'
  num_stop_nodes ++;
  return str;
}


char* create_bwt(const std::string& in, const std::vector<uint32_t>& suffix_array, int d){
    int n = suffix_array.size();
    char *bwt = (char*)malloc(n*sizeof(char));

    for(int i = 1; i < n; ++i) {

        if (suffix_array[i] > 0) {
            if (in[suffix_array[i]-1] == 1) bwt[i] = '#';
            else bwt[i] = in[suffix_array[i]-1];
        } else {
            bwt[i] = '$';
        }
        
    }

    return bwt;
}


std::vector<uint32_t> create_suffix_array(const std::string s){
    int n = s.size() + 1;

    int *sa = (int*)malloc(n * sizeof(int));
    int ret = sais((unsigned char*) s.c_str(), sa, n);

    if(ret < 0) std::cout << "Something went wrong!" << std::endl;

    std::vector<uint32_t> sa_v(sa, sa + n);
    return sa_v;
}


std::vector<int32_t> create_lcp(const std::string& s, const std::vector<uint32_t>& sa){
    int n = s.size();
    std::vector<int32_t> lcp(n+2, 0);
    std::vector<int32_t> rank(n+1, 0);

  
    for(int i = 0; i <= n; ++i) rank[sa[i]] = i;

    int k = 0;
    for(int i = 0; i <= n; ++i){

        uint32_t j = sa[rank[i]-1];
        while(i+k < n && j+k < n && s[i+k] == s[j+k]){
            if(s[i+k] == 1) break;
            ++k;
        }
     
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

std::vector<int> create_lf(char* bwt, std::map<char, int>& C, int n){
    std::vector<int> lf(n);
    
    for (int i = 1; i<=n; i++){
        char c = bwt[i];
        if (c == '$'){
            lf[i-1] = 0;
            continue;
        }
        C[c] +=1;
        lf[i-1] = C[c]-1;
    }
    return lf;
}
