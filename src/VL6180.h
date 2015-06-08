/*
 * VL6180.h
 *
 * Library is based on the useful project done by Kris Winer
 *  https://github.com/kriswiner/VL6180X
 *  
 * Created: 4/23/2015 9:43:14 PM
 *  Author: smkk
 */ 

#include "Arduino.h"

#ifndef VL6180_H_
#define VL6180_H_

typedef enum {  // define lower nibble of ALS gain register
    alsGain20 = 0,  // ALS gain of 20
    alsGain10,      // ALS gain of 10.32
    alsGain5,       // ALS gain of 5.21
    alsGain2_5,     // ALS gain of 2.60
    alsGain1_67,    // ALS gain of 1.72
    alsGain1_25,    // ALS gain of 1.28
    alsGain1_0,     // ALS gain of 1.01
    alsGain40       // ALS gain of 40

}ALSGain;


class VL6180 {

private:
    unsigned int _address;
    const char*  _name;

public:
    VL6180(const char* name);
    bool begin(void);

protected:
    float realalsGain;
    ALSGain alsGain;
    bool internal_init(void);
    void getalsGain(void);

private:
    static bool initialized;
};



class VL6180_A : public VL6180 {

public:
    VL6180_A(void): VL6180("VL6180X_L"){};

    /*
       Single-shot range/ALS operation
       single-shot ALS measurement is initiated by writing 0x01 to the
       VL6180X_SYSALS_START register{0x38}.
       • When the measurement is completed, bit 5 of
       VL6180X_RESULT_INTERRUPT_STATUS_GPIO{0x4F} will be set.
       Note that in both cases the start bit, (bit 0) auto-clears.
       • The ALS result is read from VL6180X_SYSALS_INTEGRATION_PERIOD{0x50}.
       • Interrupt status flags are cleared by writing a ‘1’ to the appropriate bit of
       SYSTEM__INTERRUPT_CLEAR{0x15}.
       • Bit 0 of RESULT__RANGE_STATUS{0x4D} and RESULT__ALS_STATUS{0x4E}
       indicate when either sensor is ready for the next operation.
       • Error codes are indicated in bits [7:4] of the status registers
       A detailed description of all the user accessible registers is given in Section 6: Device
       registers.
       Note: Single-shot ALS and range operations cannot be performed simultaneously. Only one of
       these operations should be performed at any one time and once started must be allowed to
       complete before another measurement is started. This is because any current operation will
       be aborted if another is started.
     */
    float ligthPollingRead(void);
};



class VL6180_P : public VL6180 {

public:
    VL6180_P(void): VL6180("VL6180X_P"){};

    /*
        Single-shot range/ALS operation
        A single-shot range or ALS measurement is performed as follows:
        • Write 0x01 to the VL6180X_SYSRANGE__TART register{0x18}.
        • When the measurement is completed, bit 2 of
        VL6180X_RESULT_INTERRUPT_STATUS_GPIO{0x4F} will be set.
        • Similarly, a single-shot ALS measurement is initiated by writing 0x01 to the
        VL6180X_SYSALS_START register{0x38}.
        • When the measurement is completed, bit 5 of
        VL6180X_RESULT_INTERRUPT_STATUS_GPIO{0x4F} will be set.
        Note that in both cases the start bit, (bit 0) auto-clears.
        • The range result is read from RESULT__RANGE_VAL{0x62}.
        • The ALS result is read from VL6180X_SYSALS_INTEGRATION_PERIOD{0x50}.
        • Interrupt status flags are cleared by writing a ‘1’ to the appropriate bit of
        SYSTEM__INTERRUPT_CLEAR{0x15}.
        • Bit 0 of RESULT__RANGE_STATUS{0x4D} and RESULT__ALS_STATUS{0x4E}
        indicate when either sensor is ready for the next operation.
        • Error codes are indicated in bits [7:4] of the status registers
        A detailed description of all the user accessible registers is given in Section 6: Device
        registers.
        Note: Single-shot ALS and range operations cannot be performed simultaneously. Only one of
        these operations should be performed at any one time and once started must be allowed to
        complete before another measurement is started. This is because any current operation will
        be aborted if another is started.
     */
    char rangePollingRead(void);
};

extern VL6180_A smeAmbient;
extern VL6180_P smeProximity;

#endif /* VL6180_H_ */
