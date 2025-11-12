#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    string name;
    double weight, value;
    bool divisible;
    int priority;

    double ratio() const { return value / weight; }
};

void fractionalKnapsack(vector<Item>& items, double capacity) {
    // Sort: Priority first (Ascending), then Value/Weight (Descending)
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        if (a.priority != b.priority) return a.priority < b.priority;
        return a.ratio() > b.ratio();
    });

    cout << "\n--- Sorted Items ---\n";
    // Changed header "Type" to "Divisible"
    printf("%-20s %-10s %-10s %-10s %-15s %-10s\n", "Item", "Weight", "Value", "Priority", "Val/Wgt", "Divisible");
    cout << string(80, '-') << endl;

    for (const auto& i : items) {
        // Changed output to Yes/No
        printf("%-20s %-10.1f %-10.1f %-10d %-15.2f %-10s\n", 
            i.name.c_str(), i.weight, i.value, i.priority, i.ratio(), (i.divisible ? "Yes" : "No"));
    }

    double totalValue = 0, totalWeight = 0;
    cout << "\n--- Transport Summary ---\n";

    for (const auto& i : items) {
        if (capacity <= 0) break;
        
        double take = i.divisible ? min(i.weight, capacity) : (i.weight <= capacity ? i.weight : 0);
        
        if (take == 0 && !i.divisible) { 
             printf(" - Divisible: No  | %s (Skipped: Too Heavy)\n", i.name.c_str());
             continue;
        }

        double val = take * i.ratio();
        totalValue += val;
        totalWeight += take;
        capacity -= take;

        printf(" - Divisible: %-3s | %-15s | Taken: %5.1f kg | Utility: %6.2f\n", 
            (i.divisible ? "Yes" : "No"), i.name.c_str(), take, val);
    }

    cout << "\nFINAL TOTALS\n";
    cout << "Total Weight: " << totalWeight << " kg | Remaining Cap: " << max(0.0, capacity) << " kg | Total Value: " << totalValue << "\n";
}

int main() {
    vector<Item> items = {
        {"Infant Formula", 5, 50, false, 1},
        {"Medical Kits", 10, 100, false, 1},
        {"Drinking Water", 30, 90, true, 2},
        {"Water Filters", 2, 8, false, 2},
        {"Blankets", 15, 45, false, 3},
        {"Food Packets", 20, 60, true, 3}
    };

    double capacity;
    cout << "Emergency Relief Boat Loading System\nCapacity (kg): ";
    cin >> capacity;

    if(capacity > 0) fractionalKnapsack(items, capacity);
    return 0;
}