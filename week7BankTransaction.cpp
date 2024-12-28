#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

// Cấu trúc dữ liệu để lưu thông tin của một giao dịch
struct Transaction {
    string from_account;
    string to_account;
    int money;
};

// Các biến toàn cục lưu thông tin giao dịch và các tổng
vector<Transaction> transactions; // Danh sách các giao dịch
unordered_map<string, int> total_money_from_account; // Tổng tiền chuyển từ mỗi tài khoản
unordered_set<string> all_accounts; // Danh sách tất cả các tài khoản đã xuất hiện
unordered_map<string, vector<string>> adj_list; // Danh sách kề của đồ thị giao dịch (biểu diễn các tài khoản giao dịch với nhau)

// Đọc giao dịch và lưu vào các cấu trúc dữ liệu
void readTransactions() {
    string line;
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string from_account, to_account, time_point, atm;
        int money;
        ss >> from_account >> to_account >> money >> time_point >> atm;

        // Lưu thông tin giao dịch
        transactions.push_back({from_account, to_account, money});

        // Tăng tổng tiền từ tài khoản from_account
        total_money_from_account[from_account] += money;

        // Thêm các tài khoản vào danh sách tất cả tài khoản
        all_accounts.insert(from_account);
        all_accounts.insert(to_account);

        // Thêm cạnh vào danh sách kề
        adj_list[from_account].push_back(to_account);
    }
}

// Kiểm tra xem có chu kỳ độ dài k bắt đầu từ tài khoản start không
bool hasCycleOfLengthK(const string& start, int k) {
    queue<vector<string>> q;
    q.push({start}); // Bắt đầu từ tài khoản start

    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();

        // Nếu độ dài đường đi đạt đúng k và quay lại tài khoản ban đầu
        if (path.size() == k + 1 && path.back() == start) return true;

        // Nếu độ dài đường đi chưa đạt k + 1, tiếp tục tìm tài khoản tiếp theo
        if (path.size() <= k) {
            string last_account = path.back();
            for (const string& neighbor : adj_list[last_account]) {
                // Đảm bảo rằng tài khoản này chưa có trong đường đi hiện tại (để không lặp lại)
                if (find(path.begin(), path.end(), neighbor) == path.end() || (static_cast<int>(path.size()) == k && neighbor == start)) {
                    vector<string> new_path = path;
                    new_path.push_back(neighbor);
                    q.push(new_path);
                }
            }
        }
    }
    return false;
}

int main() {
    readTransactions(); // Đọc dữ liệu giao dịch

    string line;
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string query;
        ss >> query;

        if (query == "?number_transactions") {
            // Tổng số giao dịch
            cout << transactions.size() << endl;
        } 
        else if (query == "?total_money_transaction") {
            // Tổng số tiền trong tất cả giao dịch
            int total_money = 0;
            for (const auto& transaction : transactions) {
                total_money += transaction.money;
            }
            cout << total_money << endl;
        } 
        else if (query == "?list_sorted_accounts") {
            // Liệt kê danh sách tài khoản đã xuất hiện, sắp xếp tăng dần
            vector<string> sorted_accounts(all_accounts.begin(), all_accounts.end());
            sort(sorted_accounts.begin(), sorted_accounts.end());
            for (const string& account : sorted_accounts) {
                cout << account << " ";
            }
            cout << endl;
        } 
        else if (query == "?total_money_transaction_from") {
            // Tính tổng tiền chuyển từ một tài khoản cụ thể
            string account;
            ss >> account;
            cout << total_money_from_account[account] << endl;
        } 
        else if (query == "?inspect_cycle") {
            // Kiểm tra chu kỳ giao dịch độ dài k từ một tài khoản cụ thể
            string account;
            int k;
            ss >> account >> k;
            cout << (hasCycleOfLengthK(account, k) ? 1 : 0) << endl;
        }
    }

    return 0;
}
