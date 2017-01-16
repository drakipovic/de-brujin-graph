#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <deque>
#include <map>

#include <algorithm>
#include <limits.h>
#include <unistd.h>

#include "utils.h"
#include "bit_vector.h"
#include "implicit_graph.h"
#include "explicit_graph.h"



std::string get_path(){
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}


template <typename T>
void debug(std::string what, T value){

    std::cout << what << ": " << value << std::endl;
}


int main(int argc, char **argv){
    int k = 3;

    std::string root_path = get_path();

    int d;
    root_path = root_path.substr(0, root_path.size()-8);
    std::string s = read(root_path + "/tests/" + argv[1], d);
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    uint64_t n = s.size();

    std::string option = argv[2];
    

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
    
    char bwt[n + 1];
    std::deque<uint16_t> Q;
    std::vector<node> G;
    std::vector<bool> bit_vector_left(n + 1);
    std::vector<bool> bit_vector_right(n + 1);
    
    //std::vector< std::pair<bool, bool>> bit_vectors = create_bit_vectors(k, bwt, d - 1, s, G, Q);
    create_bit_vectors(k, bwt, d - 1, s, G, Q, bit_vector_left, bit_vector_right, bitv);

    G = create_implicit_graph(k, bwt, n, d, bit_vector_left, bit_vector_right, G, Q, implicit);
    
    std::map<char, int> C = create_c(bwt, n);
    std::vector<int> lf = create_lf(bwt, C, n);

    std::vector<enode> eG = create_explicit_graph(G, bwt, lf, bit_vector_left, bit_vector_right, d, n, k, expl);

    return 0;

    
}
