#include <Wire.h> //I2C library

void i2c_eeprom_write_byte( int deviceaddress, unsigned int eeaddress, byte data ) {
  int rdata = data;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(rdata);
  Wire.endTransmission();
}

byte i2c_eeprom_read_byte( int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress, 32);
  //if (Wire.available()) rdata = Wire.read();
  while (Wire.available()) rdata = Wire.read();
  return rdata;
}
unsigned long stamp = 0;
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("The I2C Speed is 100kHz, Serial beginning.. ");
  //Serial.println("The I2C Speed is 400kHz, Serial beginning.. ");
  //Serial.println("The I2C Speed is 610kHz, Serial beginning.. ");
  //for (int i = 0; i < 256; i++)
  //{
  //  i2c_eeprom_write_byte(0x50, i, i);
  //  delay(3);
  //}
  //Serial.println("Memory written");
  stamp = millis();
}
void loop()
{
  long addr = 0; //first address
  byte b;
  while (addr < 65536)
  {
    b = i2c_eeprom_read_byte(0x50, addr);
    addr += 32;
  }
  Serial.print("All has been read, took ");
  Serial.print(millis() - stamp);
  Serial.println(" milliseconds to complete.");
  stamp = millis();
}


