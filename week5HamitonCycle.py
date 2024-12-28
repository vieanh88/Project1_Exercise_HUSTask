def is_hamiltonian_cycle(graph, n):
    # Hàm đệ quy DFS kiểm tra chu trình Hamilton bắt đầu từ đỉnh `0`
    
    def dfs(v, visited, path_length):
        """
        Hàm DFS đệ quy tìm chu trình Hamilton.
        `v`: đỉnh hiện tại.
        `visited`: danh sách đánh dấu các đỉnh đã thăm.
        `path_length`: chiều dài của đường đi hiện tại.
        """
        if path_length == n:
            # Nếu đã thăm đủ `n` đỉnh và có cạnh nối về lại đỉnh 0
            # => đây là chu trình Hamilton
            return path_length == n and 0 in graph[v]
        
        # Thử đi qua từng đỉnh kề `neighbor` của đỉnh `v`
        for neighbor in graph[v]:
            if not visited[neighbor]:  # Nếu `neighbor` chưa được thăm
                visited[neighbor] = True  # Đánh dấu `neighbor` là đã thăm
                # Đệ quy tìm tiếp từ `neighbor` và tăng `path_length` thêm 1
                if dfs(neighbor, visited, path_length + 1):
                    return True
                # Nếu không tìm thấy chu trình, huỷ đánh dấu `neighbor`
                visited[neighbor] = False
        return False  # Nếu tất cả đỉnh kề không dẫn đến chu trình Hamilton
    
    visited = [False] * n  # Tạo danh sách đánh dấu `visited` với `n` phần tử False
    visited[0] = True  # Đặt đỉnh đầu tiên (0) là đã thăm
    return dfs(0, visited, 1)  # Bắt đầu tìm kiếm từ đỉnh `0` với chiều dài 1

def check_hamiltonian(graphs):
    # Hàm kiểm tra từng đồ thị trong danh sách `graphs`
    results = []  # Danh sách lưu kết quả cho mỗi đồ thị
    for graph in graphs:
        n, m, edges = graph  # `n`: số đỉnh, `m`: số cạnh, `edges`: danh sách các cạnh
        adj_list = [[] for _ in range(n)]  # Tạo danh sách kề trống cho mỗi đỉnh
        
        # Xây dựng danh sách kề từ danh sách các cạnh
        for u, v in edges:
            adj_list[u - 1].append(v - 1)  # Thêm `v` vào danh sách kề của `u`
            adj_list[v - 1].append(u - 1)  # Thêm `u` vào danh sách kề của `v`
        
        # Kiểm tra đồ thị có chu trình Hamilton không
        if is_hamiltonian_cycle(adj_list, n):
            results.append(1)  # Thêm `1` nếu có chu trình Hamilton
        else:
            results.append(0)  # Thêm `0` nếu không có chu trình Hamilton
    
    return results  # Trả về danh sách kết quả cho từng đồ thị

# Đọc đầu vào từ người dùng
t = int(input())  # Số lượng đồ thị cần kiểm tra
graphs = []  # Danh sách lưu thông tin của các đồ thị
for _ in range(t):
    n, m = map(int, input().split())  # `n`: số đỉnh, `m`: số cạnh của đồ thị
    edges = [tuple(map(int, input().split())) for _ in range(m)]  # Đọc `m` cạnh
    graphs.append((n, m, edges))  # Thêm đồ thị vào danh sách `graphs`

# Xử lý từng đồ thị và in kết quả
results = check_hamiltonian(graphs)  # Kiểm tra chu trình Hamilton cho từng đồ thị
for result in results:
    print(result)  # In ra kết quả cho mỗi đồ thị (1 hoặc 0)
