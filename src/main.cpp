#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include "utils.h"
#include "bit_vector.h"

template <typename T>
void debug(std::string what, T value){

    std::cout << what << ": " << value << std::endl;
}


int main(){

    std::string s = "ACTACGTACGTACG$";

    int n = s.size();

    std::vector<int> sa = create_suffix_array(s);

    debug("suffix_array", "");
    for(int i = 1; i < n+1; ++i) printf("%d ", sa[i]+1);
    printf("\n");


    printf("\n");
    debug("bwt", "");
    char *bwt = create_bwt(s, sa);
    char BWT[n+1];
    for(int i = 1; i < n+1; ++i) printf("%c ", bwt[i]);
    for(int i = 1; i < n+1; ++i) BWT[i] = bwt[i];
    std::cout << std::endl;

    debug("lcp", "");
    std::vector<int> lcp = create_lcp(s, sa);
    for(int i = 1; i < n+2; ++i) std::cout << lcp[i] << " " << std::endl;
    std::cout << std::endl;

    std::map<char, int> C = create_c(BWT, n);

    debug("C['A']", C['A']);
    debug("C['C']", C['C']);
    debug("C['G']", C['G']);
    debug("C['T']", C['T']);
    std::cout << std::endl;

    std::cout << "bit_vectors" << std::endl;
    std::vector< std::pair<bool, bool> > bit_vectors = create_bit_vectors(BWT, lcp, 3, n, C);
    for(int i = 1; i < n+1; ++i) std::cout << bit_vectors[i].first << " " << bit_vectors[i].second << std::endl;

    
    return 0;
}
