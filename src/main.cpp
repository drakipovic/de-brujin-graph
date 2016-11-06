#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "suffix_array.h"
#include <sdsl/bit_vectors.hpp>

int main(){

    std::string s = "ACTACGTACGTACG";
    
    std::vector<int> sa = suffix_array(s);

    for(int i = 0; i < sa.size(); ++i) printf("%d|", sa[i]);

    printf("\n");



	sdsl::bit_vector b = {1,1,0,1,0,0,1};
    std::cout << b << std::endl;
    b = sdsl::bit_vector(80*(1<<20), 0);
    for (size_t i=0; i < b.size(); i+=100)
        b[i] = 1;
    std::cout << sdsl::size_in_mega_bytes(b) << std::endl;
    	

    return 0;
}