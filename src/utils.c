#include "utils.h"

uint8_t checkParity(uint8_t byte)
{
    // Đếm số bit 1 trong byte
    uint8_t count = 0;
    for (uint8_t i = 0; i < 8; i++) {
        if (byte & (1 << i)) count++;
    }
    // Parity chẵn: trả về 1 nếu số bit 1 là chẵn, ngược lại trả về 0
    // return (count % 2 == 0) ? 1 : 0;
    if (count % 2 == 0)
    {
        printf("Parity chan\n");
        return 1;
    } else {
        printf("Parity le\n");
        return 0;
    }
}

uint8_t reverseBits(uint8_t byte)
{
    uint8_t rev = 0;

    for (int i = 0; i < 8; ++i) {
        rev <<= 1;              // Dịch result sang trái
        rev |= (byte & 1);      // Lấy bit thấp nhất của byte đưa vào result
        byte >>= 1;                // Dịch byte sang phải để xét bit tiếp theo
    }

    return rev;
}

void pointerDemo(Door* doors)
{
    // Demo pointer to pointer
    Door* p = &doors[0];
    Door** pp = &p;
    printf("Pointer to pointer: Door 0 isOpen = %d\n", (*pp)->statusUnion.status.isOpen);

    // Demo void pointer
    void* vp = (void*)&doors[1];
    Door* d1 = (Door*)vp;
    printf("Void pointer: Door 1 isLocked = %d\n", d1->statusUnion.status.isLocked);

    // Demo const pointer
    Door* const cp = &doors[2];
    printf("Const pointer: Door 2 hasWindow = %d\n", cp->statusUnion.status.hasWindow);

    // Demo pointer to const
    const Door* pc = &doors[3];
    printf("Pointer to const: Door 3 isOpen = %d\n", pc->statusUnion.status.isOpen);
}