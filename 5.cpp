#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const double INF = 1e9;

// Structure to represent a weighted edge
struct Edge
{
    int to;
    double cost;
};

// Function to find the minimum cost path through multistage graph
pair<double, vector<int>> multistageOptimalPath(
    const vector<vector<vector<Edge>>> &stages)
{

    int N = stages.size();         // number of stages
    vector<vector<double>> dp(N);  // dp[i][j] = min cost to reach node j in stage i
    vector<vector<int>> parent(N); // parent[i][j] = node in stage i-1 giving min cost

    // Initialize DP for stage 0
    int stage0_size = stages[0].size();
    dp[0].resize(stage0_size, 0);
    parent[0].resize(stage0_size, -1);

    // Fill DP for subsequent stages
    for (int i = 1; i < N; i++)
    {
        int stage_size = stages[i].size();
        dp[i].resize(stage_size, INF);
        parent[i].resize(stage_size, -1);

        for (int j = 0; j < stage_size; j++)
        {
            // Check all edges coming from previous stage
            for (int k = 0; k < stages[i - 1].size(); k++)
            {
                for (auto &e : stages[i - 1][k])
                {
                    if (e.to == j)
                    {
                        double cost = dp[i - 1][k] + e.cost;
                        if (cost < dp[i][j])
                        {
                            dp[i][j] = cost;
                            parent[i][j] = k;
                        }
                    }
                }
            }
        }
    }

    // Find minimum cost in last stage
    double minCost = INF;
    int lastNode = -1;
    for (int i = 0; i < dp[N - 1].size(); i++)
    {
        if (dp[N - 1][i] < minCost)
        {
            minCost = dp[N - 1][i];
            lastNode = i;
        }
    }

    // Reconstruct path
    vector<int> path(N);
    int node = lastNode;
    for (int i = N - 1; i >= 0; i--)
    {
        path[i] = node;
        node = parent[i][node];
    }

    return {minCost, path};
}

int main()
{
    int stages_count;
    cout << "Enter number of stages: ";
    cin >> stages_count;

    vector<vector<vector<Edge>>> stages(stages_count);

    // Input number of nodes and edges for each stage
    for (int i = 0; i < stages_count; i++)
    {
        int nodes;
        cout << "Enter number of nodes in stage " << i + 1 << ": ";
        cin >> nodes;
        stages[i].resize(nodes);

        if (i == stages_count - 1)
            continue; // last stage has no outgoing edges

        for (int j = 0; j < nodes; j++)
        {
            int edges;
            cout << "Enter number of outgoing edges from node " << j
                 << " in stage " << i + 1 << ": ";
            cin >> edges;

            for (int k = 0; k < edges; k++)
            {
                int to;
                double cost;
                cout << "  Edge to node in next stage (0-based index) and cost: ";
                cin >> to >> cost;
                stages[i][j].push_back({to, cost});
            }
        }
    }

    // Compute optimal path
    auto result = multistageOptimalPath(stages);
    double minCost = result.first;
    vector<int> path = result.second;

    cout << "\nOptimal path through stages (0-based node indices): ";
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i] << " ";
    }
    cout << "\nMinimum cost: " << minCost << endl;

    return 0;
}


// //OUTPUT//=========================================
// PS C:\Users\ROHIT\OneDrive\Desktop\SM\DAA_Submissions\Assignment_5> cd "c:\Users\ROHIT\OneDrive\Desktop\SM\DAA_Submissions\Assignment_5\" ; if ($?) { g++ Assignment_5.cpp -o Assignment_5 } ; if ($?) { .\Assignment_5 }
// Enter number of stages: 3
// Enter number of nodes in stage 1: 2
// Enter number of outgoing edges from node 0 in stage 1: 2
//   Edge to node in next stage (0-based index) and cost: 0 3
//   Edge to node in next stage (0-based index) and cost: 1 2
// Enter number of outgoing edges from node 1 in stage 1: 1
//   Edge to node in next stage (0-based index) and cost: 0 3
// Enter number of nodes in stage 2: 2
// Enter number of outgoing edges from node 0 in stage 2: 1
//   Edge to node in next stage (0-based index) and cost: 0 2
// Enter number of outgoing edges from node 1 in stage 2: 1
//   Edge to node in next stage (0-based index) and cost: 1 1
// Enter number of nodes in stage 3: 2

// Optimal path through stages (0-based node indices): 0 1 1
// Minimum cost: 3


//=================================================
// //Method 2 : msk
// #include <iostream>
// #include <vector>
// using namespace std;

// const int INF = 1e9;

// int main() {

//     int stages = 3;
//     vector<int> nodesInStage = {2, 2, 2};

//     vector<vector<int>> stageNodes(stages);
//     int id = 0;
//     for (int i = 0; i < stages; i++) {
//         for (int j = 0; j < nodesInStage[i]; j++) {
//             stageNodes[i].push_back(id++);
//         }
//     }

//     int totalNodes = id;
//     vector<vector<int>> cost(totalNodes, vector<int>(totalNodes, INF));


//     // Stage 0 to Stage 1
//     cost[0][2] = 1;  // node 0 to node 2, cost 1
//     cost[0][3] = 3;  // node 0 to node 3, cost 3
//     cost[1][2] = 2;  // node 1 to node 2, cost 2
//     cost[1][3] = 4;  // node 1 to node 3, cost 4
    
//     // Stage 1 to Stage 2
//     cost[2][4] = 2;  // node 2 to node 4, cost 2
//     cost[2][5] = 1;  // node 2 to node 5, cost 1
//     cost[3][4] = 4;  // node 3 to node 4, cost 4
//     cost[3][5] = 5;  // node 3 to node 5, cost 5

//     vector<int> minCost(totalNodes, INF);
//     for (int u : stageNodes[0]) minCost[u] = 0;

//     vector<int> parent(totalNodes, -1);

//     for (int i = 1; i < stages; i++) {
//         for (int v : stageNodes[i]) {
//             for (int u : stageNodes[i-1]) {
//                 if (minCost[u] + cost[u][v] < minCost[v]) {
//                     minCost[v] = minCost[u] + cost[u][v];
//                     parent[v] = u;
//                 }
//             }
//         }
//     }

//     int bestNode = -1;
//     int bestCost = INF;
//     for (int v : stageNodes[stages-1]) {
//         if (minCost[v] < bestCost) {
//             bestCost = minCost[v];
//             bestNode = v;
//         }
//     }

//     // Reconstruct path
//     vector<int> path;
//     int cur = bestNode;
//     while (cur != -1) {
//         path.push_back(cur);
//         cur = parent[cur];
//     }
//     reverse(path.begin(), path.end());

//     cout << "\nOptimal path through stages: ";
//     for (int x : path) cout << x << " ";
//     cout << "\nMinimum total cost: " << bestCost << endl;

//     return 0;
// }
