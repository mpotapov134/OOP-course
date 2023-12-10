#include <string>
#include <iostream>

bool IsInteger(std::string str) {
    int pos_in_str = 0;
    for (const auto& ch : str) {
        if (!std::isdigit(ch)) {
            if (!((ch == '-' || ch == '+') && pos_in_str == 0)) {
                return false;
            }
        }
        pos_in_str++;
    }
    return true;
}

int main() {
    std::string s = "10-";
    std::cout << IsInteger(s) << "\n";
}
