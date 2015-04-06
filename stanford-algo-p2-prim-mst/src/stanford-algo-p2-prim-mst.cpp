//============================================================================
// Name        : stanford-algo-p2-prim-mst.cpp
// Author      : Xichen Shi
// Version     :
// Copyright   : 
// Description : Prim's MST
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
	bool operator() (pair<long, long> &a, pair<long,long> &b) {
		return (a.second>b.second);
	}
};

class Graph {
public:
	Graph(long num);
	void constructFromFile(string filename);
	void addNode(long v);
	void addEdge(long src, long des, long weight);
	void printGraph();
	void printNode(long v);
	long long getPrimMSTCost(long s);

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
		addEdge(v, u, weight);
	}
	fs.close();
}

void Graph::printGraph() {
	cout << "Adjacency list for graph:" << endl;
	for (auto i = _adj_lists.begin(); i != _adj_lists.end(); i++) {
		cout << i->first << " - ";
		list<pair<long, long>> neighbors = i->second; // get list of neighbor nodes
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

long long Graph::getPrimMSTCost(long s) {
	unordered_map<long, long> heap_keys;
	long long cost = 0;
	vector<pair<long,long>> Q;
	if(_adj_lists.find(s) == _adj_lists.end()) return cost;
	heap_keys[s] = 0;
	for (auto it = _adj_lists.begin(); it != _adj_lists.end(); ++it) {
		long v = it->first;
		if (v != s) {
			heap_keys[v] = 1000000;
		}
		Q.push_back(make_pair(v, heap_keys[v]));
	}
	make_heap(Q.begin(), Q.end(), compare_greater_pair());

	while(!Q.empty()) {
		// Pop next vertex from heap and add to explored
		long u = Q.front().first;
		long ku= Q.front().second;
		cost += ku;
		pop_heap(Q.begin(), Q.end());
		Q.pop_back();

		list<pair<long,long>> neighbors = _adj_lists[u];
		for(auto it = neighbors.begin(); it!= neighbors.end(); ++it) {
			long v = it->first;
			long luv = it->second;
			if ( luv < heap_keys[v]) {
				heap_keys[v] = luv;
				for(unsigned int i = 0; i<Q.size(); i++) {
					if (Q[i].first == v) Q[i].second = luv;
				}
			}
		}
		make_heap(Q.begin(), Q.end(), compare_greater_pair());
	}
	return cost;
}

int main() {
	Graph g(200);
	cout << "Loading file ......" << endl;
	g.constructFromFile("edges.txt");
	cout << "Done" << endl;

	cout <<"Running Prim MST ......" << endl;
	long long score = g.getPrimMSTCost(1);
	cout << "Done" <<endl;

	cout <<"Total Cost of MST: "<<score<<endl;

	return 0;
}
