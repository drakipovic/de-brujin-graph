#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "utils.h"

std::vector< std::pair<bool, bool> > create_bit_vectors(int k, char* bwt, int d, const std::string& s, std::vector<node>& G, std::queue<u_int>& q);
