//Branch and Bound
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;


struct Node {
    vector<int> path; 
    vector<vector<int>> reducedMatrix;
    int cost;
    int vertex; 
    int level; 
};

int reduceMatrix(vector<vector<int>>& mat) {
    int reduction = 0;
    int n = mat.size();

    // Row reduction
    for (int i = 0; i < n; i++) {
        int rowMin = INF;
        for (int j = 0; j < n; j++)
            rowMin = min(rowMin, mat[i][j]);

        if (rowMin != INF && rowMin != 0) {
            reduction += rowMin;
            for (int j = 0; j < n; j++)
                if (mat[i][j] != INF) mat[i][j] -= rowMin;
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int colMin = INF;
        for (int i = 0; i < n; i++)
            colMin = min(colMin, mat[i][j]);

        if (colMin != INF && colMin != 0) {
            reduction += colMin;
            for (int i = 0; i < n; i++)
                if (mat[i][j] != INF) mat[i][j] -= colMin;
        }
    }

    return reduction;
}


Node* newNode(vector<vector<int>> parentMatrix, vector<int> const &path, int level, int i, int j) {
    int n = parentMatrix.size();
    Node* node = new Node;
    node->path = path;
    node->level = level;
    node->reducedMatrix = parentMatrix;


    for (int k = 0; k < n; k++) {
        node->reducedMatrix[i][k] = INF;
        node->reducedMatrix[k][j] = INF;
    }
    node->reducedMatrix[j][0] = INF; // prevent returning to start too early

    return node;
}


struct CompareCost {
    bool operator()(const Node* a, const Node* b) const {
        return a->cost > b->cost;
    }
};

// LC Branch and Bound algorithm for TSP
int tspLC(vector<vector<int>> costMatrix) {
    int n = costMatrix.size();
    priority_queue<Node*, vector<Node*>, CompareCost> pq;

    vector<int> path = {0};
    Node* root = new Node;
    root->path = path;
    root->reducedMatrix = costMatrix;
    root->level = 0;
    root->vertex = 0;
    root->cost = reduceMatrix(root->reducedMatrix);

    pq.push(root);
    int minCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();

        int i = minNode->vertex;

        if (minNode->level == n - 1) {
            int lastToFirst = costMatrix[i][0];
            if (lastToFirst != INF && minNode->cost + lastToFirst < minCost) {
                minCost = minNode->cost + lastToFirst;
                bestPath = minNode->path;
                bestPath.push_back(0);
            }
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (minNode->reducedMatrix[i][j] != INF) {
                vector<int> newPath = minNode->path;
                newPath.push_back(j);

                Node* child = newNode(minNode->reducedMatrix, newPath, minNode->level + 1, i, j);
                int cost = minNode->cost + minNode->reducedMatrix[i][j];
                cost += reduceMatrix(child->reducedMatrix);
                child->cost = cost;
                child->vertex = j;

                pq.push(child);
            }
        }
        delete minNode;
    }

    cout << "\nOptimal Route: ";
    for (int city : bestPath) cout << city << " ";
    cout << "\nMinimum Cost: " << minCost << "\n";
    return minCost;
}

// Example usage
int main() {
    // Example cost matrix (0 means same city)
    vector<vector<int>> costMatrix = {
        {INF, 10, 15, 20},
        {10, INF, 35, 25},
        {15, 35, INF, 30},
        {20, 25, 30, INF}
    };

    tspLC(costMatrix);
    return 0;
}