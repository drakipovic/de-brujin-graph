#include <string>
#include <vector>
#include "utils.h"

std::vector<node> createImplicitGraph(int k, char* bwt, const std::string& s, int stop_nodes, std::vector< std::pair<bool, bool>>& bit_vectors);
