#include "door.h"

void Door_Init(Door* d, ActuatorFunc open, ActuatorFunc close, ActuatorFunc lock, ActuatorFunc unclock)
{
    if(d == NULL) // kiểm tra con trỏ để tránh truy cập vào vùng nhớ không hợp lệ, tránh gây ra lỗi segment default
        return;

    // cài đặt trạng thái mặc định sử dụng biến thành viên byte trong union
    // Trạng thái mặc định ban đầu: cửa đóng (isOpen = 0), mở khóa (isLocked = 0).
    
    /*  thay vì phải cài đặt từng trạng thái 
        d->statusUnion.status.isOpen = 0;
        d->statusUnion.status.isLocked = 0;
        d->statusUnion.status.hasWindow = 0;
    */
    
    d->statusUnion.byte = 0; 

    // Gán các con trỏ hàm
    d->open = open;  // gán địa chỉ hàm (openDoor) vào biến con trỏ hàm open trong struct Door
    d->close = close;
    d->lock = lock;
    d->unlock = unclock;

    // Debug
    /*  printf("[Init] Khoi tao cua: isOpen=%d, isLocked=%d, hasWindow=%d\n",
           d->statusUnion.status.isOpen,
           d->statusUnion.status.isLocked,
           d->statusUnion.status.hasWindow);
           
    */
}

void openDoor(Door* d)
{
    if (d == NULL) return;
    d->statusUnion.status.isOpen = 1; // cửa mở
}

void closeDoor(Door *d)
{
    if (d == NULL) return;
    d->statusUnion.status.isOpen = 0; // cửa đóng
}

void lockDoor(Door *d)
{
    if (d == NULL) return;
    d->statusUnion.status.isLocked = 1; // khóa cửa
}

void unlockDoor(Door *d)
{
    if (d == NULL) return;
    d->statusUnion.status.isLocked = 0; // mở khóa cửa
}