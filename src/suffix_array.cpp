#include "suffix_array.h"
#include "sais.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>


std::vector<int> suffix_array(std::string s){
    unsigned char *s_cp = new unsigned char[s.size()+1];
    strcpy((char *)s_cp, s.c_str());

    int n = s.size() + 1;
    int *sa = (int*)malloc(n * sizeof(int));
    int ret = sais(s_cp, sa, n);

    std::vector<int> sa_v;
    for(int i = 0; i < n; ++i){
        sa_v.push_back(sa[i]);
    }

    return sa_v;
}