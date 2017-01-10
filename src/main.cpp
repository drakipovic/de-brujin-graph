#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include "utils.h"
#include "implicit_graph.h"
#include "bit_vector.h"
#include <limits.h>
#include <unistd.h>


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
    std::string root_path = get_path();


    int d;
    root_path = root_path.substr(0, root_path.size()-8);

    std::string s = read(root_path + argv[1], d);
    //std::cout << s << std::endl;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    int n = s.size();


    char bwt[n + 1];
    std::deque<u_int> q;
    std::vector<node> G;
    //std::vector< std::pair<bool, bool> > bit_vectors = create_bit_vectors(3, bwt, d, s, G, q);
    //for(int i = 1; i < n+1; ++i) std::cout << bit_vectors[i].second << " " << bit_vectors[i].first << std::endl;
 
    G = createImplicitGraph(3, bwt, s, d);
    
    return 0;

    
}