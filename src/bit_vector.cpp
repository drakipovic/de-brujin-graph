//created: Nov 28, 2016
//author: Dino Rakipovic
#include "bit_vector.h"
#include <utility>
#include <iostream>
#include "sais.h"

void create_bit_vectors(int k, char* bwt, int d, const std::string& s, std::vector<node>& G, 
    std::deque<uint16_t>& Q, std::vector<bool>& bit_vector_left, std::vector<bool>& bit_vector_right, bool print) {
    
    int n = s.size();
    
    std::vector<uint32_t> suffix_array = create_suffix_array(s);

    char *BWT = create_bwt(s, suffix_array, d + 1);
    for(int i = 1; i < n+1; ++i){
        bwt[i] = BWT[i];
    }

    std::vector<int32_t> lcp = create_lcp(s, suffix_array);
    std::map<char, int> C = create_c(bwt, n);

    int lb = 1, k_index = 0, last_diff = 0;
    bool open = false;
    uint16_t counter = 0;

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
                    bit_vector_right[lb] = true;
                    bit_vector_right[i-1] = true;
                    G.push_back(node(k, lb-1, i-lb, lb-1));
                    Q.push_back(counter);
                    ++counter;
                }
                
                if(last_diff > lb){
                    for(int j = lb; j <= i-1; ++j){
                        char c = bwt[j];

                        if(c != '$' && c != '#') bit_vector_left[C[c]] = true;
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
            bit_vector_left[i] = false;
            if(bit_vector_right[i]){
                open = false;
            }
        }
        else if(bit_vector_right[i]){
            bit_vector_left[i] = false;
            open = true;
        }
    }

    if(print){
        for(int i = 1; i < bit_vector_left.size(); ++i){
            std::cout << bit_vector_right[i] << " " << bit_vector_left[i] << std::endl;
        }
    }

}
