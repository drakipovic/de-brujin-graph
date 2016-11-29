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
    std::vector< std::pair<bool, bool> > bit_vectors = create_bit_vectors(s,3);
    for(int i = 1; i < n+1; ++i) std::cout << bit_vectors[i].first << " " << bit_vectors[i].second << std::endl;

    
    return 0;
}
