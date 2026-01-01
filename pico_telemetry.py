import serial
import time
import sys

# --- CONFIGURATION ---
# Run 'ls /dev/ttyACM*' in terminal to check if this is 0 or 1
SERIAL_PORT = '/dev/ttyACM1'
BAUD_RATE = 115200

print(f"--- PICO MONITOR ---")
print(f"Connecting to {SERIAL_PORT}...")

try:
    # Open the connection
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2) # Wait for connection to stabilize
    print("SUCCESS: Connected!")
    print("Commands: '1' (ON), '0' (OFF), 't' (Temp), 'q' (Quit)")

except Exception as e:
    print(f"\nCRITICAL ERROR: Could not connect to {SERIAL_PORT}")
    print("1. Unplug and replug the Pico.")
    print("2. Run 'ls /dev/ttyACM*' to see the correct number.")
    print(f"System Error: {e}")
    sys.exit()

# --- MAIN LOOP ---
while True:
    try:
        user_input = input("\nCommand: ")
        
        if user_input == 'q':
            print("Closing connection.")
            ser.close()
            break

        # Send command to Pico
        ser.write(user_input.encode('utf-8'))
        
        # Give Pico a moment to process (temperature math takes time)
        if user_input == 't':
            time.sleep(0.1)
        
        # Check for reply
        if ser.in_waiting > 0:
            response = ser.readline().decode('utf-8').strip()
            
            if user_input == 't':
                print(f"🌡️  Pico Temp: {response} °C")
            else:
                print(f"🤖 Pico Says: {response}")
                
    except OSError:
        print("Error: Device disconnected unexpectedly.")
        break