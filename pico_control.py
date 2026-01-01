import serial
import time

# 1. Setup the connection to the Pico
# 115200 is the default baud rate for the Pico
try:
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
    time.sleep(2) # Give the connection a moment to settle
    print("Connected to Pico! (Type '1' for ON, '0' for OFF, 'q' to quit)")
except:
    print("Error: Could not find Pico at /dev/ttyACM0")
    exit()

# 2. Main Loop
while True:
    user_input = input("Enter command: ")
    
    if user_input == 'q':
        print("Closing connection.")
        ser.close()
        break
    
    # Send the command to the Pico
    # .encode() converts your text string into bytes (0s and 1s)
    ser.write(user_input.encode('utf-8'))
    
    # Check if the Pico sent a reply
    time.sleep(0.1) 
    if ser.in_waiting > 0:
        response = ser.readline().decode('utf-8').strip()
        print(f"   >>> {response}")