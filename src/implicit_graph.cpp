#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <deque>
#include <map>

#include "utils.h"
#include "bit_vector.h"
#include "implicit_graph.h"

#include <sdsl/suffix_arrays.hpp>
#include <sdsl/wavelet_trees.hpp>

#define left first
#define right second

#define ALPHABET_SIZE 6

struct elem {

	char c;
	u_int i;
	u_int j;

	elem(char _c, u_int _i, u_int _j) :
		c(_c), i(_i), j(_j) {} ;
};

std::map<char, int> C;
char alphabet[ALPHABET_SIZE] = { '#', '$', 'A', 'C', 'G', 'T'};
std::map<std::pair<u_int, u_int>, sdsl::wt_blcd<> > WT;


void rank_preprocess(const std::vector<std::pair<bool, bool>>& bit_vectors, std::vector<std::pair<u_int, u_int>>& ranks) {

	u_int left_ = 0, right_ = 0;
	for (int i = 0; i < bit_vectors.size(); i++) {
		left_ += bit_vectors[i].left;
		right_ += bit_vectors[i].right;
		ranks.push_back(std::pair<u_int, u_int>(left_, right_));
	}
}

sdsl::wt_blcd<> createWtForRange(int i, int j, const char* bwt, u_int n, u_int size) {

	std::string tmp(size, 'a'); 
	int l = 0;
	for (u_int k = 1; k <= n + 1; k++) {
		if (bwt[k] <= alphabet[j] && bwt[k] >= alphabet[i]) tmp[l++] = bwt[k];
	}

	//std::cout << "tmp = " << tmp << std::endl;
	sdsl::wt_blcd<> wt;
	construct_im(wt, tmp, 1);
	return wt;

} 

void createWT(const char* bwt, u_int n) {

	sdsl::wt_blcd<> wt_root = createWtForRange(0, ALPHABET_SIZE-1, bwt, n, n);
	WT[std::make_pair(0, ALPHABET_SIZE-1)] = wt_root;
	
	sdsl::wt_blcd<> wt;
	for (int i = 0; i < ALPHABET_SIZE-1; i++) {
		for (int j = i+1; j < ALPHABET_SIZE; j++) {
			if (i == 0 && j == ALPHABET_SIZE-1) continue;
			u_int size = 0;
			for (int k = i; k <= j; k++) size += wt_root.rank(n, alphabet[k]);
		
			wt = createWtForRange(i, j, bwt, n, size);
			WT[std::make_pair(i, j)] = wt;
		}
	}

}

void getIntervals(u_int i, u_int j, u_int l, u_int r, std::vector<elem>& list) {

	sdsl::wt_blcd<> wt = WT[std::make_pair(l, r)];

	if (l == r) {
		list.push_back(elem(alphabet[l], C[alphabet[l]] + i, C[alphabet[l]] + j));
	} else {
		u_int m = (l + r) / 2;
		u_int a0 = 0, b0 = 0;
		for (u_int k = l; k <= m; k++) {
			a0 += wt.rank(i - 1, alphabet[k]);
			b0 += wt.rank(j, alphabet[k]);
		}
		
		u_int a1 = i-1-a0;
		u_int b1 = j - b0;
		if (b0 > a0)
			getIntervals(a0 + 1, b0, l, m, list);
		if (b1 > a1)
			getIntervals(a1 + 1, b1, m + 1, r, list);
		
	}
}

