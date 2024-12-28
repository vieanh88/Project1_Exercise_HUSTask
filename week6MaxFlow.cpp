//Bài toán Luồng cực đại, lát cắt cực tiểu (Max Flow - Min Cut)
//Thuật toán sử dụng: Ford-Fulkerson với phương pháp tìm đường tăng dòng bằng BFS

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10004; // Số đỉnh tối đa
const int INF = 1e9; // Vô cực (để khởi tạo dòng ban đầu)

int N, M, s, t; // Số đỉnh, cung, điểm nguồn và điểm đích
vector<vector<int>> capacity; // Ma trận dung lượng của các cung
vector<vector<int>> adj; // Danh sách kề của các đỉnh

// Hàm BFS để tìm đường tăng dòng từ s đến t trong đồ thị còn lại
int bfs(vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1); // Khởi tạo mảng cha với -1
    parent[s] = -2; // Đánh dấu đỉnh nguồn
    queue<pair<int, int>> q; // Hàng đợi để duyệt đồ thị
    q.push({s, INF}); // Đẩy điểm nguồn với dòng chảy vô cực

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            // Nếu chưa đi qua đỉnh next và còn dung lượng
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur; // Gán cha của next là cur
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) // Nếu đến được đỉnh đích
                    return new_flow; // Trả về dòng chảy nhỏ nhất
                q.push({next, new_flow});
            }
        }
    }
    return 0; // Không có đường tăng dòng
}

// Hàm chính tính dòng chảy cực đại
int maxflow() {
    int flow = 0; // Khởi tạo dòng chảy bằng 0
    vector<int> parent(N + 1); // Mảng lưu đường đi từ s đến t

    int new_flow;
    // Tìm đường tăng dòng trong khi còn có thể
    while (new_flow = bfs(parent)) {
        flow += new_flow; // Cộng dòng chảy mới vào dòng chảy tổng

        // Cập nhật dung lượng trên đường đi
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow; // Giảm dung lượng trên cung thuận
            capacity[cur][prev] += new_flow; // Tăng dung lượng trên cung ngược
            cur = prev;
        }
    }

    return flow; // Trả về dòng chảy cực đại
}

int main() {
    cin >> N >> M;
    cin >> s >> t;

    capacity.assign(N + 1, vector<int>(N + 1, 0)); // Khởi tạo ma trận dung lượng
    adj.resize(N + 1); // Khởi tạo danh sách kề

    // Đọc các cung và thêm vào đồ thị
    for (int i = 0; i < M; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        capacity[u][v] += cap; // Cộng dung lượng (tránh ghi đè nếu có nhiều cung)
        adj[u].push_back(v); // Thêm v vào danh sách kề của u
        adj[v].push_back(u); // Thêm u vào danh sách kề của v (cho đồ thị còn lại)
    }

    cout << maxflow() << endl; // In ra dòng chảy cực đại

    return 0;
}
