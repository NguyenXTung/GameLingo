**Đồ án Game: Lingo!**

**Thông tin sinh viên:**
Tên: Nguyễn Xuân Tùng
Mã sinh viên: 24020354

**Giới thiệu game:**  
Trò chơi Lingo là một trò chơi từ vựng nổi tiếng, cần người chơi có vốn từ tiếng Anh cơ bản. Nhiệm vụ của người chơi là đoán một từ tiếng Anh có độ dài nhất định (Tối thiểu 4 chữ cái, tối đa 9 chữ cái). Có thể biết trước chữ cái đầu hoặc cuối của từ (dựa vào chế độ chơi mà người chơi chọn). Số lần đoán tương đương với số chữ cái của từ. Sau mỗi lần đoán, game sẽ cho biết chữ cái nào có xuất hiện và đúng vị trí so với từ khóa, chữ cái nào có xuất hiện nhưng không đúng vị trí so với từ khóa, chữ cái nào không xuất hiện trong từ khóa. Ván chơi sẽ kết thúc khi đã đoán được từ khóa hay hết lần đoán hoặc bỏ qua từ đó.
-Cách điều khiển:
Nhập các chữ cái trên bàn phím để điền từ.
Space: Gõ lại từ đoán
Enter: Chốt đáp án và kiểm tra từ
Shift: Dùng gợi ý
Left/ Right: Di chuyển ô để nhập
Backspace: Gõ lại từ đoán
Delete: Bỏ qua từ, đồng thời mất một mạng
Esc: Thoát khỏi game, về trang chủ chính.

  
**Ngưỡng điểm mục tiêu: 9-10**  

**Lý do:**  

1. **Tính năng tự làm và tự học:**  
   - Hệ thống từ điển: Lấy từ điển tiếng Anh từ link https://github.com/dwyl/english-words
Nhờ AI tạo từ điển từ khóa gồm các từ tiếng Anh thông dụng, phổ biến
   - Đồ họa 2D: Sử dụng SDL2 và SDL_image để render hình ảnh, texture, hoạt hình.
		Sử dụng SDL_ttf để render chữ cái
   - Âm thanh: Sử dụng SDL_Mixer để chạy nhạc nền và hiệu ứng âm thanh theo sự kiện.
   - Menu hệ thống: Giao diện chính, chọn mức độ, điều chỉnh trò chơi, cài đặt ngôn ngữ giao diện.  
   - Lưu điểm cao: Hệ thống đọc/ghi file lưu điểm cao nhất.  
   - Tính điểm: Điểm sẽ phụ thuộc vào độ dài từ khóa và thời điểm đoán đúng (Đoán càng sớm và từ khóa càng dài, điểm ghi được sẽ càng cao).  
Các trạng thái của chữ cái sau khi kiểm tra:
	- Xanh lá cây: Chữ cái có xuất hiện trong từ khóa, đúng vị trí so với từ khóa
	- Vàng: Chữ cái có xuất hiện trong từ khóa, sai vị trí so với từ khóa
- Xanh dương: Chữ cái không xuất hiện trong từ khóa.
Mục tiêu:
Đoán đúng từ khóa trong số lần nhất định

2. **Thuật toán đã cài đặt:**  
   - Thuật toán kiểm tra từng chữ cái (Kiểm tra tính hợp lệ của từ đoán, kiểm tra tính xuất hiện và vị trí của chữ cái so với từ khóa.

   - Thuật toán chọn ngẫu nhiên từ khóa trong file txt
   - Thuật toán kiểm tra tính hợp lệ của từ đã nhập (Kiểm tra từ đã nhập đủ chữ cái hay không, kiểm tra từ có xuất hiện trong từ điển tiếng Anh không)
3. **Điểm nổi bật:**  
- Kho từ điển phong phú (gần 400 nghìn từ tiếng Anh)
- Hệ thống level: 3 mức độ khó (Easy, Medium, Hard).
- Hệ thống chỉnh số chữ cái của từ: điều chỉnh trong Option (tối thiểu 4 chữ, tối đa 9 chữ cái)
- Hiệu ứng đồ họa: Dùng câu lệnh Sleep để chạy animation  
- Giao diện trực quan: Hiển thị các thông số của game, điểm số, chỉ dẫn của game.
- Hệ thống âm thanh: Nhạc nền và hiệu ứng phù hợp với từng sự kiện.  

**Hướng dẫn cài đặt và chạy game:**  
1. Cài đặt thư viện SDL2, SDL_image, SDL_ttf, SDL_mixer.  
2. Clone repository.  
3. Biên dịch và chạy.  

**Nguồn tham khảo:**  
- **Âm thanh:**  
Được cắt ghép từ các video trên youtube
Link video: https://youtu.be/hv2wd_bQPrM?si=IzS8bbM6K0fEaN1Q
https://youtu.be/5LTsIeG4i1g?si=ZjN9dV0G8qZ2Hfn
Phần mềm cắt ghép âm thanh: Audacity
- **Đồ họa:** Tự thiết kế bằng Powerpoint.
- File thiết kế đồ họa: https://docs.google.com/presentation/d/1OSEJ_czytIkUU9is3DWGizT-Rfi-DgjO/edit?usp=sharing&ouid=107205806872279143306&rtpof=true&sd=true

**Sử dụng AI hỗ trợ:**  
- ChatGPT: Hỗ trợ debug code, gợi ý giải pháp kỹ thuật.
-DeepSeek: Tạo kho từ khóa gồm các từ tiếng Anh thông dụng (có độ dài từ 4 đến 9 chữ cái)
- Mức độ sử dụng: Khoảng 40% code có sự trợ giúp từ AI.
