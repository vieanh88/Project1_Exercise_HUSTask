def luu_va_tim_kiem_chuoi():
    # Đọc khối đầu tiên và lưu các khóa vào một tập hợp để tìm kiếm nhanh
    co_so_du_lieu = set()
    
    # Đọc các khóa đầu tiên trước dấu *
    while True:
        khoa = input().strip()
        if khoa == '*':
            break
        co_so_du_lieu.add(khoa)

    # Đọc và xử lý các hành động (find, insert) sau dấu *
    while True:
        hanh_dong = input().strip()
        if hanh_dong == '***':
            break
        
        # Tách lệnh và khóa
        lenh, khoa = hanh_dong.split()
        
        if lenh == 'find':
            # Kiểm tra nếu khóa có tồn tại trong cơ sở dữ liệu
            if khoa in co_so_du_lieu:
                print(1)
            else:
                print(0)
        elif lenh == 'insert':
            # Nếu khóa chưa tồn tại, thêm khóa vào cơ sở dữ liệu và in 1
            if khoa in co_so_du_lieu:
                print(0)
            else:
                co_so_du_lieu.add(khoa)
                print(1)
