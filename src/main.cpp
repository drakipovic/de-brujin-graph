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
    
    char bwt[n + 1];
    std::deque<uint64_t> Q;
    std::vector<node> G;

    std::vector< std::pair<bool, bool>> bit_vectors = create_bit_vectors(k, bwt, d - 1, s, G, Q);

    G = create_implicit_graph(k, bwt, n, d, bit_vectors, G, Q);

    std::map<char, int> C = create_c(bwt, n);
    std::vector<int> lf = create_lf(bwt, C, n);

    std::vector<enode> eG = create_explicit_graph(G, bwt, lf, bit_vectors, d, n, k);

    return 0;

    
}