std::vector<node> createImplicitGraph(int k, char* bwt, const std::string& s, int d) {

	u_int n = s.size();
	std::deque<u_int> Q;
	std::vector<node> G;
    
	std::vector<std::pair<bool, bool>> bit_vectors = create_bit_vectors(k, bwt, d - 1, s, G, Q);

	std::vector<std::pair<u_int, u_int>> rank_vectors;
	rank_preprocess(bit_vectors, rank_vectors);

	u_int rightMax = rank_vectors[n].right / 2;
	u_int leftMax = rank_vectors[n].left;

	// std::cout << "RANK_VECTOR LEFT:";
	// for (auto i : rank_vectors) std::cout << i.left << " ";
	// std::cout << std::endl;

	// std::cout << "RANK_VECTOR RIGHT:";
	// for (auto i : rank_vectors) std::cout << i.right << " ";
	// std::cout << std::endl;

	// std::cout << "BIT VECTOR LEFT:";
	// for (auto i : bit_vectors) std::cout << i.left << " ";
	// std::cout << std::endl;

	// std::cout << "BIT VECTOR RIGHT:";
	// for (auto i : bit_vectors) std::cout << i.right << " ";
	// std::cout << std::endl;

	// std::cout << "btw: ";
	// for (int k = 1; k <= n; k++) {
	// 	std::cout << bwt[k] << " ";
	// }
	// std::cout << std::endl;
	

	// addition of stop nodes
	u_int id;
	G.resize(rightMax + leftMax + d);
	for (u_int s = 0; s < d; s++) {
		id = rightMax + leftMax + s;
		G[id] = node(1, s, 1, s); 
		Q.push_back(id);
		bit_vectors[s+1].left = 0;
	}

	int q_init_size = Q.size();
	//std::cout << "Q init size = " << q_init_size << std::endl;

	std::cout << "Init graf G:" << std::endl;
	for (auto& it : G) 
		std::cout <<  "node("  << it.len << ", " << it.lb << ", " << it.size << ", " << it.suffix_lb  << ")" << std::endl;
	
	//createWT(bwt, n);
	C = create_c(bwt, n);
	// std::cout << "C array: ";
	// for (char c : alphabet) {
	// 	std::cout <<  "C[" << c << "] = " << C[c] << std::endl;
	// }
	
	sdsl::wt_blcd<> wt = createWtForRange(0, ALPHABET_SIZE-1, bwt, n, n);

	bool extendable;
	u_short lb, rb, len;
	uint64_t size;

	std::vector<uint8_t> chars(wt.sigma);        // List of characters in the interval
	std::vector<uint64_t> rank_c_i(wt.sigma); // Number of occurrence of character in [0 .. i-1]
	std::vector<uint64_t> rank_c_j(wt.sigma); // Number of occurrence of character in [0 .. j-1]

	int iter = 0;
	while (!Q.empty()) {
		if (iter < q_init_size) {
			//std::cout << "front pop" << std::endl;
			id = Q.front();
			Q.pop_front();
		} else {
			//std::cout << "back pop" << std::endl;
			id = Q.back();
			Q.pop_back();
		}
		iter++;
		//std::cout << "id = " << id << ", node= (" << G[id].len << ", " << G[id].lb << ", " << G[id].size << ", " << G[id].suffix_lb  << ")" << std::endl;
		
		lb = G[id].lb;
		rb = G[id].lb + G[id].size - 1;
		len = G[id].len;
		do {
			extendable = false;
			
			std::vector<elem> list;
			//std::cout << "Calling getIntervals lb = " << lb << ", rb = " << rb + 1 << std::endl;
			//getIntervals(lb, rb, 0, ALPHABET_SIZE-1, list);
			interval_symbols(wt, lb, rb + 1, size, chars, rank_c_i, rank_c_j);
			//std::cout << "size = " << size << std::endl;
			for (int it = 0; it < size; it++) {
				uint8_t c = chars[it];
				uint64_t i = C[c] + rank_c_i[it];
				uint64_t j = C[c] + rank_c_j[it] - 1;

				//std::cout << "it = " << it << ", c = " << c << ", rank_c_i = " << rank_c_i[it] <<  ", rank_c_j = " << rank_c_j[it] << std::endl;
				//std::cout << "i = " << i << ", j = " << j << ", c = " << c <<std::endl;
				u_int ones = rank_vectors[i+1].right;

				//std::cout << "ones = " << ones << ", bit_vector = " << bit_vectors[i+1].right << std::endl;
				if (ones % 2 == 0 && bit_vectors[i+1].right == 0) {
					if (c != '$' && c != '#') {
						if (size == 1) {
							extendable = true;
							// G[id].len = G[id].len + 1;
							// G[id].lb = i;
							//std::cout << "Case 3" << std::endl;
							len++;
							lb = i;
							rb = j;
							//std::cout << "Update, cur_lb = " << lb << ", cur_rb = " << rb << ", cur_len = " << len << std::endl;
						} else {
							//std::cout << "Case 4" << std::endl;
							u_int newId = rightMax + rank_vectors[i].left;
							//std::cout << "newId = " << newId << ", rightMax = " << rightMax << ", r = " << rank_vectors[i].left << std::endl;
							G[newId] = node(k, i, j-i+1, i); 
							Q.push_back(newId);

							G[id].lb = lb;
							G[id].len = len;
						}
					} else {
						//std::cout << "Case 2" << std::endl;
						G[id].lb = lb;
						G[id].len = len;
					}
				} else {
					//std::cout << "Case 1" << std::endl;
					G[id].lb = lb;
					G[id].len = len;
				}
			}

			std::cout << "Graf G:" << std::endl;
			for (auto& it : G) {
				std::cout <<  "node("  << it.len << ", " << it.lb << ", " << it.size << ", " << it.suffix_lb  << ")" << std::endl;
			}

		} while (extendable);
	}
 
	std::vector<node> G_out = G;
	// for (u_int i = 0; i < n; i++) {
	// 	if (G[i].isEmpty()) continue;
	// 	G_out.emplace_back(G[i]);
	// }

	std::cout << "Final graf G:" << std::endl;
	for (const auto& it : G_out) std::cout <<  "node("  << it.len << ", " << it.lb << ", " << it.size << ", " << it.suffix_lb  << ")" << std::endl;

	return G_out;
} 

