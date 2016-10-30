#include <cstdio>
#include <cstdlib>
#include <vector>
#include "suffix_array.h"


int main(){
    std::string s = "banana";
    std::vector<int> sa = suffix_array(s);

    for(int i = 0; i < sa.size(); ++i) printf("%d|", sa[i]);

    printf("\n");

    return 0;
}