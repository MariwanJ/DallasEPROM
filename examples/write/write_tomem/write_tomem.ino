#include <OneWire.h>
#include <DallasEPROM.h>

/*
  Write Application Reg. (64bit) and memory(256bit) of DS2430A
  Modified by Mariwan Jalal mariwan.jalal@scanfil.com
*/

OneWire onew(4);  // on pin 4
DallasEPROM de(&onew);

void setup() {
  Serial.begin(9600);
}

void loop() {
 // unsigned char buffer[32];  // Holds one page of data
  char buf[256];
  int status;

  // Search for the first compatible EPROM/EEPROM on the bus.

  
  // If you have multiple devices you can use de.setAddress()
  de.search();

  // Print out the 1-wire device's 64-bit address
  Serial.print("Address=");
  for(int i = 0; i < 8; i++) {
    Serial.print(de.getAddress()[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");

  if (de.getAddress()[0] == 0x00) {
    Serial.println("No device was found!");
  } else {
    if (de.validAddress(de.getAddress())) {
      Serial.println("Address CRC is correct.");

//Address of the chip
  unsigned char Addressd[]={0x14, 0x87, 0xcb, 0xBf, 0x7, 0x0, 0x0, 0x43};
    //  de.setAddress (Addressd);     // Use this line if you want to specify a specific oneWire device.

  //Put here your data to be stored in the EEPORM
     uint8_t         buffer[32]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                                 0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,
                                 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
                                 0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20};

        Serial.println("try to write page");
        if ((status = de.writePage(buffer, 0)) != 0) {
        sprintf((char*)buf, "Error writing page! Code: %d", status);
        Serial.println((char*)buf);
        
      }
    }
    }
    //Data stored in the one-time programmable application Reg.
  uint8_t regData[8]={0x50,0x00,0x0,0x0,0x0,0x0,0x0,0x0} ;    //This could be used for holding SN. One-times programming
     de.writeApplicationReg(regData,0);
     de.cpyLockApplicationReg();		// Lock the REG and copy the data 
   delay(7000);
}
