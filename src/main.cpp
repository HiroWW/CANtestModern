#include <Arduino.h>
#include "print.hpp"
#include "CANpack.hpp"
#include <vector>
#include <unordered_map>

CANpack canpack;

void setup() {
    Serial.println("Waiting for setup...");
    canpack.CANsetup();
    Serial.println("CAN setup : COMPLETE");
}

#include <iostream>

// フラグの定義
#define MASTER1 1
#define MASTER2 2
#define IF 3
#define LEFT 4
#define CENTER 5
#define RIGHT 6



// ================== ここでフラグを設定 ==================








#define CURRENT_FLAG MASTER1








// =======================================================



void loop() {
    // フラグに応じた処理
    switch (CURRENT_FLAG) {
        case MASTER1:
            // MASTER1の場合の処理
            // Serial.println("Executing MASTER1 logic...");
            canMasterToIF.receive_state = 1;
            canpack.CANsend(CAN_ID_MASTERTOIF, &canMasterToIF);
            canpack.CANread({CAN_ID_MASTERTOCENTER, CAN_ID_IFTOMASTER, CAN_ID_LEFTTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case MASTER2:
            // MASTER2の場合の処理
            // Serial.println("Executing MASTER2 logic...");
            canMasterToCenter.receive_state = 1;
            canpack.CANsend(CAN_ID_MASTERTOCENTER, &canMasterToCenter);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_IFTOMASTER, CAN_ID_LEFTTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case IF:
            // IFの場合の処理
            // Serial.println("Executing IF logic...");
            canIFtoMaster.receive_state = 1;
            canpack.CANsend(CAN_ID_IFTOMASTER,&canIFtoMaster);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTOCENTER, CAN_ID_LEFTTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case LEFT:
            // LEFTの場合の処理
            // Serial.println("Executing LEFT logic...");
            canLeftToMaster.receive_state = 1;
            canpack.CANsend(CAN_ID_LEFTTOMASTER, &canLeftToMaster);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTOCENTER, CAN_ID_IFTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case CENTER:
            // CENTERの場合の処理
            // Serial.println("Executing CENTER logic...");
            canCenterToMaster.receive_state = 1;
            canpack.CANsend(CAN_ID_CENTERTOMASTER, &canCenterToMaster);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTOCENTER, CAN_ID_LEFTTOMASTER, CAN_ID_IFTOMASTER, CAN_ID_RIGHTTOMASTER});
            break;
        case RIGHT:
            // RIGHTの場合の処理
            // Serial.println("Executing RIGHT logic...");
            canRightToMaster.receive_state = 1;
            canpack.CANsend(CAN_ID_RIGHTTOMASTER, &canRightToMaster);
            canpack.CANread({CAN_ID_MASTERTOIF, CAN_ID_MASTERTOCENTER, CAN_ID_LEFTTOMASTER, CAN_ID_CENTERTOMASTER, CAN_ID_IFTOMASTER});
            break;
        default:
            // 定義されていないフラグの場合の処理
            Serial.println("Unknown flag!");
            break;
    }

    // 現在のフラグをシリアルで出力
    // 現在のフラグの名前をシリアルで出力
    Serial.print("Current flag is: ");
    switch (CURRENT_FLAG) {
        case MASTER1: Serial.print("MASTER1"); break;
        case MASTER2: Serial.print("MASTER2"); break;
        case IF: Serial.print("IF"); break;
        case LEFT: Serial.print("LEFT"); break;
        case CENTER: Serial.print("CENTER"); break;
        case RIGHT: Serial.print("RIGHT"); break;
        default: Serial.print("Unknown"); break;
    }
    Serial.print("  ");
    UTHAPS::println("M1 >> ", canMasterToIF.receive_state, "M2 >> ", canMasterToCenter.receive_state, "IF >> ", canIFtoMaster.receive_state, "LEFT >> ", canLeftToMaster.receive_state, "CENTER >> ", canCenterToMaster.receive_state, "RIGHT >> ", canRightToMaster.receive_state);
    
    
    // RESET
    canMasterToIF.receive_state = false;
    canMasterToCenter.receive_state = false;
    canIFtoMaster.receive_state = false;
    canLeftToMaster.receive_state = false;
    canCenterToMaster.receive_state = false;
    canRightToMaster.receive_state = false;
}
