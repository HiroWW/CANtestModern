#include <Arduino.h>
#include "print.hpp"
#include "CANpack.hpp"
#include <vector>
#include <unordered_map>
//--------------------------------------
//   change here to switch read/send
//--------------------------------------
bool IFREAD = true;
bool IFDEBUG = true;
//--------------------------------------

CANpack canpack;

void setup() {
    Serial.println("Waiting for setup...");
    int ids[] = {CAN_ID_CENTERTOMASTER};
    canpack.CANsetup(ids,sizeof(ids));
    Serial.println("CAN setup : COMPLETE");
}

int loopCount = 0;
void loop() {

    //--------------------------------------------------------------------------------------------------
    
    // setup Master to Tail pack and send it to CAN bus
    canMasterToLeft.updateTime = 1.1f * (loopCount % 5 + 1);
    canMasterToLeft.drCommand = 11.11f * (loopCount % 5 + 1);
    canMasterToLeft.deCommand = 111.111f * (loopCount % 5 + 1);
    for (int i = 0; i < 15; i++){
        canMasterToLeft.err_state[i] = 1.0f * i;
    }
    canMasterToLeft.gravity[0] = 33.4f;
    canMasterToLeft.gravity[1] = 66.8f;
    canMasterToLeft.gravity[2] = 99.4f;
    canMasterToLeft.mode = 2.0f * (loopCount % 5 + 1);
    canMasterToLeft.receive_state = true;
    canpack.CANsend(CAN_ID_MASTERTORIGHT ,&canMasterToLeft);

    canLeftToMaster.acc[0] =  1.1f * (loopCount % 5 + 1);
    canLeftToMaster.gyro[2] =  111.111f * (loopCount % 5 + 1);
    canLeftToMaster.heading = 33.44f;
    canpack.CANsend(CAN_ID_CENTERTOMASTER,&canLeftToMaster);
    // canpack.CANsend(CAN_ID_MASTERTORIGHT ,&canMasterToLeft);
    // canpack.CANsend(CAN_ID_MASTERTORIGHT ,&canMasterToLeft);

    UTHAPS::println("TX SIZE",sizeof(canMasterToLeft));

    //--------------------------------------------------------------------------------------------------

    canpack.CANread({CAN_ID_CENTERTOMASTER});

    if (IFDEBUG){
        // UTHAPS::println("---------- 0 : Master To IF content----------");
        // UTHAPS::println("attituded_dt = ",mip.attitude_dt);
        // UTHAPS::println("main_dt = ", mip.main_dt);
        // UTHAPS::println("control_dt = ", mip.control_dt);

        UTHAPS::println("");
        UTHAPS::println("---------- 1 :Tail To Master content----------");
        UTHAPS::println("acc 0", canCenterToMaster.acc[0]);
        UTHAPS::println("gyro 2", canCenterToMaster.gyro[2]);
        UTHAPS::println("heading ", canCenterToMaster.heading);

        UTHAPS::println("---------- 2 : Master to Tail content----------");
        UTHAPS::println("updateTime = ", canMasterToRight.updateTime);
        UTHAPS::println("drCommand = ", canMasterToRight.drCommand);
        UTHAPS::println("deCommand = ", canMasterToRight.deCommand);
        UTHAPS::println("err state = ", canMasterToRight.err_state[1]);
        UTHAPS::println("gravity = ", canMasterToRight.gravity[2]);
        UTHAPS::println("canMasterToRight.mode = ", canMasterToRight.mode);

        UTHAPS::println("---------- EX : loop CNT ----------");

        UTHAPS::println("RX loop count is ",(canMasterToRight.updateTime / 11.1f - 1));
        UTHAPS::println("TX loop count is ", loopCount);
    }
    if (! IFREAD){
        CANMessage message;
        UTHAPS::print("receive data ");
        for (int i = 0; i < 12; i++){
            if (ACAN_T4::can2.receive(message)){
                UTHAPS::println("id", message.id);
                for (int i = 0; i < 8; i++){
                    // int dataCon = message.data[]
                    UTHAPS::print(message.data[i], " ");
                }
                UTHAPS::println("");
            }
        }
    }
    loopCount++ ;
    if (loopCount == 5){
        loopCount = 0;
    }
}

// struct -> union OK
// union -> cobs OK
// cobs -> cutarr OK
    // while文するとおかしくなる。
// buffer -> msgdata NG
    // msg dataを切り抜く処理がおかしいよよね～～
    // indexを変えるとmsgdataとdataEncodedの値は一致する
    // でもcobsにぶちこむとフリーズする　うんこ
// msgdata -> decoded data OK
// decoded data -> cobsINF ??

/// decoded_dataをていぎすると、message dataの最初に0がはいってしまい、cobsがうまくいかなくなってフリーズする　という仕組み。

// // master
// IF,L,C,R

// // IF
// Master , L,C,R

// // Tail
// Master 