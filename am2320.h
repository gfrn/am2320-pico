#ifndef _inc_am2320
#define _inc_am2320

#define AM2320_ADDRESS 0x5C

/**
	@brief read sensor data (temperature and humidity)

	@param[out] p : temperature value
	@param[out] x : humidity value

    @return read status
    @retval 0 for success
    @retval 1 for checksum fail
    @retval <0 I2C read failure
**/
int read_sensors(float *temperature, float *humidity);

#endif