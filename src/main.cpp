#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <fstream>

#include <algorithm>
#include <limits.h>
#include <unistd.h>

#include "utils.h"
#include "bit_vector.h"
#include "implicit_graph.h"
#include "explicit_graph.h"


int main(int argc, char **argv){
    int d;

    std::string s = read(argv[1], d);
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    uint64_t n = s.size();

    std::ofstream out;
    out.open(argv[2]);

    std::string option = argv[3];
    
    bool implicit = false, expl = false, bitv = false;
    if(option == "--implicit"){
        implicit = true;
    }
    else if(option == "--explicit"){
        expl = true;
    }
    else if(option =="--bitvector"){
        bitv = true;
    }

    std::string k = argv[4];
    int i_k = std::stoi(k.substr(3, k.size()));

    char bwt[n + 1];
    std::deque<uint16_t> Q;
    std::vector<node> G;
    std::vector<bool> bit_vector_left(n + 1);
    std::vector<bool> bit_vector_right(n + 1);
    
    create_bit_vectors(i_k, bwt, d - 1, s, G, Q, bit_vector_left, bit_vector_right, bitv, out);

    G = create_implicit_graph(i_k, bwt, n, d, bit_vector_left, bit_vector_right, G, Q, implicit, out);
    
    std::map<char, int> C = create_c(bwt, n);
    std::vector<int> lf = create_lf(bwt, C, n);

    std::vector<enode> eG = create_explicit_graph(G, bwt, lf, bit_vector_left, bit_vector_right, d, n, i_k, expl, out);

    return 0;

    
}
