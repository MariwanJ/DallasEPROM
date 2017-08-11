
#include <OneWire.h>
#include <DallasEPROM.h>

OneWire onew(4);  // on pin 4
DallasEPROM de(&onew);
/*
  Read Application Reg. (64bit) and memory(256bit) of DS2430A
  Modified by Mariwan Jalal mariwan.jalal@gmail.com
*/
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    uint8_t  buffer[32];  // Holds one page of data
    int status;
    int counter=0;
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

            // Read the first page of memory into buffer
            Serial.println("Memmory Contents");
            if ((status = de.readPage(buffer, 0)) == 0) {
                for(int f=0; f<32; f++) {
                    Serial.print(" 0x");
                    Serial.print(buffer[f], HEX);
                    counter++;
                    if (counter==8) {
                        Serial.print("\n");
                        counter=0;
                    }
                }
                //Serial.println((char*)buffer);
            } else {
                sprintf((char*)buffer, "Error reading page! Code: %d", status);
                Serial.println((char*)buffer);
            }
        } else {
            Serial.println("Address CRC is wrong.");
        }
    }
    Serial.println("");
    if(de.isPageLocked(0))
        Serial.println("LOCKED");
    else
        Serial.println("UnLOCKED");
    if(de.rappRegisPROGRAMMED()==0)
        Serial.println("reg is LOCKED");
    else
        Serial.println("reg is UnLOCKED");
    uint8_t data2[8];
    de.readApplicationReg(data2);
    Serial.println("Applications Register");
    for(int f=0; f<8; f++) {
        Serial.print(" 0x");
        Serial.print(data2[f], HEX);
    }
    delay(3000);
}

