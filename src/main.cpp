#include <Arduino.h>
#include "print.hpp"
#include "CANpack.hpp"
#include <vector>
#include <unordered_map>

CANpack canpack;


const int extra_buffer_size = 512;

uint8_t extra_read_buffer_1[extra_buffer_size];
uint8_t extra_read_buffer_2[extra_buffer_size];
uint8_t extra_read_buffer_3[extra_buffer_size];
uint8_t extra_read_buffer_4[extra_buffer_size];
uint8_t extra_read_buffer_5[extra_buffer_size];
uint8_t extra_read_buffer_6[extra_buffer_size];
uint8_t extra_read_buffer_7[extra_buffer_size];
uint8_t extra_read_buffer_8[extra_buffer_size];
uint8_t extra_write_buffer_1[extra_buffer_size];
uint8_t extra_write_buffer_2[extra_buffer_size];
uint8_t extra_write_buffer_3[extra_buffer_size];
uint8_t extra_write_buffer_4[extra_buffer_size];
uint8_t extra_write_buffer_5[extra_buffer_size];
uint8_t extra_write_buffer_6[extra_buffer_size];
uint8_t extra_write_buffer_7[extra_buffer_size];
uint8_t extra_write_buffer_8[extra_buffer_size];



#include <iostream>

// フラグの定義
#define MASTER1 1
#define MASTER2 2
#define IF 3
#define LEFT 4
#define CENTER 5
#define RIGHT 6
#define DEBUG 7



// ================== ここでフラグを設定 ==================








#define CURRENT_FLAG RIGHT








// =======================================================


void setup() {
    delay(1000);
    Serial1.addMemoryForRead(extra_read_buffer_1, extra_buffer_size);
    Serial2.addMemoryForRead(extra_read_buffer_2, extra_buffer_size);
    Serial3.addMemoryForRead(extra_read_buffer_3, extra_buffer_size);
    Serial4.addMemoryForRead(extra_read_buffer_4, extra_buffer_size);
    Serial5.addMemoryForRead(extra_read_buffer_5, extra_buffer_size);
    Serial6.addMemoryForRead(extra_read_buffer_6, extra_buffer_size);
    Serial7.addMemoryForRead(extra_read_buffer_7, extra_buffer_size);
    Serial8.addMemoryForRead(extra_read_buffer_8, extra_buffer_size);
    Serial1.addMemoryForWrite(extra_write_buffer_1, extra_buffer_size);
    Serial2.addMemoryForWrite(extra_write_buffer_2, extra_buffer_size);
    Serial3.addMemoryForWrite(extra_write_buffer_3, extra_buffer_size);
    Serial4.addMemoryForWrite(extra_write_buffer_4, extra_buffer_size);
    Serial5.addMemoryForWrite(extra_write_buffer_5, extra_buffer_size);
    Serial6.addMemoryForWrite(extra_write_buffer_6, extra_buffer_size);
    Serial7.addMemoryForWrite(extra_write_buffer_7, extra_buffer_size);
    Serial8.addMemoryForWrite(extra_write_buffer_8, extra_buffer_size);
    Serial.println("Waiting for setup...");
    canpack.CANsetup(nullptr, 0, 40, 1024, true);
    Serial.println("CAN setup : COMPLETE");
}

int loopCount = 0;
void loop() {
    canpack.CANread(2, &canCenterToMaster);
    canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTOCENTER, CAN_ID_LEFTTOMASTER, CAN_ID_IFTOMASTER, CAN_ID_RIGHTTOMASTER});
}
