//============================================================================
// Name        : dijkstra-shortest-path.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Dijkstra's shortest path algorithm
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
	unordered_map<long,long> getShortestPaths(long s);

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
	long v, e, weight;
	while (getline(fs, line)) {
		stringstream strs(line);
		strs >> v;
		while (!strs.eof()) {
			strs >> e >> weight;
			addEdge(v, e, weight);
		}
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

unordered_map<long,long> Graph::getShortestPaths(long s) {
	unordered_map<long, long> dist;
	vector<pair<long,long>> Q;
	if(_adj_lists.find(s) == _adj_lists.end()) return dist;
	dist[s] = 0;
	for (auto it = _adj_lists.begin(); it != _adj_lists.end(); ++it) {
		long v = it->first;
		if (v != s) {
			dist[v] = 1000000;
		}
		Q.push_back(make_pair(v, dist[v]));
	}
	make_heap(Q.begin(), Q.end(), compare_greater_pair());

	while(!Q.empty()) {
		long u = Q.front().first;
		pop_heap(Q.begin(), Q.end());
		Q.pop_back();
		list<pair<long,long>> neighbors = _adj_lists[u];
		for(auto it = neighbors.begin(); it!= neighbors.end(); ++it) {
			long v = it->first;
			long luv = it->second;
			long alt = dist[u] + luv;
			if ( alt < dist[v]) {
				dist[v] = alt;
				for(unsigned int i = 0; i<Q.size(); i++) {
					if (Q[i].first == v) Q[i].second = alt;
				}
			}
		}
		make_heap(Q.begin(), Q.end(), compare_greater_pair());
	}
	return dist;
}

int main() {
	Graph g(200);
	cout << "Loading file ......" << endl;
	g.constructFromFile("dijkstraData.txt");
	cout << "Done" << endl;

	cout <<"Running Dijkstra ......" << endl;
	unordered_map<long,long> dist = g.getShortestPaths(1);
	cout << "Done" <<endl;

	vector<long> arr = {7,37,59,82,99,115,133,165,188,197};
	for(unsigned int i = 0; i<arr.size(); i++) {
		cout<<dist[arr[i]]<<",";
	}
	return 0;
}
