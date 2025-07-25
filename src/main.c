#include "door.h"
#include "can_frame.h"
#include "utils.h"

void printDoorStatus(const char* label, Door* doors, int count) {
    printf("%s\n", label);
    for (int i = 0; i < count; i++) {
        printf("  Door %d: open=%d, locked=%d, window=%d, byte=0x%02X\n",
            i, doors[i].statusUnion.status.isOpen,
            doors[i].statusUnion.status.isLocked,
            doors[i].statusUnion.status.hasWindow,
            doors[i].statusUnion.byte);
    }
}

void printFrameBytes(const char* label, CAN_Frame_t* frame) {
    printf("%s\n  Bytes: ", label);
    for (int i = 0; i < 8; i++) {
        printf("0x%02X ", frame->bytes[i]);
    }
    printf("\n");
}

int main() {
    Door doors[4];
    CAN_Frame_t frame;
    for (int i = 0; i < 4; i++) {
        Door_Init(&doors[i], openDoor, closeDoor, lockDoor, unlockDoor);
    }

    int running = 1;
    while (running) {
        printf("\n===== MENU =====\n");
        printf("1. Xem trang thai cua\n");
        printf("2. Thao tac actuator (open/close/lock/unlock)\n");
        printf("3. Packing trang thai vao frame\n");
        printf("4. Unpacking frame vao cua\n");
        printf("5. Kiem tra parity 1 cua\n");
        printf("6. Dao bit trang thai 1 cua\n");
        printf("7. Thao tac advanced pointer\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        int choice; scanf("%d", &choice);
        int idx;
        uint8_t val;
        switch (choice) {
            case 1:
                printDoorStatus("Trang thai cua:", doors, 4);
                break;
            case 2:
                printf("Chon cua (0-3): "); scanf("%d", &idx);
                if (idx < 0 || idx > 3) break;
                printf("Chon thao tac: 1-Open, 2-Close, 3-Lock, 4-Unlock: ");
                int act; scanf("%d", &act);
                if (act == 1) doors[idx].open(&doors[idx]);
                else if (act == 2) doors[idx].close(&doors[idx]);
                else if (act == 3) doors[idx].lock(&doors[idx]);
                else if (act == 4) doors[idx].unlock(&doors[idx]);
                printDoorStatus("Sau thao tac:", doors, 4);
                break;
            case 3:
                packDoorStatus(doors, &frame);
                printFrameBytes("Frame sau packing:", &frame);
                break;
            case 4:
                unpackDoorStatus(&frame, doors);
                printDoorStatus("Trang thai sau unpacking:", doors, 4);
                break;
            case 5:
                printf("Chon cua (0-3): "); scanf("%d", &idx);
                if (idx < 0 || idx > 3) break;
                val = doors[idx].statusUnion.byte;
                printf("Parity cya byte trang thai cua %d: %d\n", idx, checkParity(val));
                if
                break;
            case 6:
                printf("Chon cua (0-3): "); scanf("%d", &idx);
                if (idx < 0 || idx > 3) break;
                val = doors[idx].statusUnion.byte;
                printf("Byte trang thai cua %d dao bit: 0x%02X\n", idx, reverseBits(val));
                break;
            case 7:
                pointerDemo(doors);
                break;
            case 0:
                running = 0;
                break;
            default:
                printf("Chuc nang khong hop le\n");
        }
    }
    printf("Ket thuc chuong trinh.\n");
    return 0;
}


