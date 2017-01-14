#include <deque>
#include "utils.h"

std::vector<node> create_implicit_graph(int k, char* bwt, int n, int d, std::vector< std::pair<bool, bool>>& bit_vectors,
	std::vector<node>& G, std::deque<uint64_t>& Q);
