import serial
import time

ardMod="/dev/cu.usbserial-10 "
# Change 'COM3' to your actual Arduino port (e.g., '/dev/ttyUSB0' for Linux/Mac)
ser = serial.Serial(ardMod, 9600, timeout=1)  
time.sleep(2)  # Allow time for the connection to initialize

print("Listening for IR signals from Arduino...")

phNumber = []  # List to store 10 digits

try:
    while True:
        if ser.in_waiting > 0:  # Check if data is available
            received_data = ser.readline().decode('utf-8').strip()  # Read the data

            if received_data.isdigit():  # Check if it's a valid number
                phNumber.append(received_data)  # Add to list
                print(f"Received: {received_data} | Current: {''.join(phNumber)}")

                if len(phNumber) == 10:  # Stop when 10 digits are collected
                    print(f"\n📞 Phone Number Collected: {''.join(phNumber)}")
                    phNumber.clear()  # Reset for next input

except KeyboardInterrupt:
    print("\nStopping...")
    ser.close()
