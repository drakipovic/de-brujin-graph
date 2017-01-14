#include <deque>

#include "utils.h"

std::vector<std::pair<bool, bool>> create_bit_vectors(int k, char* bwt, int d, const std::string& s, std::vector<node>& G, 
	std::deque<uint64_t>& Q);
