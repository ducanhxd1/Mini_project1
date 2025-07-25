#include "can_frame.h"
// #include <string.h>

void packDoorStatus(Door* doors, CAN_Frame_t* frame) {
    if (doors == NULL || frame == NULL) return;

    // Copy từng trạng thái cửa vào từng byte trong frame
    frame->door0 = doors[0].statusUnion.byte;
    frame->door1 = doors[1].statusUnion.byte;
    frame->door2 = doors[2].statusUnion.byte;
    frame->door3 = doors[3].statusUnion.byte;

    // Mặc định chưa dùng cờ cảnh báo
    frame->warn_flags = 0;
    frame->reserved[0] = 0;
    frame->reserved[1] = 0;
    frame->reserved[2] = 0;

    printf("[PACK] Dong goi frame:\n");
    printf("  Door 0: 0x%02X\n", frame->door0);
    printf("  Door 1: 0x%02X\n", frame->door1);
    printf("  Door 2: 0x%02X\n", frame->door2);
    printf("  Door 3: 0x%02X\n", frame->door3);
    printf("  Warn flags: 0x%02X\n", frame->warn_flags);
    printf("  Reserved: %02X %02X %02X\n",
           frame->reserved[0],
           frame->reserved[1],
           frame->reserved[2]);
}

void unpackDoorStatus(CAN_Frame_t* frame, Door* doors) {
    if (frame == NULL || doors == NULL) return;

    // Cập nhật trạng thái từng cửa từ frame
    doors[0].statusUnion.byte = frame->door0;
    doors[1].statusUnion.byte = frame->door1;
    doors[2].statusUnion.byte = frame->door2;
    doors[3].statusUnion.byte = frame->door3;

    printf("[UNPACK] Giai ma frame:\n");
    printf("  Door 0: 0x%02X\n", doors[0].statusUnion.byte);
    printf("  Door 1: 0x%02X\n", doors[1].statusUnion.byte);
    printf("  Door 2: 0x%02X\n", doors[2].statusUnion.byte);
    printf("  Door 3: 0x%02X\n", doors[3].statusUnion.byte);
}
