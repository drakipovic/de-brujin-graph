import os
from collections import defaultdict

root = os.path.abspath(os.path.dirname(__file__))

class Graph(object):

    def __init__(self):
        self.been = {}
        self.path = ""
        self.curr_node = 0

    def parse(self, filename):
        with open(root + '/' + filename) as f:
            data = [line.strip() for line in f.readlines()]
        
        self.graph = self._save_graph(data)
    
    def traverse(self, curr_node = 0):
        for i in range(len(self.graph)):
            self._find_path(i)
        
        return self.path

    def _find_path(self, curr_node):
        if self.been.get(curr_node, None):
            return

        self.been[curr_node] = 1
        self.path += self.graph.get(curr_node)['label']
        for n in self.graph.get(curr_node)['neighbors']:
            self._find_path(n)
        
        
    def _save_graph(self, data):
        current_node = 0
        graph = defaultdict(lambda: defaultdict(list))

        for line in data:
            if '[' in line:
                if int(line[0]) != current_node:
                    current_node += 1

                graph[current_node]['label'] = line.split(" ")[1]
                
            if '->' in line:
                n = line.split(' -> ')
                graph[current_node]['neighbors'].append(int(n[1]))
        
        return graph
    

graph = Graph()
graph.parse('graph.txt')
print graph.traverse()