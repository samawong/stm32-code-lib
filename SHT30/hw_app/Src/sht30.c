#include "sht30.h"

#include "i2c.h"

SHT30_INFO sht30_info;

int16_t sht3x_probe(void) {
	
}

															 


uint8_t sht_common_generate_crc(uint8_t *data, uint16_t count)
{
    uint8_t crc = 0XFF;
    uint8_t current_byte;
    uint8_t crc_bit;
 
    /* calculates 8-Bit checksum with given polynomial */
    for (current_byte = 0; current_byte < count; ++current_byte)
    {
        crc ^= (data[current_byte]);
        for (crc_bit = 8; crc_bit > 0; --crc_bit)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0X31;
            else
                crc = (crc << 1);
        }
    }
    return crc;
	}
