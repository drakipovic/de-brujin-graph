#include <string>
#include <vector>
#include <map>

#ifndef UTILS_H
#define UTILS_H

struct node {

    int len; 
    int lb; 
    int size; 
    int suffix_lb;

    node():
        len(0), lb(0), size(0), suffix_lb(0) {}; 
    node(int _len, int _lb, int _size, int _slb):
        len(_len), lb(_lb), size(_size), suffix_lb(_slb) {};
    bool isEmpty() {
    	return len == 0 && lb == 0 && size == 0 && suffix_lb == 0;
    }

};

struct enode {

    int len; 
    std::vector<int> pos_list; 
    std::vector<int> adj_list; 

    enode() {}; 
    enode(int _len):
        len(_len), pos_list(std::vector<int>()), adj_list(std::vector<int>()){};
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