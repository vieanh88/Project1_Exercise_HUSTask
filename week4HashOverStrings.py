# Hàm tính mã băm của chuỗi `s` với cơ số 256 và modulo `m`
def hash_code(s, m):
    hash_value = 0  # Khởi tạo giá trị băm ban đầu là 0
    power = 1  # `power` dùng để tính lũy thừa của 256 (bắt đầu là 256^0)
    
    # Tính mã băm từ phải sang trái của chuỗi
    for char in reversed(s):
        hash_value = (hash_value + ord(char) * power) % m  # Cập nhật giá trị băm
        power = (power * 256) % m  # Cập nhật lũy thừa của 256 với modulo `m`
    
    return hash_value

# Đọc dữ liệu đầu vào
n, m = map(int, input().split())  # `n`: số chuỗi, `m`: số modulo
strings = [input().strip() for _ in range(n)]  # Đọc `n` chuỗi đầu vào

# Tính và in mã băm cho mỗi chuỗi
for s in strings:
    print(hash_code(s, m))  # Gọi hàm `hash_code` để tính và in mã băm của chuỗi `s`
