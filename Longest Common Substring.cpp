#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Define a structure to hold the cell information
struct Cell {
    int length;
    string direction;
};

string longest_common_substring(const string& str1, const string& str2, vector<vector<Cell>>& dp) {
    int n = str1.length(), m = str2.length();
    dp.assign(n + 1, vector<Cell>(m + 1, {0, ""}));
    int length = 0;  // Length of longest common substring
    int row, col;    // To store the end point of the longest common substring in str1

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = {0, "None"};
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j].length = dp[i - 1][j - 1].length + 1;
                dp[i][j].direction = "Diag";
                if (length < dp[i][j].length) {
                    length = dp[i][j].length;
                    row = i;
                    col = j;
                }
            } else {
                dp[i][j] = {0, "Reset"};
            }
        }
    }

    if (length == 0) {
        return "";
    }

    string result;
    while (dp[row][col].length != 0) {
        result = str1[row - 1] + result;
        --row;
        --col;
    }

    return result;
}

void print_table(const vector<vector<Cell>>& dp) {
    for (int i = 0; i < dp.size(); i++) {
        for (int j = 0; j < dp[0].size(); j++) {
            cout << dp[i][j].length << dp[i][j].direction[0] << " ";
        }
        cout << "\n";
    }
}

int main() {
    string str1 = "ABAB";
    string str2 = "BABA";
    vector<vector<Cell>> dp;

    string lcs = longest_common_substring(str1, str2, dp);
    cout << "Longest Common Substring: " << lcs << endl;
    cout << "\nDirectional Lookup Table:\n";
    print_table(dp);

    return 0;
}
