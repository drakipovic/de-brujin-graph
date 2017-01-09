#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include "utils.h"
#include "implicit_graph.h"
#include "bit_vector.h"

template <typename T>
void debug(std::string what, T value){

    std::cout << what << ": " << value << std::endl;
}


int main(){

    std::string s = read("/home/dinek/workspace/de-brujin-graph/input2.fa");
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    int n = s.size();

    std::queue<u_int> q;
    std::vector<node> G(n);
    char bwt[n + 1];
    std::vector< std::pair<bool, bool> > bit_vectors = create_bit_vectors(3, bwt, s, G, q);
    for(int i = 1; i < n+1; ++i) std::cout << bit_vectors[i].second << " " << bit_vectors[i].first << std::endl;

    //G = createImplicitGraph(3, bwt, s);
    
    
    return 0;

    
}