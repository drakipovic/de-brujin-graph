//created: Dec 13, 2016
//author: Tena Perak
#include "implicit_graph.h"
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <fstream>

#include <sdsl/suffix_arrays.hpp>
#include <sdsl/wavelet_trees.hpp>
#include "utils.h"
#include "bit_vector.h"

#define left first
#define right second
#define ALPHABET_SIZE 6

void rank_preprocess(const std::vector<bool>& left, const std::vector<bool> & right, 
	std::vector<std::pair<uint16_t, uint16_t>>& ranks) {

	uint16_t left_ = 0, right_ = 0;
	for (int i = 0; i < left.size(); i++) {
		left_ += left[i];
		right_ += right[i];
		ranks.push_back(std::pair<uint16_t, uint16_t>(left_, right_));
	}
}

void create_wt(sdsl::wt_blcd<>& wt, int i, int j, char* bwt, int n) {

	std::string tmp(n, 'a'); 
	for (int k = 1; k <= n + 1; k++) {
		tmp[k-1] = bwt[k];
	}

	construct_im(wt, tmp, 1);
} 

std::vector<node> create_implicit_graph(int k, char* bwt, int n, int d, std::vector<bool>& left, 
	std::vector<bool>& right, std::vector<node>& G, std::deque<uint16_t>& Q, bool print, 
	std::ofstream& out) {
    
	std::vector<std::pair<uint16_t, uint16_t>> rank_vectors;
	rank_preprocess(left, right, rank_vectors);

	uint16_t rightMax = rank_vectors[n].right / 2;
	uint16_t leftMax = rank_vectors[n].left;

	// addition of stop nodes
	uint16_t id;
	G.resize(rightMax + leftMax + d);
	for (int s = 0; s < d; s++) {
		id = rightMax + leftMax + s;
		G[id] = node(1, s, 1, s); 
		Q.push_back(id);
		left[s+1] = 0;
	}

	int q_init_size = Q.size();
	
	
	sdsl::wt_blcd<> wt;
	create_wt(wt, 0, ALPHABET_SIZE-1, bwt, n);

	std::map<char, int> C = create_c(bwt, n);

	bool extendable;
	uint64_t lb, rb, len;
	uint64_t size;

	std::vector<uint8_t> chars(wt.sigma);       
	std::vector<uint64_t> rank_c_i(wt.sigma); // rank of c in [0 .. i-1]
	std::vector<uint64_t> rank_c_j(wt.sigma); // rank of c in [0 .. j-1]
	
	int iter = 0;
	while (!Q.empty()) {
		// using Q as a stack and queue
		if (iter < q_init_size) {
			id = Q.front();
			Q.pop_front();
		} else {
			id = Q.back();
			Q.pop_back();
		}
		iter++;
		
		lb = G[id].lb;
		rb = G[id].lb + G[id].size - 1;
		len = G[id].len;
		do {
			extendable = false;
			interval_symbols(wt, lb, rb + 1, size, chars, rank_c_i, rank_c_j);
			
			for (int it = 0; it < size; it++) {
				uint8_t c = chars[it];
				uint64_t i = C[c] + rank_c_i[it];
				uint64_t j = C[c] + rank_c_j[it] - 1;

				uint64_t ones = rank_vectors[i+1].right;
				if (ones % 2 == 0 && right[i+1] == 0) {
					if (c != '$' && c != '#') {
						if (size == 1) {
							extendable = true;
							len++;
							lb = i;
							rb = j;
						} else {
							uint64_t newId = rightMax + rank_vectors[i].left;
							G[newId] = node(k, i, j-i+1, i); 
							Q.push_back(newId);

							G[id].lb = lb;
							G[id].len = len;
						}
					} else {
						G[id].lb = lb;
						G[id].len = len;
					}
				} else {
					G[id].lb = lb;
					G[id].len = len;
				}
			}

		} while (extendable);
	}
	
	//sort output for testing 
	
	if(print){
		std::vector<node> graph(G.size());
		for(int i = 0; i < G.size(); ++i) graph.push_back(G[i]);
		std::sort(graph.begin(), graph.end(), cmp);

		for (int i = 0; i < graph.size(); ++i){
			if(!graph[i].len) continue;
			out << graph[i].len << " " <<  graph[i].lb << " " << graph[i].size << " " << graph[i].suffix_lb  << std::endl;
		}
	}

	return G;
} 

