# Split_graph_into_branches
C++ Functions to split a given undirected graph into branch nodes or branch edges.

# Definition of branch and root node
Branches are defined as subsets of nodes in a graph, that are connected to each other only through a `root` node. That means if the `root` will be removed from a graph, each branch will be disconnected from other branches, therefore building a separate sub-graph. If removing the `root` node does not disconnect any nodes from the rest of graph, that graph has only 1 branch. 

Branch is represented either by vector of nodes, which are included in the branch, or by vector of edges, which are connecting the nodes in the branch. The `root` node does not belong to any branch. But the edges, that connect the `root` node with nodes in a branch, will belong to that branch.

# Brief documentation
- The function `vector<vector<int>> getBranchNodes(undirected_graph graph, int root)` returns a vector of branches. Here branch is represented by vector of nodes, that are included in the branch. Therefore the function returns a 2D vector of a format `vec[branch][node]`.

- The function `vector<vector<Edge>> getBranchEdges(undirected_graph graph, int root)` returns a vector of branches. Here branch is represented by vector of edges, that are connecting the nodes in the branch. Therefore the function returns a 2D vector of a format `vec[branch][edge]`.

- The function `pair<vector<vector<int>>, vector<vector<Edge>>> getBranchNodesAndEdges(undirected_graph graph, int root)` returns a pair of vectors of branches. First element of the pair is a vector of branches, represented by vector of nodes, and the second element is a vector of branches, represented by vector of edges. The return value is basically a result of `make_pair(getBranchNodes(g, root), getBranchEdges(g, root))`, but the algorithm will be executed only once.

- `Edge` is a `typedef` for `pair<int, int>`, representing a pair of nodes. 

- `undirected_graph` is a typedef for boost's adjacency list: `boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS>`