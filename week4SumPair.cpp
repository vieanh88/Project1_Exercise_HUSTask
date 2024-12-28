#include <iostream>
#include <algorithm> // Để dùng hàm sort
using namespace std;

int main() {
    int n, M;
    cin >> n >> M;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Sắp xếp mảng
    sort(arr, arr + n);

    int left = 0;       // Con trỏ trái
    int right = n - 1;  // Con trỏ phải
    int count = 0;      // Biến đếm số cặp hợp lệ

    // Dùng hai con trỏ để tìm các cặp có tổng bằng M
    while (left < right) {
        int sum = arr[left] + arr[right]; // Tính tổng của hai phần tử
        
        if (sum == M) {
            count++;     // Nếu tổng bằng M, tìm được một cặp và tăng giá trị count
            left++;      // Dịch con trỏ trái sang phải
            right--;     // Dịch con trỏ phải sang trái
        } else if (sum < M) {
            left++;      // Nếu tổng < M, cần tăng tổng => dịch con trỏ trái sang phải
        } else {
            right--;     // Nếu tổng > M, cần giảm tổng => dịch con trỏ phải sang trái
        }
    }

    //In kết quá
    cout << count << endl;

    return 0;
}
