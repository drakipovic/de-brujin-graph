#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <deque>
#include "utils.h"

#define left first
#define right second


std::vector< std::pair<bool, bool> > create_bit_vectors(int k, char* bwt, int d, const std::string& s, std::vector<node>& G, std::deque<u_int>& q){

    int n = s.size();
    std::vector< std::pair<bool, bool> > bit_vectors(n + 1);   
    std::vector<int> suffix_array = create_suffix_array(s);
    // for(int i = 1; i < n+1; ++i) std::cout << suffix_array[i] << " ";
    // std::cout<<std::endl;

    char *BWT = create_bwt(s, suffix_array, d + 1);
    int tmp;
    for(int i = 1; i < n+1; ++i){
        if(BWT[i] == '$') tmp = i;
        bwt[i] = BWT[i];
    }
    char t = bwt[tmp];
    //std::cout << t << std::endl;
    //std::cout << "BWT: " << std::endl;
    // bwt[tmp] = bwt[tmp + d];
    // bwt[tmp+d] = t;
    // for(int i = 1; i < n+1; ++i) std::cout << bwt[i] << std::endl;
    // std::cout << std::endl;

    std::vector<int> lcp = create_lcp(s, suffix_array);
    std::map<char, int> C = create_c(bwt, n);


    int lb = 1, k_index = 0, last_diff = 0;
    bool open = false;
    u_int counter = 0;

    for(int i = 2; i <= n+1; ++i){
        C[bwt[i-1]]++;
        if(lcp[i] >= k){
            open = true;
            if(lcp[i] == k){
                k_index = i;
            }
        }
        else{
            if(open){
                if(k_index > lb){
                    bit_vectors[lb].right = true;
                    bit_vectors[i-1].right = true;
                    G.push_back(node(k, lb-1, i-lb, lb-1));
                    q.push_back(counter);
                    ++counter;
                }
                //std::cout << last_diff << " " << lb << std::endl;
                if(last_diff > lb){
                    for(int j = lb; j <= i-1; ++j){
                        char c = bwt[j];

                        if(c != '$' && c != '#') bit_vectors[C[c]].left = true;
                    }
                }
                open = false;
            }
            lb = i;
        }
        if(bwt[i] != bwt[i-1]) last_diff = i;
        
    }
    open = false;

    for(int i = 0; i < n+1; ++i){
        if(open){
            bit_vectors[i].left = false;
            if(bit_vectors[i].right){
                open = false;
            }
        }
        else if(bit_vectors[i].right){
            bit_vectors[i].left = false;
            open = true;
        }
    }

    return bit_vectors;

}
