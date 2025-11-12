#include <bits/stdc++.h>
using namespace std;

void greedyColoring(vector<vector<int>> &graph, int numCourses) {
    vector<int> result(numCourses, -1);
    result[0] = 0;

    vector<bool> available(numCourses, true);

    for (int u = 1; u < numCourses; u++) {
        fill(available.begin(), available.end(), true);

        for (int adj : graph[u]) {
            if (result[adj] != -1)
                available[result[adj]] = false;
        }

        int color;
        for (color = 0; color < numCourses; color++) {
            if (available[color])
                break;
        }
        result[u] = color;
    }

    cout << "Exam Slot Assignment (Greedy Coloring):\n";
    for (int u = 0; u < numCourses; u++) {
        cout << "Course " << u << " --> Slot " << result[u] << endl;
    }

    int maxColor = *max_element(result.begin(), result.end());
    cout << "\nTotal Exam Slots Used: " << (maxColor + 1) << endl;
}

int main() {
    int numCourses, edges;

    cout << "Enter number of courses: ";
    cin >> numCourses;

    cout << "Enter number of edges (conflicts): ";
    cin >> edges;

    vector<vector<int>> graph(numCourses);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    greedyColoring(graph, numCourses);
    return 0;
}


// OUTPUT:

// Enter number of courses: 5
// Enter number of edges (conflicts): 6
// Enter edges (u v):
// 0 1
// 0 2
// 1 2
// 1 3
// 2 4
// 3 4

// Exam Slot Assignment (Greedy Coloring):
// Course 0 → Slot 0
// Course 1 → Slot 1
// Course 2 → Slot 2
// Course 3 → Slot 0
// Course 4 → Slot 1

// Total Exam Slots Used: 3


//=============================================================
// //method2 : msk

// #include <iostream>
// #include <vector>
// #include <algorithm>
// using namespace std;

// void greedyColoring(vector<vector<int>>& graph, int V) {
//     vector<int> result(V, -1);
//     vector<bool> available(V, false);


//     result[0] = 0;


//     for (int u = 1; u < V; u++) {
//         fill(available.begin(), available.end(), false);
//         for (int i = 0; i < V; i++) {
//             if (graph[u][i] && result[i] != -1)
//                 available[result[i]] = true;
//         }

//         int cr;
//         for (cr = 0; cr < V; cr++) {
//             if (!available[cr])
//                 break;
//         }

//         result[u] = cr;
//     }


//     cout << "\nExam Schedule (Course : Time Slot)\n";
//     cout << "----------------------------------\n";
//     for (int u = 0; u < V; u++)
//         cout << "Course " << u + 1 << " --> Slot " << result[u] + 1 << endl;

//     int totalSlots = *max_element(result.begin(), result.end()) + 1;
//     cout << "\nMinimum number of time slots required: " << totalSlots << endl;
// }

// int main() {

//     int V = 6;
//     int E = 8;

//     vector<vector<int>> graph(V, vector<int>(V, 0));


//     vector<pair<int, int>> edges = {
//         {1, 2}, {1, 3}, {2, 4}, {3, 4}, 
//         {4, 5}, {5, 6}, {2, 6}, {3, 6}
//     };

//     for (auto& edge : edges) {
//         int u = edge.first - 1;  
//         int v = edge.second - 1;
//         graph[u][v] = 1;
//         graph[v][u] = 1;
//     }

//     greedyColoring(graph, V);

//     return 0;
// }