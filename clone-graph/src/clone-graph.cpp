//============================================================================
// Name        : clone-graph.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct UndirectedGraphNode {
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};

UndirectedGraphNode *cloneGraphBFS(UndirectedGraphNode *node) {
	if(node==NULL) return NULL;
	queue<UndirectedGraphNode*> q;
	unordered_map<UndirectedGraphNode*,UndirectedGraphNode*> clone_map;

	UndirectedGraphNode *nodecopy = new UndirectedGraphNode(node->label);
	clone_map[node] = nodecopy;
	q.push(node);

	while(!q.empty())
	{
		UndirectedGraphNode *curr = q.front();
		q.pop();
		for(unsigned int i=0;i<curr->neighbors.size();i++) // for each neighbor
		{
			UndirectedGraphNode *neighbor = curr->neighbors[i];
			if(clone_map.find(neighbor)==clone_map.end()) // if neighbor  doesn't exist
			{
				UndirectedGraphNode *p = new UndirectedGraphNode(neighbor->label);
				clone_map[curr]->neighbors.push_back(p);
				clone_map[neighbor] = p;
				q.push(neighbor);
			}
			else // if neighbor exist
			{
				clone_map[curr]->neighbors.push_back(clone_map[neighbor]);
			}
		}
	}

	return nodecopy;
}

unordered_map<UndirectedGraphNode*,UndirectedGraphNode*> clone_map;

UndirectedGraphNode *cloneGraphDFS(UndirectedGraphNode *node) {
    if(node==NULL) return NULL;

    if(clone_map.find(node)==clone_map.end()){
        UndirectedGraphNode* node_copy = new UndirectedGraphNode(node->label);
        clone_map[node] = node_copy;
        for(unsigned int i=0; i<node->neighbors.size(); i++)
        {
            clone_map[node]->neighbors.push_back(cloneGraphDFS(node->neighbors[i]));
        }
    }
    return clone_map[node];
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
