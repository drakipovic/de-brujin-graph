#include <string>
#include <vector>
#include <map>

#ifndef UTILS_H
#define UTILS_H

struct node {

    u_short len; 
    u_short lb; 
    u_short size; 
    u_short suffix_lb;

    node():
        len(0), lb(0), size(0), suffix_lb(0) {}; 
    node(u_short _len, u_short _lb, u_short _size, u_short _slb):
        len(_len), lb(_lb), size(_size), suffix_lb(_slb) {};
    bool isEmpty() {
    	return len == 0 && lb == 0 && size == 0 && suffix_lb == 0;
    }

};

struct enode {

    u_short len; 
    std::vector<u_short> pos_list; 
    std::vector<u_short> adj_list; 

    enode() {}; 
    enode(u_short _len):
        len(_len), pos_list(std::vector<u_short>()), adj_list(std::vector<u_short>()){};
    bool isEmpty() {
    	return len == 0 && pos_list.empty() && adj_list.empty();
    }

};

std::string read(std::string path, int& num_stop_nodes);

std::vector<int> create_suffix_array(std::string s);

char* create_bwt(std::string in, std::vector<int>& suffix_array, int d);

std::vector<int> create_lcp(std::string str, std::vector<int>& suffix_array);

std::map<char, int> create_c(char* bwt, int n);

std::vector<int> create_lf(char* bwt, std::map<char, int> C, int n);

#endif /* UTILS_H */