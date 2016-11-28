#include <string>
#include <vector>
#include <map>

std::vector<int> create_suffix_array(std::string s);

char* create_bwt(std::string in, std::vector<int>& suffix_array);

std::vector<int> create_lcp(std::string str, std::vector<int>& suffix_array);

std::map<char, int> create_c(char* bwt, int n);