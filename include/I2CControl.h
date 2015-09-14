#ifndef H_I2CCONTROL
#define H_I2CCONTROL

#include <pthread.h>
// Slave address
#define ADXL345_ADDR            0x53            // 3 Axis Accelerometer         Analog Devices ADXL345 
#define L3G4200D_ADDR           0x69            // 3 Axis Gyro                  ST Microelectronics L3G4200D
#define HMC5883L_ADDR           0x1E            // 3 Axis Magnetometer          Honeywell HMC5883L
#define BMP085_ADDR             0x77            // Barometer + Thermometer      Bosch BMP085
#define PCA9685PW_ADDR          0x40		// PWM				PCA9685PW

typedef struct {
    pthread_mutex_t mutex;
    float accl[3], gyro[3], magn[3];
    float RTD, altitude;
    long RP;
    int ret[3];
    int PWM_pin[4];
    int PWM_power[4];
} I2CVariables;

typedef struct {
    float accl_offset[3], gyro_offset[3], magn_offset[3], altitude_offset;
    float accl_sd[3], gyro_sd[3], magn_sd[3], altitude_sd;
    float accl_abs, magn_abs;
} I2CVariblesCali;

typedef struct {
    I2CVariables *i2c_var;
    float *mean;
    float *sd;
    char c;
} I2CCaliThread;


void ADXL345_init(int i);
int ADXL345_getRawValue(void);
int ADXL345_getRealData(float* acceleration);
void L3G4200D_init(int i);
int L3G4200D_getRawValue(void);
int L3G4200D_getRealData(float* angVel);
void HMC5883L_singleMeasurement(void);
void HMC5883L_init(int i);
int HMC5883L_getRawValue(void);
int HMC5883L_getRealData(float* magn);
int HMC5883L_getRealData_Direct(float* magn);
int HMC5883L_getOriginalData_Direct(float* magn);
int HMC5883L_dataReady(void);
void BMP085_init(int i);
void BMP085_Trigger_UTemp(void);
void BMP085_Trigger_UPressure(void);
int BMP085_getRawTemp(void);
int BMP085_getRawPressure(void);
int BMP085_getRealData(float *RTD, long *RP, float *altitude);
int getAccGyro(float *accl, float *gyro);


void PCA9685PW_PWMReset(void);
void PCA9685PW_init(int i);
int PCA9685PWMFreq(void);
void PCA9685PW_PWMReset(void);
int pca9685PWMReadSingle(int pin, int *data);
int pca9685PWMReadSingleOff(int pin, int *off);
int pca9685PWMReadMulti(int* pin, int data[][2], int num);
int pca9685PWMReadMultiOff(int pin, int *data, int num);
void pca9685PWMWriteSingle(int pin, int* data);
void pca9685PWMWriteSingleOff(int pin, int off);
void pca9685PWMWriteMulti(int *pin, int data[][2], int num);
void pca9685PWMWriteMultiOff(int *pin, int *data, int num);


void I2CVariables_init(I2CVariables *i2c_var);
int I2CVariables_end(I2CVariables *i2c_var);
int Renew_acclgyro(I2CVariables *i2c_var);
int Renew_magn(I2CVariables *i2c_var);
int Renew_magn_Origin(I2CVariables *i2c_var);
int Renew_baro(I2CVariables *i2c_var);

#endif