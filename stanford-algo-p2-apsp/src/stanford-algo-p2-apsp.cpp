//============================================================================
// Name        : stanford-algo-p2-apsp.cpp
// Author      : Xichen Shi
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <climits>
#include <unordered_map>
#include <utility>
#include <list>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct compare_greater_pair {
	bool operator()(pair<long, long> &a, pair<long, long> &b) {
		return (a.second > b.second);
	}
};

class Graph {
public:
	Graph(long num);
	long getNumNodes() {
		return _num_nodes;
	}
	long getNumEdges() {
		return _num_edges;
	}
	long getNodeMax() {
		return _node_max;
	}
	void constructFromFile(string filename);
	void addNode(long v);
	void addEdge(long src, long des, long weight);
	void printGraph();
	void printNode(long v);
	void getFloydWarshallApsp(vector<vector<long> > &paths);

private:
	long _num_nodes;
	long _num_edges;
	long _node_max;
	unordered_map<long, list<pair<long, long>>> _adj_lists;
};

Graph::Graph(long num) :
		_num_nodes(0), _num_edges(0), _node_max(0), _adj_lists() {
	_adj_lists.reserve(num);
}

void Graph::addNode(long v) {
	_node_max = (v > _node_max) ? v : _node_max;
	if (_adj_lists.find(v) != _adj_lists.end()) {
		return;
	} else {
		_adj_lists[v] = list<pair<long, long>>(); // Add node w/o outgoing edge
		_num_nodes++;
	}
}

void Graph::addEdge(long src, long des, long weight) {
	addNode(src);
	addNode(des);
	_adj_lists[src].push_back(make_pair(des, weight));
	_num_edges++;
}

void Graph::constructFromFile(string filename) {
	ifstream fs(filename);
	string line;
	string edge;
	long num_nodes, num_edges;
	getline(fs, line);
	stringstream strs(line);
	strs >> num_nodes >> num_edges;
	long u, v, weight;
	while (getline(fs, line)) {
		stringstream strs(line);
		strs >> u >> v >> weight;
		addEdge(u, v, weight);
	}
	fs.close();
}

void Graph::printGraph() {
	cout << "Adjacency list for graph:" << endl;
	for (auto i = _adj_lists.begin(); i != _adj_lists.end(); i++) {
		cout << i->first << " - ";
		list<pair<long, long> > neighbors = i->second; // get list of neighbor nodes
		for (auto j = neighbors.begin(); j != neighbors.end(); j++) {
			cout << j->first << ":" << j->second << ",";
		}
		cout << endl;
	}
}

void Graph::printNode(long v) {
	if (_adj_lists.find(v) == _adj_lists.end()) {
		cout << v << ": No such node" << endl;
	} else {
		cout << v << ":";
		list<pair<long, long>> lst = _adj_lists[v];
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			cout << it->first << ":" << it->second << ",";
		}
		cout << endl;
	}
}

void Graph::getFloydWarshallApsp(vector<vector<long> > &paths) {
	long n = _node_max;
	vector<vector<long> > paths_old(n + 1, vector<long>(n + 1, 0));
	vector<vector<long> > paths_new(n + 1, vector<long>(n + 1, 0));

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			// Break for non-existent source vertex
			if(_adj_lists.find(i) == _adj_lists.end()) break;
			// Constructing base case
			if (i == j) {
				paths_old[i][j] = 0;
			} else {
				list<pair<long, long> > neighbors = _adj_lists[i];
				long temp = LONG_MAX;
				for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
					if(it->first == j) {
						temp = it->second;
						break;
					}
				}
				paths_old[i][j] = temp;
			}
		}
	}

	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				long case1 = paths_old[i][j];
				long case2 =
						(paths_old[i][k] == LONG_MAX
								|| paths_old[k][j] == LONG_MAX) ?
								LONG_MAX : (paths_old[i][k] + paths_old[k][j]);
				paths_new[i][j] = min(case1, case2);
			}
		}
		paths_old = paths_new;
	}
	paths = paths_new;
}

int main() {
	Graph g(1000);
	cout << "Loading file ......" << endl;
	g.constructFromFile("g3.txt");
	cout << "Done" << endl;

	vector<vector<long> > apsp_paths;
	g.getFloydWarshallApsp(apsp_paths);

	long minPath = 0;
	for(int i = 1; i < apsp_paths.size(); i++) {
		for (int j = 1; j < apsp_paths[i].size(); j++) {
			if( i!=j ) {
				minPath = min(apsp_paths[i][j],minPath);
			} else if(apsp_paths[i][j] < 0) {
				cout<<"NULL"<<endl;
			}
		}
	}
	cout<<minPath<<endl;
	return 0;
}
