#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <queue>

#define left first
#define right second


std::vector< std::pair<bool, bool> > create_bit_vectors(char *bwt, std::vector<int> lcp, int k, int n, std::map<char, int> C){
    std::vector< std::pair<bool, bool> > bit_vectors(n);   
    std::queue<int> q;

    int lb = 1, k_index = 0, last_diff = 0;
    bool open = false;
    int counter = 0;

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
                    q.push(counter);
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