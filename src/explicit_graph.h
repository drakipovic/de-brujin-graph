#include <vector>
#include <fstream>

#include "utils.h"

std::vector<enode> create_explicit_graph(std::vector<node> iG, char* bwt, std::vector<int> lf, 
    std::vector<bool>& left, std::vector<bool>& right, int d, int n, int k, bool print, 
    std::ofstream& out);
