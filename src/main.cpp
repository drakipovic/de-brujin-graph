#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "suffix_array.h"

int main(){

    std::string s = "ACTACGTACGTACG";
    
    std::vector<int> sa = suffix_array(s);

    for(int i = 0; i < sa.size(); ++i) printf("%d|", sa[i]);

    printf("\n");
    	

    return 0;
}
