#include <SoftwareSerial.h>

// Configure software serial port
SoftwareSerial SIM900(7, 8); // RX, TX

void setup() {
  // Start serial communication with Arduino IDE
  Serial.begin(9600);
  
  // Start communication with SIM900 GSM shield at a baud rate of 19200
  // Make sure this matches the baud rate of your SIM900 module
  SIM900.begin(19200);
  
  // Give time to your GSM shield to log on to the network
  delay(20000);   
  
  Serial.println("Checking for incoming and sent messages...");
  
  // Uncomment the following line to read all stored SMS messages (sent and received)
  // readSMS();
}

void loop() {
  // Check if there's any incoming data from the SIM900 module
  if (SIM900.available()) {
    // Read the incoming character
    char c = SIM900.read();
    
    // Print the incoming character to the Serial Monitor
    Serial.print(c);
    
    // If the incoming character is a newline, it indicates the end of a message
    if (c == '\n') {
      // Check if the received message starts with +CMT (indicates incoming SMS)
      if (SIM900.find("+CMT:")) {
        // Read and print the entire SMS message
        String message = SIM900.readStringUntil('\n');
        Serial.println(message);
      }
    }
  }
  
  // Uncomment the following line to read all stored SMS messages (sent and received)
  // readSMS();
  
  // Check for incoming messages every 5 seconds
  delay(5000);
}

void readSMS() {
  // Command to read all stored SMS messages
  SIM900.println("AT+CMGL=\"ALL\"");
  delay(1000);
  
  // Check for response
  while (SIM900.available()) {
    String response = SIM900.readStringUntil('\n');
    Serial.println(response);
  }
}
