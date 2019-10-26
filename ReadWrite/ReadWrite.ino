/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>

File myFile; 
char data = 0; 
  
void setup() {
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  
  if(SD.exists("test.txt")){
    SD.remove("test.txt");
  }
}

void loop() {
  long val = 0;
  delay(100);
  for(int i=0; i<512;i++){
      val += analogRead(0);
      delay(100);
  }
  
      myFile = SD.open("test.txt", FILE_WRITE);
      myFile.print(val/512);
      myFile.print(";");
      myFile.close();
      izpis();
}

void izpis(){
    myFile = SD.open("test.txt", FILE_READ);
      if (myFile) {
        Serial.println("\ntest.txt:");
    
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
      }
}
