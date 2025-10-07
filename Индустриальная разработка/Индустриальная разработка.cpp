#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

vector<vector<int>> parse_triangle(const string& input) {
    vector<vector<int>> triangle;
    size_t pos = input.find('[');
    if (pos == string::npos) return triangle;
    
    string s = input.substr(pos);
    vector<int> current_row;
    int num = 0;
    bool in_number = false;
    bool negative = false;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '-') {
            negative = true;
        } else if (isdigit(c)) {
            if (!in_number) {
                num = 0;
                in_number = true;
            }
            num = num * 10 + (c - '0');
        } else {
            if (in_number) {
                current_row.push_back(negative ? -num : num);
                in_number = false;
                negative = false;
            }
            if (c == ']') {
                if (!current_row.empty()) {
                    triangle.push_back(current_row);
                    current_row.clear();
                }
            }
        }   
    }
    return triangle;
}

int main() {
    string input, line;
    int open_br = 0, close_br = 0;
    bool seen_bracket = false;
    while (getline(cin, line)) {
        if (!seen_bracket && line.find_first_not_of(" \t\r\n") == string::npos) continue;
        for (char c : line) {
            if (c == '[') { ++open_br; seen_bracket = true; }
            else if (c == ']') ++close_br;
        }
        input += line;
        if (seen_bracket && open_br > 0 && open_br == close_br) break;
    }

    vector<vector<int>> triangle = parse_triangle(input);
    int n = static_cast<int>(triangle.size());
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> dp = triangle.back();
    for (int row = n - 2; row >= 0; --row) {
        for (int j = 0; j <= row; ++j) {
            dp[j] = triangle[row][j] + min(dp[j], dp[j + 1]);
        }
    }
    cout << dp[0] << endl;
    return 0;
}
