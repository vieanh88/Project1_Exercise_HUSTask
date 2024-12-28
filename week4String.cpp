#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main() {
    unordered_set<string> database; // Tập hợp để lưu các khóa
    string input;

    // Đọc khối đầu tiên cho đến khi gặp dấu *
    while (true) {
        getline(cin, input);
        if (input == "*") break; // Dừng lại khi gặp *
        database.insert(input); // Thêm các khóa vào cơ sở dữ liệu
    }

    // Đọc và xử lý các lệnh trong khối thứ hai cho đến khi gặp ***
    while (true) {
        getline(cin, input);
        if (input == "***") break; // Dừng lại khi gặp ***
        
        // Tách lệnh và khóa
        string command = input.substr(0, input.find(' '));
        string key = input.substr(input.find(' ') + 1);

        if (command == "find") {
            // Kiểm tra xem khóa có trong tập hợp hay không
            if (database.find(key) != database.end()) {
                cout << "1" << endl; // Nếu có, in 1
            } else {
                cout << "0" << endl; // Nếu không, in 0
            }
        } else if (command == "insert") {
            // Kiểm tra và thêm khóa vào tập hợp
            if (database.find(key) != database.end()) {
                cout << "0" << endl; // Nếu đã tồn tại, in 0
            } else {
                database.insert(key); // Nếu chưa tồn tại, thêm vào và in 1
                cout << "1" << endl;
            }
        }
    }

    return 0;
}
