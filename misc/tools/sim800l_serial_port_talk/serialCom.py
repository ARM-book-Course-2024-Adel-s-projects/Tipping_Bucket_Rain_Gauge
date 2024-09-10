import serial
import threading
import time
import signal
import sys

ser = serial.Serial(
    port="/dev/ttyACM0",
    baudrate=115200,
    timeout=1
)

time.sleep(2)

def close_connection(received_signal, frame):
    print("\nClossing the serial connection...")
    ser.close()
    sys.exit(0)

signal.signal(signal.SIGINT, close_connection)
signal.signal(signal.SIGTERM, close_connection)

def send_data():
    while True:
        try:
            message = input("Write your message: ")
            message += '\r\n'
            ser.write(message.encode())
        except (KeyboardInterrupt, EOFError):
            close_connection(None, None)

def receive_data():
    while True:
        try:
            if ser.in_waiting > 0:
                response = ser.readline().decode('utf-8').rstrip()
                if response:
                    print(f"\n\nReceived: {response}")
        except (KeyboardInterrupt, EOFError):
            close_connection(None, None)

send_thread = threading.Thread(target=send_data)
receive_thread = threading.Thread(target=receive_data)

send_thread.start()
receive_thread.start()

send_thread.join()
receive_thread.join()
