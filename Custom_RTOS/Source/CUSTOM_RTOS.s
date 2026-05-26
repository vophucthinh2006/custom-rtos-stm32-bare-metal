/*
THIS PART IS 100% VIBE CODED, I USED LLM TO MAKE THE VERY FIRST VERSION
WILL BE LEARNED AND ADJUSTED FOR BETTER PERFORMANCE LATER
*/





.syntax unified
.cpu cortex-m3
.thumb

.global os_start
.global PendSV_Handler

.extern current_task
.extern next_task
.extern os_scheduler_launch

.section .text

.type RTOS_Start, %function
os_start:
    /* 1. Gọi hàm C để tìm Task có độ ưu tiên cao nhất, gán vào 'current_task' */
    BL RTOS_Scheduler_Launch

    /* 2. Trỏ vào TCB của Task đầu tiên để lấy con trỏ Stack ban đầu */
    LDR R0, =current_task       @ R0 = Địa chỉ của biến con trỏ 'current_task'
    LDR R0, [R0]                @ R0 = Giá trị bên trong biến (địa chỉ vùng nhớ TCB)
    LDR R0, [R0]                @ R0 = Giá trị của phần tử đầu tiên trong TCB (chính là stack_ptr)

    /* 3. Nạp con trỏ Stack của Task vào thanh ghi PSP (Process Stack Pointer) */
    MSR PSP, R0

    /* 4. Cấu hình CPU chuyển sang dùng PSP cho Thread mode thay vì MSP */
    MOV R0, #0x02               @ Bit SPSEL = 1 (Chọn dùng PSP)
    MSR CONTROL, R0
    ISB                         @ Ép CPU đồng bộ và thực thi cấu hình này ngay lập tức

    /* 5. Khôi phục ngữ cảnh phần mềm 'dummy' (R4-R11) mà ta đã fake trong os_task_create */
    LDMIA PSP!, {R4-R11}

    /* 6. Khôi phục ngữ cảnh phần cứng 'dummy' để bẻ hướng CPU nhảy vào Task */
    LDMIA PSP!, {R0-R3}         @ Pop R0-R3 dummy
    LDMIA PSP!, {R12}           @ Pop R12 dummy
    LDMIA PSP!, {LR}            @ Pop LR dummy (đang giữ mã 0xFFFFFFFD)
    LDMIA PSP!, {PC}            @ Pop PC (Địa chỉ hàm của Task). Lệnh này ép CPU nhảy vào chạy Task!
    LDMIA PSP!, {R0}            @ Giải phóng ô cuối cùng của Stack (chính là xPSR dummy)

    BX LR                       @ Lệnh phòng hờ (Thực tế CPU đã nhảy sang Task ở lệnh PC phía trên)

@ ====================================================================
@ HÀM NGẮT: void PendSV_Handler(void);
@ Chức năng: Thực hiện việc tráo đổi Stack giữa Task cũ và Task mới.
@ ====================================================================
.type PendSV_Handler, %function
PendSV_Handler:
    /* ---------------------------------------------------------------- */
    /* BƯỚC 1: CẤT NGỮ CẢNH CỦA TASK CŨ (SAVE CONTEXT)                  */
    /* ---------------------------------------------------------------- */
    MRS R0, PSP                 @ R0 = Lấy con trỏ Stack PSP của Task đang chạy dở
    STMDB R0!, {R4-R11}         @ Đẩy các thanh ghi R4 đến R11 vào Stack của Task cũ
                                @ (Dấu ! giúp R0 tự động cập nhật giảm xuống vị trí đỉnh mới)

    LDR R1, =current_task       @ R1 = Địa chỉ của biến con trỏ 'current_task'
    LDR R1, [R1]                @ R1 = Địa chỉ vùng nhớ TCB của Task cũ
    STR R0, [R1]                @ TCB->stack_ptr = R0 (Cất đỉnh Stack mới vào TCB để lưu lại)

    /* ---------------------------------------------------------------- */
    /* BƯỚC 2: TRÁO ĐỔI BIẾN CON TRỎ (SWITCH TASK)                      */
    /* ---------------------------------------------------------------- */
    LDR R1, =current_task       @ R1 = Địa chỉ của biến con trỏ 'current_task'
    LDR R2, =next_task          /* R2 = Địa chỉ của biến con trỏ 'next_task'
                                       (được chỉ định trước đó bởi hàm os_sched) */
    LDR R2, [R2]                @ R2 = Địa chỉ vùng nhớ TCB của Task mới
    STR R2, [R1]                @ current_task = next_task (Chính thức đổi ngôi!)

    /* ---------------------------------------------------------------- */
    /* BƯỚC 3: KHÔI PHỤC NGỮ CẢNH CỦA TASK MỚI (RESTORE CONTEXT)        */
    /* ---------------------------------------------------------------- */
    LDR R0, [R2]                @ R0 = current_task->stack_ptr (Lấy đỉnh Stack của Task mới ra)
    LDMIA R0!, {R4-R11}         @ Rút các thanh ghi R4 đến R11 từ Stack của Task mới trả về CPU
                                @ (Dấu ! giúp R0 tự động tăng lên sau khi rút dữ liệu)

    MSR PSP, R0                 @ Cập nhật lại thanh ghi PSP vật lý bằng con trỏ R0 mới

    /* ---------------------------------------------------------------- */
    /* BƯỚC 4: THOÁT NGẮT AN TOÀN                                       */
    /* ---------------------------------------------------------------- */
    MOV LR, #0xFFFFFFFD         @ Gán mã EXC_RETURN vào thanh ghi LR để ép CPU
                                @ biết khi thoát ngắt phải khôi phục nốt bằng Stack PSP
    BX LR                       @ Thoát ngắt! Phần cứng tự động POP nốt 8 thanh ghi còn lại
                                @ (R0-R3, R12, LR, PC, xPSR) của Task mới. Task mới tiếp tục chạy mượt mà.
