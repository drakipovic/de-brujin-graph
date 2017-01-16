//created: Jan 1, 2017
//author: Katarina Matic
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <math.h>
#include <fstream>

#include "utils.h"

#define left first
#define right second


void print_graph(const std::vector<enode>& G, std::ofstream& out);

std::vector<enode> create_explicit_graph(std::vector<node> iG, char* bwt, std::vector<int> lf, 
    std::vector<bool>& left, std::vector<bool>& right, int d, int n, int k, bool print, 
    std::ofstream& out){

    //initialize explicit graph nodes
    std::vector<enode> G(iG.size());
    std::vector<int> start_nodes(d);
    for (int j = 1; j<G.size(); j++){
        G[j] = enode();
    }

    //construct rank vectors
    std::vector<std::pair<int, int>> rank_vectors;
    int left_ = 0, right_ = 0;
	for (int i = 0; i < left.size(); i++) {
		left_ += left[i];
		right_ += right[i];
		rank_vectors.push_back(std::pair<int, int>(left_, right_));
	}
    int rightMax = (rank_vectors[n].right / 2 );
	int leftMax = rank_vectors[n].left;

    //initial position
    int i = 0;
    int pos = n+1;
    
    //for every sequence
    for (int s = 0; s< d; s++){
        int id = rightMax + leftMax + s;
        pos = pos - iG[id].len;
        int idx = iG[id].lb;

        G[id].len = iG[id].len;
        G[id].pos_list.emplace_back(pos);

        char test;
        //while char in bwt is not end of sequence or end of pan-genome
        while(bwt[idx+1]!='$' && bwt[idx+1]!='#'){
            i = lf[idx];
            test = bwt[idx+1];
            int ones = rank_vectors[i+1].right; 
            int newId = 0;

            //calculate new id
            if (ones % 2 == 0 and right[i+1] == 0){
                newId = rightMax + rank_vectors[i].left;
            }
            else{
                newId = (ones-1)/2;
            }
            
            pos = pos - (iG[newId].len - k+1);

            //add values to new node
            G[newId].adj_list.emplace_back(id);
            G[newId].pos_list.emplace_back(pos);
            G[newId].len = iG[newId].len;

            //calculate next indices
            idx = iG[newId].lb + (i - iG[newId].suffix_lb);
            id = newId;
        }
        //next start node
        start_nodes[d-1-s] = id;
        i = lf[idx];
    }
    if(print)
        print_graph(G, out);

    return G;
}

void print_graph(const std::vector<enode>& G, std::ofstream& out) {

    uint64_t labels = 0;
    uint64_t edges = 0;
    
    uint64_t node_number = 0;
    for(const auto& node : G)
    {
        labels += G[node_number].pos_list.size();
        edges += G[node_number].adj_list.size();
        // Print node_number
        out << node_number << " ";
        // Print label
        out << "[label=\"";
        {
            out << node.pos_list[node.pos_list.size()-1];
            for(uint64_t j=node.pos_list.size()-2; j<node.pos_list.size()-1; --j)
            {
                out << "," << node.pos_list[j];
            }
        }
        out << ":" << node.len << "\"]\n";
        // Print edges
        for(uint64_t j=node.adj_list.size()-1; j<node.adj_list.size(); --j)
        {
            out << node_number << " -> " << node.adj_list[j] << "\n";
        }
        ++node_number;
    }
}