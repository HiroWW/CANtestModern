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
    canpack.CANsetup();
    
    Serial.println("CAN setup : COMPLETE");
}

int loopCount = 0;
void loop() {
    // フラグに応じた処理
    // Serial.println(micros());
    uint32_t startTime = micros();
    while (micros() - startTime < 15000){
    }
    // Serial.println(micros());
    switch (CURRENT_FLAG) {
        case MASTER1:
            // MASTER1の場合の処理
            // Serial.println("Executing MASTER1 logic...");
            canMasterToIF.receiveState = 1;
            canMasterToRight.deCommand = 1111.f * (loopCount%10);
            // canpack.CANsend(CAN_ID_MASTERTOIF, &canMasterToIF);
            canpack.CANsend(CAN_ID_MASTERTORIGHT, &canMasterToRight);
            canpack.CANread({CAN_ID_MASTERTOCENTER, CAN_ID_IFTOMASTER, CAN_ID_LEFTTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case MASTER2:
            // MASTER2の場合の処理
            // Serial.println("Executing MASTER2 logic...");
            canMasterToCenter.receiveState = 1;
            canpack.CANsend(CAN_ID_MASTERTOCENTER, &canMasterToCenter);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_IFTOMASTER, CAN_ID_LEFTTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case IF:
            // IFの場合の処理
            // Serial.println("Executing IF logic...");
            canIFtoMaster.receiveState = 1;
            canpack.CANsend(CAN_ID_IFTOMASTER,&canIFtoMaster);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTOCENTER, CAN_ID_LEFTTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case LEFT:
            // LEFTの場合の処理
            // Serial.println("Executing LEFT logic...");
            // canLeftToMaster.receiveState = 1;
            canpack.CANsend(CAN_ID_LEFTTOMASTER, &canLeftToMaster);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTOCENTER, CAN_ID_IFTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case CENTER:
            // CENTERの場合の処理
            // Serial.println("Executing CENTER logic...");
            // canCenterToMaster.receiveState = 1;
            canpack.CANsend(CAN_ID_CENTERTOMASTER, &canCenterToMaster);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTOCENTER, CAN_ID_LEFTTOMASTER, CAN_ID_IFTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case RIGHT:
            // RIGHTの場合の処理
            // Serial.println("Executing RIGHT logic...");
            // canRightToMaster.receiveState = 1;
            canpack.CANsend(CAN_ID_RIGHTTOMASTER, &canRightToMaster);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTORIGHT, CAN_ID_MASTERTOCENTER, CAN_ID_LEFTTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_IFTOMASTER});
            
            break;
        case DEBUG:
            // DEBUG MODE FOR 2 BOARDS COM
            // SEND M1 M2 IF L C 
            canMasterToIF.receiveState = 1;
            canpack.CANsend(CAN_ID_MASTERTOIF, &canMasterToIF);
            canMasterToCenter.receiveState = 1;
            canpack.CANsend(CAN_ID_MASTERTOCENTER, &canMasterToCenter);
            canIFtoMaster.receiveState = 1;
            canpack.CANsend(CAN_ID_IFTOMASTER,&canIFtoMaster);
            // canLeftToMaster.receiveState = 1;
            canpack.CANsend(CAN_ID_LEFTTOMASTER, &canLeftToMaster);
            // canCenterToMaster.receiveState = 1;
            canpack.CANsend(CAN_ID_CENTERTOMASTER, &canCenterToMaster);

            canpack.CANread({CAN_ID_RIGHTTOMASTER});
            break;
        default:
            // 定義されていないフラグの場合の処理
            Serial.println("Unknown flag!");
            break;
    }

    // 現在のフラグをシリアルで出力
    if (loopCount % 1 == 0){

        UTHAPS::println("=======================================================================================================================================");
        // 現在のフラグの名前をシリアルで出力
        Serial.print("Current flag is: ");
        switch (CURRENT_FLAG) {
            case MASTER1: Serial.print("MASTER1"); break;
            case MASTER2: Serial.print("MASTER2"); break;
            case IF: Serial.print("IF"); break;
            case LEFT: Serial.print("LEFT"); break;
            case CENTER: Serial.print("CENTER"); break;
            case RIGHT: Serial.print("RIGHT"); break;
            case DEBUG: Serial.print("DEBUG"); break;
            default: Serial.print("Unknown"); break;
        }
        Serial.print("  ");
        // UTHAPS::println("M1 >> ", canMasterToRight.updateTime, "M2 >> ", canMasterToCenter.receive_state, "IF >> ", canIFtoMaster.receive_state, "LEFT >> ", canLeftToMaster.receive_state, "CENTER >> ", canCenterToMaster.receive_state, "RIGHT >> ", canRightToMaster.receive_state);
        
    }
    loopCount ++;
    
    // RESET
    canMasterToIF.receiveState = false;
    canMasterToCenter.receiveState = false;
    canIFtoMaster.receiveState = false;
    // delay(1000);
}
