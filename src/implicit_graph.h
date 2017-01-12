#include <string>
#include <vector>
#include "utils.h"

std::vector<node> create_implicit_graph(int k, char* bwt, const std::string& s, int stop_nodes, std::vector< std::pair<bool, bool>>& bit_vectors);
