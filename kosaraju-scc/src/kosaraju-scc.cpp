//============================================================================
// Name        : kosaraju-scc.cpp
// Author      : Xichen Shi
// Version     :
// Copyright   : 
// Description : Kosaraju's alogrithm on strongly connected components
//============================================================================

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class Graph {
public:
	Graph(int num);
	void constructFromFile(string filename);
	void addNode(int v);
	void addEdge(int src, int des);
	void printGraph();
	void debugGraph();
	void printNode(int v);
	Graph getReverse();
	void DFS(int v, unsigned int &num, vector<bool> &explored);
	void DFS(int v, stack<int> &node_stack, vector<bool> &explored);
	void DFSLoop(stack<int> &node_stack);
	vector<unsigned int> getSCCVector();

private:
	int _num_nodes;
	int _num_edges;
	int _node_max;
	unordered_map<int, list<int>> _adj_lists;
};

Graph::Graph(int num) :
		_num_nodes(0), _num_edges(0), _node_max(0), _adj_lists() {
	_adj_lists.reserve(num);
}

void Graph::addNode(int v) {
	_node_max = (v > _node_max) ? v : _node_max;
	if (_adj_lists.find(v) != _adj_lists.end()) {
		return;
	} else {
		_adj_lists[v] = list<int>(); // Add node w/o outgoing edge
		_num_nodes++;
	}
}

void Graph::addEdge(int src, int des) {
	addNode(src);
	addNode(des);
	_adj_lists[src].push_back(des);
	_num_edges++;
}

void Graph::constructFromFile(string filename) {
	ifstream fs(filename);
	string line;
	int v, e;
	while (getline(fs, line)) {
		stringstream strs(line);
		strs >> v;
		while (strs >> e) {
			addEdge(v, e);
		}
	}
	fs.close();
}

void Graph::printGraph() {
	cout << "Adjacency list for graph:" << endl;
	for (auto i = _adj_lists.begin(); i != _adj_lists.end(); i++) {
		cout << i->first << ":";
		list<int> neighbors = i->second; // get list of neighbor nodes
		for (auto j = neighbors.begin(); j != neighbors.end(); j++) {
			cout << *j << ",";
		}
		cout << endl;
	}
}

void Graph::debugGraph() {
	cout << "Adjacency list for graph:" << endl;
	for (int i = 0; i < _node_max; i++) {
		cout << i << ":";
		list<int> neighbors = _adj_lists[i]; // get list of neighbor nodes
		for (auto j = neighbors.begin(); j != neighbors.end(); j++) {
			cout << *j << ",";
		}
		cout << endl;
	}
}

void Graph::printNode(int v) {
	if (_adj_lists.find(v) == _adj_lists.end()) {
		cout << v << ": No such node" << endl;
	} else {
		cout << v << ":";
		list<int> lst = _adj_lists[v];
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			cout << *it << ",";
		}
		cout << endl;
	}
}

Graph Graph::getReverse() {
	Graph Grev(_num_nodes);
	for (auto i = _adj_lists.begin(); i != _adj_lists.end(); i++) {
		int src = i->first;
		list<int> neighbours = i->second;
		for (auto j = neighbours.begin(); j != neighbours.end(); j++) {
			int des = *j;
			Grev.addEdge(des, src);
		}
	}
	return Grev;
}


void Graph::DFS(int v, stack<int> &node_stack, vector<bool> &explored) {
	stack<pair<bool, int>> localstack;
	localstack.push(make_pair(false, v));

	while (!localstack.empty()) {
		pair<bool, int> node_pair = localstack.top();
		localstack.pop();
		int u = node_pair.second;

		if (node_pair.first) {
			node_stack.push(u);
			continue;
		}

		if (!explored[u]) {
			explored[u] = true;
			localstack.push(make_pair(true, u));
			list<int> neighbors = _adj_lists[u];
			for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
				if (!explored[*it]) {
					localstack.push(make_pair(false,*it));
				}
			}
		}
	}
}

void Graph::DFSLoop(stack<int> &node_stack) {
	// Initialize (reset) time finish and explored nodes
	vector<bool> explored(_node_max + 1, false);

	for (auto i = _adj_lists.begin(); i != _adj_lists.end(); i++) {
		int v = i->first;
		if (!explored[v]) {
			DFS(v, node_stack, explored);
		}
	}
}

void Graph::DFS(int v, unsigned int &num, vector<bool> &explored) {
	stack<int> localstack;
	localstack.push(v);

	while (!localstack.empty()) {
		int u = localstack.top();
		localstack.pop();

		if (!explored[u]) {
			explored[u] = true;
			list<int> neighbors = _adj_lists[u];
			for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
				int t = *it;
				if (!explored[t]) {
					localstack.push(t);
				}
			}
			num++;
		}
	}
}

vector<unsigned int> Graph::getSCCVector() {
	// First DFS
	cout<<"Getting SCCs"<<endl;
	Graph grev = this->getReverse();
	stack<int> node_stack;
	grev.DFSLoop(node_stack);

	// Second DFS
	// Initialize (reset) time finish and explored nodes
	vector<bool> explored(_node_max + 1, false);
	vector<unsigned int> scc_vec;
	while (!node_stack.empty()) {
		int v = node_stack.top();
		node_stack.pop();
		unsigned int count = 0;
		if (!explored[v]) {
			DFS(v, count, explored);
			scc_vec.push_back(count);
		}
	}
	sort(scc_vec.begin(), scc_vec.end());
	return scc_vec;
}

int main() {
	Graph g(10000);
	cout << "Loading file ......"<<endl;
	g.constructFromFile("SCC.txt");
	cout << "Done" << endl;

	vector<unsigned int> output = g.getSCCVector();
	for (unsigned int i = 0; i < 10 && i < output.size(); i++) {
		cout << output[output.size() - i - 1] << ",";
	}
	return 0;
}
