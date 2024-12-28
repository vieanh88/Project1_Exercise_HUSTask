/* Để tối ưu hơn nữa cho việc xử lý các truy vấn trên dữ liệu lớn hơn, chúng ta có thể áp dụng các kỹ thuật như sau:

1.  Chuyển đổi từ map sang cấu trúc dữ liệu khác với độ phức tạp tốt hơn cho truy vấn tổng doanh thu trong khoảng thời gian:
    Chúng ta có thể sử dụng Segment Tree hoặc Fenwick Tree (Binary Indexed Tree) để lưu tổng doanh thu tại mỗi thời điểm và thực hiện truy vấn theo khoảng nhanh chóng hơn.

2.  Chuẩn bị dữ liệu trước (Preprocessing) cho từng truy vấn:
    Với các truy vấn tổng doanh thu trong một khoảng thời gian (?total_revenue_in_period),
    chúng ta có thể sử dụng kỹ thuật prefix sum (tổng tích lũy) để tính toán doanh thu đến từng thời điểm.
    Sau đó, ta có thể lấy tổng doanh thu giữa hai thời điểm bất kỳ với độ phức tạp O(1) sau khi tính trước mảng prefix sum.
3.  Giảm thiểu bộ nhớ bằng cách nén thời gian (Time Compression):
    Để giảm bộ nhớ của revenueByTime, chúng ta chỉ lưu các mốc thời gian xuất hiện trong dữ liệu bằng cách ánh xạ thời gian về các chỉ số liên tiếp.
    Điều này sẽ làm giảm không gian lưu trữ và giúp truy vấn trên mảng prefix sum dễ dàng hơn.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <algorithm>
#include <climits> // Thêm thư viện này để sử dụng INT_MAX

using namespace std;

struct Order {
    string customerID;
    string productID;
    int price;
    string shopID;
    int timePoint; // Chuyển đổi thời gian sang giây từ trước
};

// Hàm chuyển đổi thời gian từ định dạng HH:MM:SS sang số giây để dễ so sánh
int timeToSeconds(const string &time) {
    int h = stoi(time.substr(0, 2));
    int m = stoi(time.substr(3, 2));
    int s = stoi(time.substr(6, 2));
    return h * 3600 + m * 60 + s;
}

int main() {
    vector<Order> orders; // Danh sách các đơn hàng
    unordered_map<string, int> shopRevenue; // Tổng doanh thu của từng cửa hàng
    unordered_map<string, unordered_map<string, int>> customerShopRevenue; // Doanh thu của khách hàng tại từng cửa hàng
    map<int, int> revenueByTime; // Doanh thu tại mỗi thời điểm (dưới dạng giây)

    int totalRevenue = 0;
    int totalOrders = 0;
    string line;

    // Đọc dữ liệu đơn hàng
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        Order order;
        string timePoint;
        ss >> order.customerID >> order.productID >> order.price >> order.shopID >> timePoint;

        order.timePoint = timeToSeconds(timePoint); // Chuyển thời gian sang giây

        orders.push_back(order);
        totalRevenue += order.price;
        totalOrders++;
        shopRevenue[order.shopID] += order.price;
        customerShopRevenue[order.customerID][order.shopID] += order.price;
        revenueByTime[order.timePoint] += order.price;
    }

    // Chuẩn bị prefix sum cho doanh thu theo thời gian
    vector<pair<int, int>> compressedRevenue; // {time, cumulative revenue}
    int cumulativeRevenue = 0;

    for (auto &[time, revenue] : revenueByTime) {
        cumulativeRevenue += revenue;
        compressedRevenue.emplace_back(time, cumulativeRevenue);
    }

    // Hàm tìm tổng doanh thu trong khoảng thời gian bằng binary search trên prefix sum
    auto getRevenueInPeriod = [&](int start, int end) {
        // Tìm giới hạn dưới và trên bằng binary search
        auto itStart = lower_bound(compressedRevenue.begin(), compressedRevenue.end(), make_pair(start, 0));
        auto itEnd = upper_bound(compressedRevenue.begin(), compressedRevenue.end(), make_pair(end, INT_MAX));

        if (itStart == compressedRevenue.end() || itEnd == compressedRevenue.begin()) return 0;
        itEnd--;

        int startRevenue = (itStart == compressedRevenue.begin()) ? 0 : (itStart - 1)->second;
        return itEnd->second - startRevenue;
    };

    // Đọc các truy vấn
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string query;
        ss >> query;

        if (query == "?total_number_orders") {
            cout << totalOrders << endl;
        }
        else if (query == "?total_revenue") {
            cout << totalRevenue << endl;
        }
        else if (query == "?revenue_of_shop") {
            string shopID;
            ss >> shopID;
            cout << shopRevenue[shopID] << endl;
        }
        else if (query == "?total_consume_of_customer_shop") {
            string customerID, shopID;
            ss >> customerID >> shopID;
            cout << customerShopRevenue[customerID][shopID] << endl;
        }
        else if (query == "?total_revenue_in_period") {
            string fromTime, toTime;
            ss >> fromTime >> toTime;
            int start = timeToSeconds(fromTime);
            int end = timeToSeconds(toTime);

            cout << getRevenueInPeriod(start, end) << endl;
        }
    }

    return 0;
}
