#ifndef _DOOR_H_
#define _DOOR_H_

#include <stdint.h>

/**
 * @brief Trạng thái của 1 cửa, sử dụng bitfield để tiết kiệm bộ nhớ.
 * 
 * - isOppen:  1 nếu cửa đang mở, 0 nếu cửa đóng.
 * - isLocked:  1 nếu cửa đang khóa, 0 nếu cửa không khóa.
 * - hasWindow: 1 nếu cửa có cửa sổ, 0 nếu không.
 * - reversed: dự phòng
 * 
 */

typedef struct {
    uint8_t isOpen : 1;         // 1 : mở, 0: đóng
    uint8_t isLocked : 1;       // 1: khóa, 0: mở khóa
    uint8_t hasWindow : 1;      // 1: cửa kính mở

    uint8_t reversed : 5;
} DoorStatus_t;

/**
 * @brief Union đóng gói trạng thái của cửa để thao tác dưới dạng byte.
 */

typedef union {
    DoorStatus_t status;
    uint8_t byte;
} DoorStatusUnion_t;


typedef struct Door Door;

/**
 * @brief Con trỏ hàm actuator, nhận vào địa chỉ struct DoorStatus_t cần thao tác
 */

typedef void (*ActuatorFunc)(Door*);

/**
 * @brief Struct quản lý đầy đủ 1 cửa xe, bao gồm trạng thái và 4 hàm actuator.
 */

struct Door{
    DoorStatusUnion_t statusUnion;
    ActuatorFunc open;
    ActuatorFunc close;
    ActuatorFunc lock;
    ActuatorFunc unlock;
} ;


/**
 * @brief Khởi tạo 1 cửa, gán các hàm actuator và reset trạng thái về mặc định.
 * 
 * @param d      Con trỏ đến cửa cần khởi tạo.
 * @param open   Hàm actuator mở cửa.
 * @param close  Hàm actuator đóng cửa.      
 * @param lock   Hàm actuator khóa cửa.
 * @param unlock Hàm actuator mở khóa cửa.
 */

void Door_Init(Door* d, ActuatorFunc open, ActuatorFunc close, ActuatorFunc lock, ActuatorFunc unlock);

/**
 * @brief Actuator mở cửa (set isOpen = 1).
 * 
 * @param d Con trỏ đến cửa cần kiểm tra.
 * 
 */
void openDoor(Door* d);

/**
 * @brief Actuator đóng cửa (set isOpen = 0).
 * 
 * @param d Con trỏ đến cửa cần kiểm tra.
 * 
 */
void closeDoor(Door* d);

/**
 * @brief Actuator khóa cửa (set isLocked = 1).
 * 
 * @param d Con trỏ đến cửa cần kiểm tra.
 * 
 */             
void lockDoor(Door* d);

/**
 * @brief Actuator mở khóa cửa (set isLocked = 0).
 * 
 * @param d Con trỏ đến cửa cần kiểm tra.
 * 
 */
void unlockDoor(Door* d);


#endif