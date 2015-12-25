/*
 * VL6180.cpp
 *
 * Created: 4/23/2015 9:43:23 PM
 *  Author: smkk
 */ 

#include "VL6180.h"
#include "VL6180Reg.h"
#include <Arduino.h>
#include <Wire.h>

bool VL6180::initialized = false;

static void readRegister_16Bit(byte slaveAddress, uint16_t regToRead, byte *buffer) {
    Wire.beginTransmission(slaveAddress);
    Wire.write((uint8_t)((regToRead >> 8) & 0xFF)); // Put MSB of 16-bit slave register address in Tx buffer
    Wire.write((uint8_t)(regToRead & 0xFF));        // Put LSB of 16-bit slave register address in Tx buffer
    Wire.endTransmission(false);                    //endTransmission but keep the connection active

    Wire.requestFrom(slaveAddress, 1);              //Ask for bytes, once done, bus is released by default
    while(Wire.available() < 1);                    //Hang out until we get the # of bytes we expect

    for(int x = 0 ; x < 1 ; x++) {
        buffer[x] = Wire.read();
    }
    Wire.endTransmission(true);
}

static void writeRegister_16Bit(uint8_t slaveAddress, uint16_t regToWrite, uint8_t dataToWrite){
    Wire.beginTransmission(slaveAddress);
    Wire.write((regToWrite >> 8) & 0xFF);           // Put MSB of 16-bit slave register address in Tx buffer
    Wire.write(regToWrite & 0xFF);                  // Put LSB of 16-bit slave register address in Tx buffer
    Wire.write(dataToWrite);
    Wire.endTransmission();
}

static bool readBufferRegister_16Bit(uint8_t slaveAddress, uint16_t regToRead, uint8_t *buffer, uint8_t bufferLen) {
    bool ret = true;

    Wire.beginTransmission(slaveAddress);
    Wire.write((uint8_t)((regToRead >> 8) & 0xFF)); // Put MSB of 16-bit slave register address in Tx buffer
    Wire.write((uint8_t)(regToRead & 0xFF));        // Put LSB of 16-bit slave register address in Tx buffer
    Wire.endTransmission(false);                    //endTransmission but keep the connection active

    Wire.requestFrom(slaveAddress, bufferLen);      //Ask for bytes, once done, bus is released by default

    uint8_t x = 0;
    while(Wire.available()) {                       //Hang out until we get the # of bytes we expect
        buffer[x++] = Wire.read();
    }

    if (Wire.endTransmission(true)!= 0)
        ret = false;

    return ret;
}


VL6180::VL6180(const char* name): _address(VL6180X_ADDRESS), _name(name) {
    if (VL6180::initialized == false) {
        alsGain = alsGain20;
    }
}

bool VL6180::begin(void) {
    byte data;

    readRegister_16Bit(_address, VL6180X_IDENTIFICATION_MODEL_ID, &data);

    // if the WHOAMI Register return the correct information do the final initialization
    if (data == VL6180X_IDENTIFICATION_MODEL_ID_RETURN){
		// this shall be happen only the first time
        if (VL6180::initialized == false) {
            internal_init();
            VL6180::initialized=true;
        }
    }
	
	return VL6180::initialized;
}


void VL6180::getalsGain() {
    switch (alsGain)
    {
    // Possible ALS gains
    case alsGain20:
        realalsGain = 20.; // get actual ALS gain from nominal index
        break;
    case alsGain10:
        realalsGain = 10.32;
        break;
    case alsGain5:
        realalsGain = 5.21;
        break;
    case alsGain2_5:
        realalsGain = 2.60;
        break;
    case alsGain1_67:
        realalsGain = 1.72;
        break;
    case alsGain1_25:
        realalsGain = 1.28;
        break;
    case alsGain1_0:
        realalsGain = 1.01;
        break;
    case alsGain40:
        realalsGain = 40.;
        break;
    }
}

