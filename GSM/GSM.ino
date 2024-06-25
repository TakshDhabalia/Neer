void setup() {
  // Start communication with the GSM module
  Serial1.begin(9600);
  
  // Start the primary serial communication for debugging
  Serial.begin(9600);

  // Wait for the GSM module to initialize
  delay(5000); // Increase initialization delay
  Serial.println("Initializing...");

  // Check GSM module communication
  if (!checkGSMModule()) {
    Serial.println("GSM module not responding.");
    while (1);
  }

  // Set up SMS reception
  enableSMSReception();

  // Send an SMS
  sendSMS("+917715958053", "Hello from Arduino Mega");
}

void loop() {
  if (Serial1.available()) {
    readSMS();
  }
}

bool checkGSMModule() {
  Serial1.println("AT"); // Check if the module is ready
  delay(1000);

  if (Serial1.available()) {
    String response = Serial1.readString();
    Serial.print("Response: ");
    Serial.println(response);
    return response.indexOf("OK") != -1;
  }

  return false;
}

void sendSMS(const char* number, const char* message) {
  Serial1.println("AT+CMGF=1"); // Set the module to SMS mode
  delay(1000);
  readResponse();

  Serial1.print("AT+CMGS=\"");
  Serial1.print(number);
  Serial1.println("\"");
  delay(1000);
  readResponse();

  Serial1.print(message);
  delay(100);
  Serial1.print((char)26); // Send Ctrl+Z to indicate the end of the message
  delay(5000); // Wait for the module to process the message
  readResponse();
}

void readResponse() {
  long timeout = millis() + 5000; // 5 seconds timeout
  while (millis() < timeout) {
    while (Serial1.available()) {
      String response = Serial1.readString();
      Serial.print("Response: ");
      Serial.println(response);
      if (response.indexOf("OK") != -1 || response.indexOf("+CMGS") != -1) {
        Serial.println("Message sent successfully.");
        return;
      }
      if (response.indexOf("ERROR") != -1) {
        Serial.println("Error sending message.");
        return;
      }
    }
  }
  Serial.println("No response from GSM module.");
}

void enableSMSReception() {
  Serial1.println("AT+CMGF=1"); // Set the module to SMS mode
  delay(1000);
  Serial1.println("AT+CNMI=2,2,0,0,0"); // Configure the module to send received SMS data to the serial port
  delay(1000);
}

void readSMS() {
  if (Serial1.available()) {
    String message = Serial1.readString();
    Serial.print("Received Message: ");
    Serial.println(message);
  }
}
