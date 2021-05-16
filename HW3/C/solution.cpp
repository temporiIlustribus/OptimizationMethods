#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

// Based on:
// https://neerc.ifmo.ru/wiki/index.php?title=Задача_о_рюкзаке

auto restore_weight(std::vector<std::vector<uint32_t>>& maxCost,
                        std::vector<std::pair<uint32_t, uint32_t>>& items, 
                        uint32_t k, uint32_t s) {
    if (maxCost[1][s] == 0) {
        return 0U;
    }
    if (maxCost[0][s] == maxCost[1][s]) {
        return restore_weight(maxCost, items, k - 1, s);
    }
    return items[k].first + restore_weight(maxCost, items, k - 1, s - items[k].first);
}

int main() {
    std::ifstream cin("input.txt");
    std::ofstream cout("output.txt");
    size_t N, W;
    cin >> N;
    uint32_t input;
    std::vector<std::pair<uint32_t, uint32_t>> items(N); 
    for (size_t i = 0; i < N; ++i) {
        cin >> input;
        items[i] = std::make_pair(input, 0U);
    }
    for (size_t i = 0; i < N; ++i) {
        cin >> input;
        items[i] = std::make_pair(items[i].first, input);
    }
    cin >> W; 
    if (N == 0) {
        cout << "0 0\n";
        cin.close();
        cout.close();
        return 0;
    }
    
    // Solve using Dynamic Programming
    std::vector<std::vector<uint32_t>> maxCost(2, std::vector<uint32_t>(W+1, 0));
    std::vector<std::vector<uint32_t>> weights(2, std::vector<uint32_t>(W+1, 0));
    for (size_t k = 0; k < N; ++k) {
        maxCost[0] = maxCost[1];
        weights[0] = weights[1];
        for (size_t s = 1; s <= W; ++s) {
            if (s >= items[k].first && maxCost[0][s] < maxCost[0][s - items[k].first] + items[k].second) {
                maxCost[1][s] = maxCost[0][s - items[k].first] + items[k].second;
                weights[1][s] = weights[0][s - items[k].first] + items[k].first;
            } else {
                maxCost[1][s] = maxCost[0][s];
                weights[1][s] = weights[0][s];
            }
        }
    }
    cout << weights[1][W] << ' ' << maxCost[1][W] << '\n';
    cin.close();
    cout.close();
    return 0;
}