bool VL6180::internal_init(void) {
    uint8_t reset=0, timeOut=0;

    getalsGain();
    while (reset!=1 && timeOut<100) {
        readRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSTEM_FRESH_OUT_OF_RESET, &reset);  // read fresh_out_of_reset bit

        if(reset == 1) {  // if if fresh_out_of_reset bit set, then device has been freshly initialized

            // SR03 settings AN4545 24/27 DocID026571 Rev 19 SR03 settings
            // http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/DM00122600.pdf
            // Below are the recommended settings required to be loaded onto the VL6180X during the
            // initialisation of the device (see Section 1.3).
            // Mandatory : private registers


            writeRegister_16Bit(VL6180X_ADDRESS, 0x0207, 0x01);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x0208, 0x01);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x0096, 0x00);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x0097, 0xFD);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00e3, 0x00);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00e4, 0x04);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00e5, 0x02);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00e6, 0x01);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00e7, 0x03);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00f5, 0x02);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00d9, 0x05);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00db, 0xce);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00dc, 0x03);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00dd, 0xf8);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x009f, 0x00);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00a3, 0x3c);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00b7, 0x00);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00bb, 0x3c);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00b2, 0x09);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00ca, 0x09);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x0198, 0x01);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x01b0, 0x17);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x01ad, 0x00);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x00ff, 0x05);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x0100, 0x05);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x0199, 0x05);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x01a6, 0x1b);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x01ac, 0x3e);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x01a7, 0x1f);
            writeRegister_16Bit(VL6180X_ADDRESS, 0x0030, 0x00);

            // configure range measurement for low power
            // Specify range measurement interval in units of 10 ms from 0 (= 10 ms) - 254 (= 2.55 s)

            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSRANGE_INTERMEASUREMENT_PERIOD, 0x09); // 100 ms interval in steps of 10 ms
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSRANGE_VHV_REPEAT_RATE, 0xFF); // sets number of range measurements after which autocalibrate is performed
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSRANGE_VHV_RECALIBRATE, 0x01); // perform temperature calibration of the ranging sensor

            // Set Early Convergence Estimate for lower power consumption
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSRANGE_MAX_CONVERGENCE_TIME, 0x32); // set max convergence time to 50 ms (steps of 1 ms)
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSRANGE_RANGE_CHECK_ENABLES, 0x10 | 0x01);  // enable (0x01) early convergence estimate
            // This ECE is calculated as follows:
            // [(1 - % below threshold) x 0.5 x 15630]/ range max convergence time
            // This is ~123 ms for 50 ms max convergence time and 80% below threshold
            // This is a sixteen bit (2 byte) register with the first byte MSByte and the second LSByte
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE, 0x00); // set early convergence estimate to 5%
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSRANGE_EARLY_CONVERGENCE_ESTIMATE + 1, 0x7B); // set early convergence estimate to 5%

            // Configure ALS
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSALS_INTERMEASUREMENT_PERIOD, 0x0A);   // set to 100 ms
            // Following is a 16-bit register with the first MSByte reserved

            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSALS_INTEGRATION_PERIOD, 0x00);
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSALS_INTEGRATION_PERIOD+1, 0x63);        // set ALS integration time to 100 ms in steps of 1 ms

            // The internal readout averaging sample period can be adjusted from 0 to 255. Increasing the sampling
            // period decreases noise but also reduces the effective max convergence time and increases power consumption:
            // Effective max convergence time = max convergence time - readout averaging period (see
            // Section 2.5: Range timing). Each unit sample period corresponds to around 64.5 ?s additional
            // processing time. The recommended setting is 48 which equates to around 4.3 ms
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_READOUT_AVERAGING_SAMPLE_PERIOD, 0x30);  // compromise between low noise and increased execution time
            // Gain can be 0 = 20, 1 = 10, 2 = 5, 3 = 2.5, 4 = 1.67, 5 = 1.25, 6 = 1.0 and 7 = 40
            // These are value possible for the lower nibble. The upper nibble must be 4
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSALS_ANALOGUE_GAIN, 0x40 | alsGain);   // Sets light and dark gain (don't change upper nibble)
            // Scalar (1 - 32, bits 4:0) to multiply raw ALS count for additonal gain, if necessary
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_FIRMWARE_RESULT_SCALER, 0x01);

            // Configure the interrupts
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSTEM_MODE_GPIO0, 0x00);                // set up GPIO 0 (set to high impedence for now)
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSTEM_MODE_GPIO1, 0x00);                // set up GPIO 1 (set to high impedence for now)
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSTEM_INTERRUPT_CONFIG_GPIO, 0x24);     // enable sample ready interrupt

