#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// A* Search Algorithm to find the shortest path from 'start' to 'target'
void astar(int start, int target, vector<vector<pair<int, int>>>& adj, vector<int>& h) {
    int n = adj.size();
    
    // g_score stores the exact cost from the start node to the current node
    // We initialize all costs to infinity (INT_MAX), except the start node
    vector<int> g_score(n, INT_MAX);
    g_score[start] = 0;
    
    // Priority queue to store {f_score, node}. 
    // greater<> ensures the smallest f_score is always at the top.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // f_score = g_score + h_score. Push the starting node.
    pq.push({g_score[start] + h[start], start});
    
    // To reconstruct the path later, we remember where we came from
    vector<int> parent(n, -1);
    vector<int> visit(n, 0);

    while(!pq.empty()) {
        // Get the node with the lowest f_score
        int current = pq.top().second;
        pq.pop();

        // If we reached our destination, print the path and exit!
        if(current == target) {
            cout << "\nPath found: ";
            vector<int> path;
            int curr = target;
            
            // Backtrack using the parent array to get the full path
            while(curr != -1) {
                path.push_back(curr);
                curr = parent[curr];
            }
            reverse(path.begin(), path.end()); // Reverse it to print from Start to Target
            
            for(int i = 0; i < path.size(); i++) {
                cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
            }
            cout << "\nTotal Cost: " << g_score[target] << endl;
            return;
        }

        // Skip if we have already fully processed this node
        if(visit[current]) continue;
        visit[current] = 1;

        // Explore all neighbors of the current node
        for(int i = 0; i < adj[current].size(); i++) {
            int neighbor = adj[current][i].first;
            int weight = adj[current][i].second;

            if(visit[neighbor]) continue;

            // Calculate the exact cost to reach this neighbor
            int tentative_g_score = g_score[current] + weight;

            // If we found a cheaper path to this neighbor, update it
            if(tentative_g_score < g_score[neighbor]) {
                parent[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                
                // Calculate f(n) = g(n) + h(n) and add to priority queue
                int f_score = g_score[neighbor] + h[neighbor];
                pq.push({f_score, neighbor});
            }
        }
    }
    
    cout << "\nNo path found from " << start << " to " << target << endl;
}

int main() {
    int n, edges;
    
    cout << "Enter number of nodes: ";
    cin >> n;
    
    cout << "Enter number of edges: ";
    cin >> edges;
    
    // Adjacency list now stores pairs: {neighbor_node, edge_weight}
    vector<vector<pair<int, int>>> adj(n);

    cout << "Enter the edges (u v weight):\n";
    for(int i = 0; i < edges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;

        // Undirected graph with weights
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    // A* needs a heuristic (estimated distance to the target for each node)
    vector<int> h(n);
    cout << "\nEnter the heuristic values (estimated distance to target) for nodes 0 to " << n - 1 << ":\n";
    for(int i = 0; i < n; i++) {
        cout << "Node " << i << ": ";
        cin >> h[i];
    }

    int start, target;
    cout << "\nEnter the START node: ";
    cin >> start;
    cout << "Enter the TARGET node: ";
    cin >> target;

    // Run the A* algorithm
    astar(start, target, adj, h);

    return 0;
}