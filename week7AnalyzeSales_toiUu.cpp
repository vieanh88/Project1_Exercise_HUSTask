#include <iostream> // Thư viện nhập xuất
#include <string> // Thư viện xử lý chuỗi
#include <vector> // Thư viện vector để lưu trữ danh sách các đơn hàng
#include <unordered_map> // Thư viện unordered_map để lưu bảng băm
#include <map> // Thư viện map để lưu trữ dữ liệu theo thứ tự
#include <sstream> // Thư viện stringstream để tách chuỗi

using namespace std;

// Cấu trúc để lưu thông tin của một đơn hàng
struct Order {
    string customerID; // Mã khách hàng
    string productID; // Mã sản phẩm
    int price; // Giá của sản phẩm
    string shopID; // Mã cửa hàng
    string timePoint; // Thời điểm mua hàng dưới dạng HH:MM:SS
};

// Hàm chuyển đổi thời gian từ định dạng HH:MM:SS sang số giây để dễ so sánh
int timeToSeconds(const string &time) {
    int h = stoi(time.substr(0, 2)); // Lấy giờ (2 ký tự đầu tiên) và chuyển sang số nguyên
    int m = stoi(time.substr(3, 2)); // Lấy phút (2 ký tự sau giờ) và chuyển sang số nguyên
    int s = stoi(time.substr(6, 2)); // Lấy giây (2 ký tự cuối) và chuyển sang số nguyên
    return h * 3600 + m * 60 + s; // Chuyển đổi giờ, phút, giây thành tổng số giây
}

int main() {
    vector<Order> orders; // Danh sách lưu trữ tất cả các đơn hàng
    unordered_map<string, int> shopRevenue; // Bảng băm lưu doanh thu của mỗi cửa hàng
    unordered_map<string, unordered_map<string, int>> customerShopRevenue; // Bảng băm lưu doanh thu của mỗi khách hàng tại từng cửa hàng
    map<int, int> revenueByTime; // Map để lưu doanh thu dựa theo thời gian (thời gian là key, doanh thu là value)

    int totalRevenue = 0; // Biến lưu tổng doanh thu của toàn công ty
    int totalOrders = 0; // Biến lưu tổng số đơn hàng

    string line; // Chuỗi để lưu từng dòng dữ liệu đầu vào

    // Đọc dữ liệu đơn hàng từ đầu vào
    while (getline(cin, line) && line != "#") { // Đọc từng dòng cho đến khi gặp ký tự '#'
        stringstream ss(line); // Tạo stringstream từ dòng để tách dữ liệu
        Order order; // Tạo một biến kiểu Order để lưu thông tin đơn hàng
        ss >> order.customerID >> order.productID >> order.price >> order.shopID >> order.timePoint; // Đọc thông tin từng trường của đơn hàng từ dòng

        // Cập nhật dữ liệu cho các đơn hàng
        orders.push_back(order); // Thêm đơn hàng vào danh sách orders
        totalRevenue += order.price; // Cộng giá của đơn hàng vào tổng doanh thu
        totalOrders++; // Tăng số lượng đơn hàng thêm 1
        shopRevenue[order.shopID] += order.price; // Cộng giá của đơn hàng vào doanh thu của cửa hàng tương ứng
        customerShopRevenue[order.customerID][order.shopID] += order.price; // Cộng giá của đơn hàng vào doanh thu của khách hàng tại cửa hàng tương ứng

        int orderTime = timeToSeconds(order.timePoint); // Chuyển thời gian của đơn hàng sang giây
        revenueByTime[orderTime] += order.price; // Cập nhật doanh thu theo thời gian vào map `revenueByTime`
    }

    // Đọc các truy vấn từ đầu vào
    while (getline(cin, line) && line != "#") { // Đọc từng dòng truy vấn cho đến khi gặp ký tự '#'
        stringstream ss(line); // Tạo stringstream từ dòng truy vấn để tách các phần tử
        string query; // Biến lưu loại truy vấn
        ss >> query; // Đọc loại truy vấn từ dòng

        if (query == "?total_number_orders") {
            // Truy vấn số lượng đơn hàng
            cout << totalOrders << endl; // In ra tổng số đơn hàng
        }
        else if (query == "?total_revenue") {
            // Truy vấn tổng doanh thu của công ty
            cout << totalRevenue << endl; // In ra tổng doanh thu
        }
        else if (query == "?revenue_of_shop") {
            // Truy vấn doanh thu của một cửa hàng cụ thể
            string shopID; // Biến lưu mã cửa hàng
            ss >> shopID; // Đọc mã cửa hàng từ truy vấn
            cout << shopRevenue[shopID] << endl; // In ra doanh thu của cửa hàng được yêu cầu
        }
        else if (query == "?total_consume_of_customer_shop") {
            // Truy vấn doanh thu từ một khách hàng tại một cửa hàng cụ thể
            string customerID, shopID; // Biến lưu mã khách hàng và mã cửa hàng
            ss >> customerID >> shopID; // Đọc mã khách hàng và mã cửa hàng từ truy vấn
            cout << customerShopRevenue[customerID][shopID] << endl; // In ra doanh thu của khách hàng tại cửa hàng đó
        }
        else if (query == "?total_revenue_in_period") {
            // Truy vấn tổng doanh thu trong một khoảng thời gian
            string fromTime, toTime; // Biến lưu thời gian bắt đầu và thời gian kết thúc
            ss >> fromTime >> toTime; // Đọc thời gian bắt đầu và kết thúc từ truy vấn
            int start = timeToSeconds(fromTime); // Chuyển thời gian bắt đầu sang giây
            int end = timeToSeconds(toTime); // Chuyển thời gian kết thúc sang giây
            int periodRevenue = 0; // Biến lưu doanh thu trong khoảng thời gian

            // Sử dụng lower_bound và upper_bound để tìm doanh thu trong khoảng thời gian
            auto itStart = revenueByTime.lower_bound(start); // Tìm phần tử đầu tiên trong `revenueByTime` có thời gian >= start
            auto itEnd = revenueByTime.upper_bound(end); // Tìm phần tử đầu tiên trong `revenueByTime` có thời gian > end

            for (auto it = itStart; it != itEnd; ++it) { // Duyệt từ `itStart` đến `itEnd`
                periodRevenue += it->second; // Cộng doanh thu của mỗi đơn hàng vào tổng doanh thu của khoảng thời gian
            }

            cout << periodRevenue << endl; // In ra tổng doanh thu trong khoảng thời gian yêu cầu
        }
    }

    return 0; // Kết thúc chương trình
}
