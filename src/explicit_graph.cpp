#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <math.h>
#include "utils.h"

#define left first
#define right second



std::vector<enode> create_explicit_graph(std::vector<node> iG, char* bwt, std::vector<int> lf, std::vector< std::pair<bool, bool> > bit_vectors, int d, int n, int k){
    
    //std::cout << d<< std::endl;
    // std::cout << "Final graf G:" << std::endl;
	// for (const auto& it : iG) std::cout <<  "node("  << it.len << ", " << it.lb << ", " << it.size << ", " << it.suffix_lb  << ")" << std::endl;
    // for (const auto& it : lf) std::cout <<  "lf("  << it  << ")" << std::endl;    


    //std::cout << pos << std::endl;

    std::vector<enode> G(iG.size());
    std::vector<int> start_nodes(d);
    for (int j = 1; j<G.size(); j++){
        G[j] = enode();
    }

    //za lef i right max
    std::vector<std::pair<u_int, u_int>> rank_vectors;
    u_int left_ = 0, right_ = 0;
	for (int i = 0; i < bit_vectors.size(); i++) {
		left_ += bit_vectors[i].left;
		right_ += bit_vectors[i].right;
		rank_vectors.push_back(std::pair<u_int, u_int>(left_, right_));
	}
    u_int rightMax = (rank_vectors[n].right / 2 );
	u_int leftMax = rank_vectors[n].left;

    int i = 0;
    int pos = n+1;
    
    for (const auto& it : rank_vectors) std::cout <<  "ra("  << it.first << "," << it.second << ")" << std::endl;
    std::cout << std::endl << "leftMax" << leftMax << "rightMax" << rightMax << std::endl;
    //for (const auto& it : bit_vectors) std::cout <<  "bit("  << it.first << "," << it.second << ")" << std::endl;
    std::cout << " n " << n << " d " << d << " k " << k << std::endl;
    
    std::cout << "pos " << pos << std::endl;
    
    for (int s = 0; s< d; s++){
        std::cout << "i " << i  << " s " << s << std::endl;
        //int id = rightMax  + d + i; // jer idem 3 po 3 od zadnjeg, a rightMax je za 1 manji
        int id = rightMax + leftMax + s;
        pos = pos - iG[id].len;
        int idx = iG[id].lb;

        G[id].len = iG[id].len;
        G[id].pos_list.emplace_back(pos);

        

        std::cout << "id " << id << std::endl;
        std::cout << "idx " << idx << std::endl;
        std::cout << "iG[id].len " << iG[id].len  << std::endl;
        std::cout << "pos u for " << pos << std::endl;
        std::cout << "i u for " << i << std::endl;

        std::cout << bwt <<std::endl;

        char test;
        int end = 0;
        while(bwt[idx+1]!='$' && bwt[idx+1]!='#'){
            i = lf[idx];
            test = bwt[idx+1];
            std::cout << "test: " << test <<std::endl;
            int ones = rank_vectors[i+1].right; 
            std::cout << "ones " << ones << std::endl;
            int newId = 0;

            std::cout << "rank r " << bit_vectors[i+1].right << std::endl;
            if (ones%2==0 and bit_vectors[i+1].right==0){
                newId = rightMax + rank_vectors[i].left;
                std::cout << "newId if " << newId << std::endl;

            }
            else{
                newId = (ones-1)/2;
                std::cout << "newId else " << newId << std::endl;
            }

            pos = pos - (iG[newId].len - k+1);

            G[newId].adj_list.emplace_back(id);
            G[newId].pos_list.emplace_back(pos);
            G[newId].len = iG[newId].len;

            idx = iG[newId].lb + (i - iG[newId].suffix_lb);
            std::cout << "idx u while  lb  suf" << idx <<   "  " <<  iG[newId].lb << " "  << iG[newId].suffix_lb<< std::endl;
        
            std::cout << "pos u while " << pos << std::endl;

            id = newId;
            std::cout << "id u while kraj " << id << std::endl;
            std::cout << "i while kraj " <<i << std::endl;
            end++;

        }
        start_nodes[d-1-s] = id;
        i = lf[idx];
    }
   
    return G;



    /*
    std::cout << "Final graf eG:" << std::endl;
    for (const auto& it : G) {
        std::cout <<  "node( " << it.len << " [";
        for (int i = 0; i<it.pos_list.size(); i++){
            std::cout << it.pos_list[i] << " , ";
        }
        std::cout << "], [ ";
        for (int i = 0; i<it.adj_list.size(); i++){
            std::cout << it.adj_list[i] << " , ";
        }
        std::cout << "] )" << std::endl;
    }*/
    
}