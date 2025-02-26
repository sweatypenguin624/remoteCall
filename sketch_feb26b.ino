#include <IRremote.h>

#define IR_PIN 2  // IR Receiver connected to Pin 2

// Define IR codes for numbers 0-9
const unsigned long IR_CODES[] = {
  0xE619FF00, // 0
  0xBA45FF00, // 1
  0xB946FF00, // 2
  0xB847FF00, // 3
  0xBB44FF00, // 4
  0xBF40FF00, // 5
  0xBC43FF00, // 6
  0xF807FF00, // 7
  0xEA15FF00, // 8
  0xF609FF00  // 9
};

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long irCode = IrReceiver.decodedIRData.decodedRawData;

    if (irCode != 0) { // Ignore invalid signals
      int number = -1;  // Default to -1 if code is not found

      // Match received IR code to a number
      for (int i = 0; i < 10; i++) {
        if (irCode == IR_CODES[i]) {
          number = i;
          break;
        }
      }

      if (number != -1) {
        Serial.println(number);  // Send number to Python
      }

    }

    IrReceiver.resume(); // Prepare for next signal
  }
}
