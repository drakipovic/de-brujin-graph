#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <map>

#include "utils.h"
#include "bit_vector.h"
#include "implicit_graph.h"

#include <sdsl/suffix_arrays.hpp>
#include <sdsl/wavelet_trees.hpp>

#define left first
#define right second

#define ALPHABET_SIZE 5

struct elem {

	char c;
	u_int i;
	u_int j;

	elem(char _c, u_int _i, u_int _j) :
		c(_c), i(_i), j(_j) {} ;
};

std::map<char, int> C;
char alphabet[ALPHABET_SIZE] = { '$', 'A', 'C', 'G', 'T'};
std::map<std::pair<u_int, u_int>, sdsl::wt_blcd<> > WT;


void rank_preprocess(const std::vector<std::pair<bool, bool>>& bit_vectors, std::vector<std::pair<u_int, u_int>>& ranks) {

	u_int left_ = 0, right_ = 0;
	for (const auto& it : bit_vectors) {
		left_ += it.left;
		right_ += it.right;
		ranks.push_back(std::pair<u_int, u_int>(left_, right_));
	}
}

sdsl::wt_blcd<> createWtForRange(int i, int j, const char* bwt, u_int n, u_int size) {

	std::string tmp(size, 'a'); 
	int l = 0;
	for (u_int k = 1; k <= n + 1; k++) {
		if (bwt[k] <= alphabet[j] && bwt[k] >= alphabet[i]) tmp[l++] = bwt[k];
	}

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

std::vector<node> createImplicitGraph(int k, char* bwt, const std::string& s, int stop_nodes) {

	u_int n = s.size();
	std::queue<u_int> Q;
	std::vector<node> G(n); // ne znam kolko ih treba bit
    
	std::vector<std::pair<bool, bool>> bit_vectors = create_bit_vectors(k, bwt, stop_nodes, s, G, Q); 

	std::vector<std::pair<u_int, u_int>> rank_vectors;
	rank_preprocess(bit_vectors, rank_vectors);

	u_int rightMax = rank_vectors[n-1].left / 2;
	u_int leftMax = rank_vectors[n-1].right;


	u_int d = 1; // number of sequnces in S, should be computed during bit vector creation

	// addition of stop nodes
	u_int id;
	for (u_int s = 1; s <= d; s++) {
		id = rightMax + leftMax + s;
		G[id] = node(1, s, 1, s); 
		Q.push(id);
		bit_vectors[s].left = 0;
	}

	createWT(bwt, n);
	C = create_c(bwt, n);

	bool extendable;
	u_short lb, rb;
	while (!Q.empty()) {
		id = Q.front();
		Q.pop();
		do {
			extendable = false;
			lb = G[id].lb;
			rb = lb + G[id].size - 1;
			std::vector<elem> list;
			getIntervals(lb, rb, 0, ALPHABET_SIZE-1, list);
			for (const auto& it : list) {
				u_int ones = rank_vectors[it.i].right;
				if (ones % 2 == 0 && bit_vectors[it.i].right == 0) {
					if (it.c != '$' && it.c != '#') {
						if (list.size() == 1) {
							extendable = true;
							G[id].len = G[id].len + 1;
							G[id].lb = it.i;
						} else {
							u_int newId = rightMax + rank_vectors[it.i-1].left + 1;
							G[newId] = node(k, it.i, it.j-it.i+1, it.i); 
							Q.push(newId);
						}
					}
				}
			}

		} while (extendable);
	}
 
	std::vector<node> G_out;
	for (u_int i = 1; i < n; i++) {
		if (G[i].isEmpty()) break;
		G_out.emplace_back(G[i]);
	}

	std::cout << "Final graf G:" << std::endl;
	for (const auto& it : G_out) std::cout <<  "node("  << it.len << ", " << it.lb << ", " << it.size << ", " << it.suffix_lb  << ")" << std::endl;

	return G_out;
} 

