#pragma once
#include <boost/graph/adjacency_list.hpp>

using namespace std;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS> undirected_graph;
typedef pair<int, int> Edge;
typedef vector<vector<int>> branchNodes;
typedef vector<vector<Edge>> branchEdges;

branchNodes getBranchNodes(undirected_graph graph, int root);
branchEdges getBranchEdges(undirected_graph graph, int root);
pair<branchNodes, branchEdges> getBranchNodesAndEdges(undirected_graph graph, int root);