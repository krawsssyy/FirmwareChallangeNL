#ifndef UART_DRIVER_H
#define UART_DRIVER_H

typedef struct {
    unsigned char  id;         /** id of the device */
    unsigned int   int_data;   /** generic int data */
    unsigned short short_data; /** generic short data */
    unsigned char  char_data;  /** generic char data */
} sensor_data_t;

/** this function is used to retrieve the sensor data */
void get_sensor_data(sensor_data_t *sensor_data);

/** function used to start the uart communication */
void uart_driver_start_communication();

/** function used to stop the uart communication */
void uart_driver_stop_communication();

/** function used to return a single byte read from the serial bus. the uart communication MUST be started before
 * calling this function */
unsigned char uart_driver_get_byte();

/** function used to transmit a single byte to the serial bus. the uart communication MUST be started before calling
 * this function */
void uart_driver_send_byte(unsigned char data);

#endif