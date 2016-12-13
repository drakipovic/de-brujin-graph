#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "utils.h"
#include "implicit_graph.h"
#include "bit_vector.h"

template <typename T>
void debug(std::string what, T value){

    std::cout << what << ": " << value << std::endl;
}


int main(){

    std::string s = "ACTACGTACGTACG$";
    int n = s.size();

    std::queue<u_int> q;
    std::vector<node> G;
    char bwt[n + 1];
    // std::vector< std::pair<bool, bool> > bit_vectors = create_bit_vectors(3, bwt, s, G, q);
    // for(int i = 1; i < n+1; ++i) std::cout << bit_vectors[i].first << " " << bit_vectors[i].second << std::endl;

    G = createImplicitGraph(3, bwt, s);

    
    return 0;
}
