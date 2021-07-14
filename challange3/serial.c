#include "uart_driver.h"
#include <stdio.h>

void print_sensor_data(sensor_data_t *sensor_data);

int main() {
    sensor_data_t sensor_data;
    get_sensor_data(&sensor_data);
    print_sensor_data(&sensor_data);
}

/** the data from the sensor comes in as following:
 * 1. id            [char,  1 bytes]
 * 2. int_data      [int,   4 bytes]
 * 3. short_data    [short, 2 bytes]
 * 4. char_data     [char,  1 bytes]
 */
void get_sensor_data(sensor_data_t *sensor_data) {
        //using little endian
    //retrieving id field
    uart_driver_start_communication();
    unsigned char data = uart_driver_get_byte();
    uart_driver_stop_communication();
    /**throughout this program, I will start communcation, read one byte and then stop communcation
     basing on the premise that this might be an actual UART(I am not taking into account the start bit, parity bit and stop bit(s)(because I've seen how the data is layed out), which might be included in the data sent by the transmitting UART)
     and I dont wanna mess up their baud rates */
    sensor_data->id = data;
    //retrieving int_data field in little endian and reconstruct it afterwards as an int
    short i;
    unsigned char int_data[4];
    for(i = 0; i < 4; i++) {
        uart_driver_start_communication();
        data = uart_driver_get_byte();
        uart_driver_stop_communication();
        int_data[i] = data;
    }
    int_data[4] = '\0';
    int int_dataa = (int)int_data[0] + ((int)int_data[1] << 8) + ((int)int_data[2] << 16) + ((int)int_data[3] << 24);
    sensor_data->int_data = int_dataa;
    //retrieving short_data field in little endian and reconstruct it aftwards as a short
    unsigned char short_data[2];
    for(i = 0; i < 2; i++) {
        uart_driver_start_communication();
        data = uart_driver_get_byte();
        uart_driver_stop_communication();
        short_data[i] = data;
    }
    short_data[2] = '\0';
    short short_dataa = (short)short_data[0] + ((short)short_data[1] << 8);
    sensor_data->short_data = short_dataa;
    //retrieving char_data field
    uart_driver_start_communication();
    data = uart_driver_get_byte();
    uart_driver_stop_communication();
    sensor_data->char_data = data;
}

void print_sensor_data(sensor_data_t *sensor_data) {
    printf("id: %d\n", sensor_data->id);
    printf("int_data: %d\n", sensor_data->int_data);
    printf("short_data: %d\n", sensor_data->short_data);
    printf("char_data: %d\n", sensor_data->char_data);
}