#if 0
            // enable continuous range mode
            if(VL6180XMode == contRangeMode) {
                writeByte(VL6180X_ADDRESS, VL6180X_SYSRANGE_START, 0x03);  // start auto range mode

            }
            // enable continuous ALS mode
            if(VL6180XMode == contALSMode) {
                // Configure ALS
                writeByte(VL6180X_ADDRESS, VL6180X_SYSALS_INTERMEASUREMENT_PERIOD, 0x32);   // set to 100 ms
                // Following is a 16-bit register with the first MSByte reserved
                writeByte(VL6180X_ADDRESS, VL6180X_SYSALS_INTEGRATION_PERIOD+1, 0x32);        // set ALS integration time to 50 ms in steps of 1 ms
                writeByte(VL6180X_ADDRESS, VL6180X_SYSALS_START, 0x03);                     // start auto range mode
            }
#endif
            // Clear reset bit
            writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSTEM_FRESH_OUT_OF_RESET, 0x00);        // reset fresh_out_of_reset bit to zero
            return true;
        } else {
            timeOut++;
        }
    }
    reset=0;
    return false;
}


float VL6180_A::lightPollingRead(void) {
    uint8_t status;
    uint8_t rawData[2] = {0, 0};
    float als;
    writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSALS_START, START_SINGLE_MODE);

    readRegister_16Bit(VL6180X_ADDRESS, VL6180X_RESULT_INTERRUPT_STATUS_GPIO, &status);
    status = status & ALS_SINGLE_MODE_MASK;

    while (status != ALS_SINGLE_MODE_READY) {
        readRegister_16Bit(VL6180X_ADDRESS, VL6180X_RESULT_INTERRUPT_STATUS_GPIO, &status);
        delay(100); // is really needed ?
        status = status & ALS_SINGLE_MODE_MASK;
    }

    readBufferRegister_16Bit(VL6180X_ADDRESS, VL6180X_RESULT_ALS_VAL, rawData, 2);
    writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSTEM_INTERRUPT_CLEAR, CLEAR_ALS_INT);

    uint16_t alsraw = (uint16_t) (((uint16_t) rawData[0] << 8) | rawData[1]); //get 16-bit als raw value
    als = 0.32f * ((float) alsraw / realalsGain) * (100.0f/100.0f);  // convert to absolute lux

    return (als * 10000);
}

char VL6180_P::rangePollingRead(void) {
    uint8_t status;
    uint16_t alsRaw;
    uint8_t rawData[2] = {0, 0};
    byte    distance;

    writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSRANGE_START, START_SINGLE_MODE);

    readRegister_16Bit(VL6180X_ADDRESS, VL6180X_RESULT_INTERRUPT_STATUS_GPIO, &status);
    status = status & RANGE_SINGLE_MODE_MASK;
    while (status != RANGE_SINGLE_MODE_READY) {
        readRegister_16Bit(VL6180X_ADDRESS, VL6180X_RESULT_INTERRUPT_STATUS_GPIO, &status);
        status = status & RANGE_SINGLE_MODE_MASK;
    }

    readRegister_16Bit(VL6180X_ADDRESS, VL6180X_RESULT_RANGE_VAL, rawData);
    distance=rawData[0];
    writeRegister_16Bit(VL6180X_ADDRESS, VL6180X_SYSTEM_INTERRUPT_CLEAR, CLEAR_ALS_INT);
    return distance;


    return -1; //should never arrive here

}

VL6180_A smeAmbient;
VL6180_P smeProximity;
