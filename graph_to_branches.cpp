#include "graph_to_branches.hpp"
#include <boost/dynamic_bitset.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <stack>

using namespace boost;

branchNodes getBranchNodes(undirected_graph graph, int root)  // returns a 2-D vector of a format v[branch][nodes]
{
	graph_traits <undirected_graph>::adjacency_iterator first, last;  // graph iterators
	property_map <undirected_graph, vertex_index_t >::type	index_map = get(vertex_index, graph);  // node indices
	dynamic_bitset<> visited(num_vertices(graph), 0);  // keep track of nodes, that were visited
	stack<int> Q;  // stack to save nodes, that are adjacent to not visited nodes
	Q.push(root);
	visited[root] = true;
	int vertexToVisit = 0;
	bool createNewBranch = false;
	branchNodes branchNodes;  // nodes splitted to branches
	while (!Q.empty()) { 
		int u = Q.top();
		Q.pop();
		if (u == root)
			createNewBranch = true;
		bool vertexToVisitRemaining = false;
		tie(first, last) = adjacent_vertices(u, graph);
		for (; first != last; ++first) {
			int vertex = int(get(index_map, *first));
			if (!visited[vertex] && !vertexToVisitRemaining) {
				if (createNewBranch) {
					branchNodes.push_back({});
					createNewBranch = false;
				}
				visited[vertex] = true;
				branchNodes.back().push_back(vertex);
				vertexToVisitRemaining = true;
				vertexToVisit = vertex;  // next node to be visited
			}
			// if at least 1 more unvisited adjacent node is remaining, then add it's parent to stack
			else if (!visited[get(index_map, *first)] && vertexToVisitRemaining) {  
				Q.push(u); 
				break;
			}
		}
		if (vertexToVisitRemaining)
			Q.push(vertexToVisit);
	}
	return branchNodes;
}

branchEdges getBranchEdges(undirected_graph graph, int root)  // returns a 2-D vector of a format v[branch][edge]
{
	graph_traits <undirected_graph>::adjacency_iterator first, last;  // graph iterators
	property_map <undirected_graph, vertex_index_t >::type	index_map = get(vertex_index, graph);  // node indices
	dynamic_bitset<> visited(num_vertices(graph), 0);  // keep track of nodes, that were visited
	stack<int> Q;  // stack to save nodes, that are adjacent to not visited nodes
	Q.push(root);
	visited[root] = true;
	int vertexToVisit = 0;
	bool createNewBranch = false;
	branchEdges branchEdges;  // edges splitted to branches
	while (!Q.empty()) {
		int u = Q.top();
		Q.pop();
		if (u == root)
			createNewBranch = true;
		bool vertexToVisitRemaining = false;
		tie(first, last) = adjacent_vertices(u, graph);
		for (; first != last; ++first) {
			int vertex = int(get(index_map, *first));
			if (!visited[vertex] && !vertexToVisitRemaining) {
				if (createNewBranch) {
					branchEdges.push_back({});
					createNewBranch = false;
				}
				visited[vertex] = true;
				branchEdges.back().push_back(Edge(u, vertex));
				vertexToVisitRemaining = true;
				vertexToVisit = vertex;  // next node to be visited
			}
			// if at least 1 more unvisited adjacent node is remaining, then add it's parent to stack
			else if (!visited[get(index_map, *first)] && vertexToVisitRemaining) {
				Q.push(u);
				break;
			}
		}
		if (vertexToVisitRemaining)
			Q.push(vertexToVisit);
	}
	return branchEdges;
}

pair<branchNodes, branchEdges> getBranchNodesAndEdges(undirected_graph graph, int root)
{
	graph_traits <undirected_graph>::adjacency_iterator first, last;  // graph iterators
	property_map <undirected_graph, vertex_index_t >::type	index_map = get(vertex_index, graph);  // node indices
	dynamic_bitset<> visited(num_vertices(graph), 0);  // keep track of nodes, that were visited
	stack<int> Q;  // stack to save nodes, that are adjacent to not visited verices
	Q.push(root);
	visited[root] = true;
	int vertexToVisit = 0;
	bool createNewBranch = false;
	vector<vector<Edge>> branchEdges;  // vertices splitted to branches
	vector<vector<int>> branchNodes;  // edges splitted to branches
	while (!Q.empty()) {
		int u = Q.top();
		Q.pop();
		if (u == root)
			createNewBranch = true;
		bool vertexToVisitRemaining = false;
		tie(first, last) = adjacent_vertices(u, graph);
		for (; first != last; ++first) {
			int vertex = int(get(index_map, *first));
			if (!visited[vertex] && !vertexToVisitRemaining) {
				if (createNewBranch) {
					branchEdges.push_back({});
					branchNodes.push_back({});
					createNewBranch = false;
				}
				visited[vertex] = true;
				branchEdges.back().push_back(Edge(u, vertex));
				branchNodes.back().push_back(vertex);
				vertexToVisitRemaining = true;
				vertexToVisit = vertex;  // next node to be visited
			}
			// if at least 1 more unvisited adjacent node is remaining, then add it's parent to stack
			else if (!visited[get(index_map, *first)] && vertexToVisitRemaining) {
				Q.push(u);
				break;
			}
		}
		if (vertexToVisitRemaining)
			Q.push(vertexToVisit);
	}
	return make_pair(branchNodes, branchEdges);
}