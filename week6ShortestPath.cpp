// Sử dụng thuật toán Dijkstra để tìm đường đi ngắn nhất từ s đến t trong đồ thị có hướng với trọng số không âm.

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits.h>

using namespace std;

const int INF = INT_MAX; // Giá trị vô cực để đại diện cho khoảng cách lớn

int n, m, s, t; // Số đỉnh, số cung, đỉnh nguồn, và đỉnh đích
vector<vector<pair<int, int>>> adj; // Danh sách kề lưu đồ thị (đỉnh và trọng số)

vector<int> dijkstra(int start) {
    vector<int> dist(n + 1, INF); // Khởi tạo khoảng cách ban đầu là vô cực
    dist[start] = 0; // Khoảng cách từ start đến start là 0
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Hàng đợi ưu tiên (min-heap)
    pq.push({0, start}); // Đẩy điểm bắt đầu vào hàng đợi

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Nếu khoảng cách lớn hơn khoảng cách hiện tại, bỏ qua
        if (d > dist[u]) continue;

        // Duyệt các cạnh kề của đỉnh u
        for (auto edge : adj[u]) {
            int v = edge.first; // Đỉnh kề
            int weight = edge.second; // Trọng số của cung (u, v)

            // Nếu tìm được khoảng cách ngắn hơn, cập nhật khoảng cách
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v}); // Thêm vào hàng đợi
            }
        }
    }
    return dist; // Trả về mảng khoảng cách từ start đến tất cả các đỉnh
}

int main() {
    cin >> n >> m;
    adj.resize(n + 1); // Khởi tạo danh sách kề

    // Đọc các cung và thêm vào danh sách kề
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w}); // Thêm cung (u, v) với trọng số w vào danh sách kề
    }

    cin >> s >> t;

    // Tìm khoảng cách ngắn nhất từ s
    vector<int> dist = dijkstra(s);

    // Kiểm tra xem có đường từ s đến t hay không
    if (dist[t] == INF) {
        cout << -1 << endl; // Không có đường đi
    } else {
        cout << dist[t] << endl; // In ra khoảng cách ngắn nhất
    }

    return 0;
}
