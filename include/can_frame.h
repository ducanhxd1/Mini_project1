#ifndef _CAN_FRAME_H_
#define _CAN_FRAME_H_

#include <stdio.h>
#include <stdint.h>
#include "door.h"

/**
 * @brief Frame dữ liệu truyền thông, gồm trạng thái 4 cửa và cờ cảnh báo.
 * -door0...door3:  Tráng thái từng cửa (dưới dạng byte).
 * - warn_flags:    Dự phòng cho cảnh báo, parity, lỗi, ...
 * - reserved:      Đệm
 */

typedef union {
    struct {
        uint8_t door0; // Trạng thái cửa 0
        uint8_t door1; // Trạng thái cửa 1
        uint8_t door2; // Trạng thái cửa 2
        uint8_t door3; // Trạng thái cửa 3
        uint8_t warn_flags; // Cờ cảnh báo, parity, lỗi, ...
        uint8_t reserved[3]; // Đệm để đảm bảo kích thước khung CAN
    };
    uint8_t bytes[8]; // Mảng byte để thao tác trực tiếp
} CAN_Frame_t;

/**
 * @brief Đóng gói trạng thái của 4 cửa vào frame truyền thông.
 * @param doors     Mảng 4 cửa nguồn
 * @param frame     Con trỏ tới frame đích
 */

void packDoorStatus(Door* doors, CAN_Frame_t* frame);

/**
 * @brief Giải mã frame truyền thông, cập nhật lại  trạng thái cho 4 cửa.
 * @param frame     Con trỏ tới frame nguồn
 * @param doors     Mảng 4 cửa sẽ được cập nhật
 */

void unpackDoorStatus(CAN_Frame_t* frame, Door* doors);

#endif // _CAN_FRAME_H_