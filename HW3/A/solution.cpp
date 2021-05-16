#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream cin("input.txt");
    std::ofstream cout("output.txt");
    size_t n, S;
    cin >> n;
    std::vector<uint32_t> items(n); 
    for (size_t i = 0; i < n; ++i) {
        cin >> items[i];
    }
    cin >> S; 
    if (n == 0) {
        cout << "0\n";
        cin.close();
        cout.close();
        return 0;
    }
    std::sort(items.begin(), items.end(), std::greater<>());
    std::vector<uint32_t> containers(1);
    containers[0] = 0;
    for (size_t i = 0; i < n; ++i) {
        if (i == 0) {
            containers[0] += items[i];
        } else {
            bool flag = false;
            for (size_t j = 0; j < containers.size(); ++j) {
                if (S - containers[j] >= items[i]) {
                    containers[j] += items[i];
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                containers.push_back(items[i]);
            }
        }
    }
    cout << containers.size() << '\n';
    cin.close();
    cout.close();
    return 0;
}