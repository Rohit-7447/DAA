//Disaster Relief Resource
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int utility;
};

int knapsack(const vector<Item>& items, int W, vector<int>& selectedItems) {
    int N = items.size();
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (items[i - 1].weight <= w) {
                int includeItem = dp[i - 1][w - items[i - 1].weight] + items[i - 1].utility;
                dp[i][w] = max(includeItem, dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int remainingWeight = W;
    for (int i = N; i > 0; --i) {
        if (dp[i][remainingWeight] != dp[i - 1][remainingWeight]) {
            selectedItems.push_back(i - 1);
            remainingWeight -= items[i - 1].weight;
        }
    }

    return dp[N][W];
}

int main() {
    int N, W;
    cout << "Enter the number of items: ";
    cin >> N;

    cout << "Enter the truck capacity: ";
    cin >> W;

    vector<Item> items(N);

    cout << "Enter the weight and utility of each item:\n";
    for (int i = 0; i < N; ++i) {
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> items[i].weight;
        cout << "Item " << i + 1 << " - Utility: ";
        cin >> items[i].utility;
    }

    vector<int> selectedItems;
    int maxUtility = knapsack(items, W, selectedItems);

    cout << "\nMaximum utility that can be carried: " << maxUtility << endl;
    cout << "Items chosen:\n";

    for (int i : selectedItems) {
        cout << "Item " << i + 1
             << " - Weight: " << items[i].weight
             << " Utility: " << items[i].utility << endl;
    }

    return 0;
}


//OUTPUT=================================
// Enter the number of items: 4
// Enter the truck capacity: 7
// Enter the weight and utility of each item:
// Item 1 - Weight: 1
// Item 1 - Utility: 1
// Item 2 - Weight: 3
// Item 2 - Utility: 4
// Item 3 - Weight: 4
// Item 3 - Utility: 5
// Item 4 - Weight: 5
// Item 4 - Utility: 7

// Maximum utility that can be carried: 9
// Items chosen:
// Item 3 - Weight: 4 Utility: 5
// Item 2 - Weight: 3 Utility: 4

// //method 2: r7447
// // Emergency Relief Supplies system using 0/1 Knapsack 
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <map>
// #include <iomanip>

// using namespace std;

// void getMaxUtility(const vector<int>& itemWeight, const vector<int>& itemUtility, int maxTruckCapacity, int totalItems) {
//     vector<int> dp(maxTruckCapacity + 1, 0);
//     vector<vector<int>> selectedTrack(totalItems, vector<int>(maxTruckCapacity + 1, 0));

//     for (int i = 0; i < totalItems; ++i) {
//         int w_i = itemWeight[i];
//         int u_i = itemUtility[i];
        
//         for (int currentCapacity = maxTruckCapacity; currentCapacity >= w_i; --currentCapacity) {
//             if (dp[currentCapacity] < dp[currentCapacity - w_i] + u_i) {
//                 dp[currentCapacity] = dp[currentCapacity - w_i] + u_i;
//                 selectedTrack[i][currentCapacity] = 1;
//             }
//         }
//     }

//     int maxUtility = dp[maxTruckCapacity];
//     cout << "\n=======================================================\n";
//     cout << "  Maximum Utility (Optimal Relief Load): " << maxUtility << endl;
//     cout << "=======================================================\n";

//     vector<int> selectedItems(totalItems, 0);
//     int remainingCapacity = maxTruckCapacity;
//     int totalSelectedWeight = 0;

//     for (int i = totalItems - 1; i >= 0; --i) {
//         if (selectedTrack[i][remainingCapacity] == 1) {
//             selectedItems[i] = 1;
//             remainingCapacity -= itemWeight[i];
//             totalSelectedWeight += itemWeight[i];
//         }
//     }

//     cout << "\nSelected Items:\n";
//     cout << left << setw(8) << "Item" << setw(10) << "Weight" << setw(10) << "Utility" << "Included (1/0)\n";
//     cout << string(45, '-') << endl;
//     for (int i = 0; i < totalItems; ++i) {
//         cout << left << setw(8) << (i + 1)
//              << setw(10) << itemWeight[i]
//              << setw(10) << itemUtility[i]
//              << selectedItems[i] << endl;
//     }
    
//     cout << "\nTotal Selected Weight: " << totalSelectedWeight << " kg (Max Capacity: " << maxTruckCapacity << " kg)\n";
// }

// // --- Main Program ---
// int main() {
//     int totalItems;
//     cout << "Enter total number of essential items (N): ";
//     if (!(cin >> totalItems) || totalItems <= 0) {
//         return 1;
//     }

//     int maxTruckCapacity;
//     cout << "Enter maximum truck capacity (W in kg): ";
//     if (!(cin >> maxTruckCapacity) || maxTruckCapacity <= 0) {
//         return 1;
//     }

//     vector<int> itemWeight(totalItems);
//     vector<int> itemUtility(totalItems);

//     cout << "\nEnter details for each item (weight in kg and utility value):\n";
//     for (int i = 0; i < totalItems; ++i) {
//         cout << "Item " << (i + 1) << " weight (kg): ";
//         if (!(cin >> itemWeight[i]) || itemWeight[i] < 0) {
//             return 1;
//         }
//         cout << "Item " << (i + 1) << " utility value: ";
//         if (!(cin >> itemUtility[i]) || itemUtility[i] < 0) {
//             return 1;
//         }
//     }

//     getMaxUtility(itemWeight, itemUtility, maxTruckCapacity, totalItems);

//     return 0;
// }