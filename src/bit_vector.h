#include <deque>
#include "utils.h"

void create_bit_vectors(int k, char* bwt, int d, const std::string& s, std::vector<node>& G, 
	std::deque<uint16_t>& Q, std::vector<bool>& left, std::vector<bool>& right, bool print);
