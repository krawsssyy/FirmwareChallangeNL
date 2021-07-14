#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char source[10];
	int id;
	unsigned long timestamp;
	int temperature;
	int humidity;
	int pressure;
} measurment_t;

int* serialize(measurment_t measurment, int* sizeOfSerialize) {
	short i;
	short srcLen = strlen(measurment.source);
	int* resultArr = (int*)malloc(srcLen + 4*sizeof(int) + sizeof(long) + 1);//strlen(source) bytes for the string, 4 ints, 1 long, 1 null-byte from source
	//consider little endian
	for(i = 0; i < srcLen; i++)
		resultArr[i] = measurment.source[srcLen - i - 1];
	//we ignore the null-byte at source[strlen(source)] and we place it after the string is ended as a measure of knowing where the string ended,  so we dont waste (10 - strlen(source)) more bytes
	//---for deserialization, read untill first null byte, then add a null-byte in front of the entire string(little-endian)
	resultArr[i] = 0x00;
	int currCount = i;
	//extract bytes of id
	//consider ints = 4 bytes
	for(i = 0; i < 25; i = i + 8)
		resultArr[++currCount] = (measurment.id >> i) & 0xFF;
	//extract bytes of timestamp
	//consider longs = 8 bytes
	for(i = 0; i < 57; i = i + 8)
		resultArr[++currCount] = (measurment.timestamp >> i) & 0xFF;
	//extract bytes of temperature
	for(i = 0; i < 25; i = i + 8)
		resultArr[++currCount] = (measurment.temperature >> i) & 0xFF;
	//extract bytes of humidity
	for(i = 0; i < 25; i = i + 8)
		resultArr[++currCount] = (measurment.humidity >> i) & 0xFF;
	//extract bytes of pressure
	for(i = 0; i < 25; i = i + 8)
		resultArr[++currCount] = (measurment.pressure >> i) & 0xFF;
	*sizeOfSerialize = currCount;
	return resultArr;
}

int main(){
	// for testing purposes - uncomment and recompile if you wanna test the function out

	/*char source[10];
	int id;
	unsigned long timestamp;
	int temperature;
	int humidity;
	int pressure;

	printf("Source : ");scanf("%s", &source);
	printf("ID : ");scanf("%d", &id);
	printf("Timestamp : ");scanf("%lu", &timestamp);
	printf("Temperature : ");scanf("%d", &temperature);
	printf("Humidity : ");scanf("%d", &humidity);
	printf("Pressure : ");scanf("%d", &pressure);

	measurment_t measurment;
	strncpy(measurment.source, source, strlen(source));
	measurment.source[strlen(source)] = '\0';
	measurment.id = id;
	measurment.timestamp = timestamp;
	measurment.temperature = temperature;
	measurment.humidity = humidity;
	measurment.pressure = pressure;

	int sizeOfSerialize;
	int* serializedMeasurment = serialize(measurment, &sizeOfSerialize);
	short i;
	for(i = 0; i <= sizeOfSerialize; i++)
		printf("Byte %d of serialized measurment is : %x\n", i, serializedMeasurment[i]); */

	return 0;
}