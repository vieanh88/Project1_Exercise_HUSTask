# Hàm Floyd-Warshall để tính đường đi ngắn nhất giữa mọi cặp đỉnh
def floyd_warshall(n, edges):
    # Khởi tạo ma trận khoảng cách với vô cực
    INF = float('inf')
    dist = [[INF] * n for _ in range(n)]
    
    # Thiết lập khoảng cách từ mỗi đỉnh đến chính nó là 0
    for i in range(n):
        dist[i][i] = 0
    
    # Cập nhật khoảng cách ban đầu dựa trên các cung
    for u, v, w in edges:
        dist[u - 1][v - 1] = w  # Đỉnh `u` và `v` được giảm đi 1 để sử dụng chỉ số 0

    # Thuật toán Floyd-Warshall
    for k in range(n):  # Đỉnh trung gian
        for i in range(n):  # Đỉnh bắt đầu
            for j in range(n):  # Đỉnh kết thúc
                if dist[i][k] < INF and dist[k][j] < INF:
                    # Cập nhật khoảng cách nếu đi qua `k` ngắn hơn
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    
    # Đổi tất cả giá trị vô cực thành -1 để biểu thị không có đường đi
    for i in range(n):
        for j in range(n):
            if dist[i][j] == INF:
                dist[i][j] = -1

    return dist

# Đọc dữ liệu đầu vào
n, m = map(int, input().split())  # `n`: số đỉnh, `m`: số cung
edges = [tuple(map(int, input().split())) for _ in range(m)]

# Tính ma trận khoảng cách ngắn nhất
dist_matrix = floyd_warshall(n, edges)

# Xuất kết quả
for row in dist_matrix:
    print(" ".join(map(str, row)))
