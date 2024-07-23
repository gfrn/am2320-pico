#include <stdlib.h>
#include "hardware/i2c.h"
#include "am2320.h"

// CRC16 checksum calculator, copied from datasheet
unsigned short crc16(uint8_t *ptr, uint8_t len) {
    unsigned short crc = 0xFFFF;
    while (len--) {
        crc ^= *ptr++;
        for (uint8_t i = 0; i < 8; i++) {
            if (crc & 0x01) {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

int read_sensors(float *temperature, float *humidity) {
    char *reply_buffer = malloc(8*sizeof(char));
    int retval = 0;

    // Wake up sensor
    i2c_write_blocking(i2c_default, AM2320_ADDRESS, "\x00", 1, false);
    sleep_ms(3);

    retval = i2c_write_blocking(i2c_default, AM2320_ADDRESS, "\x03\x00\x04", 3, false);

    if (retval != 3) {
        return retval;
    }

    sleep_ms(2);

    // Read temperature/humidity registers
    retval = i2c_read_blocking(i2c_default, AM2320_ADDRESS, reply_buffer, 8, false);

    if (retval != 8) {
        return retval;
    }

    *humidity = (256U*reply_buffer[2] + reply_buffer[3]) * 0.1f;
    *temperature = (256U*(reply_buffer[4] & 0x7F) + reply_buffer[5]) * (reply_buffer[4] & 0x80 ? -0.1f : 0.1f);

    // Perform checksum check
    retval = crc16(reply_buffer, 6) != 256U * reply_buffer[7] + reply_buffer[6];
    free(reply_buffer);

    return retval;
}