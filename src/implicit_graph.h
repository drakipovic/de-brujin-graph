#include <deque>
#include "utils.h"

std::vector<node> create_implicit_graph(int k, char* bwt, int n, int d, std::vector<bool>& left, std::vector<bool>& right,
	std::vector<node>& G, std::deque<uint16_t>& Q);
