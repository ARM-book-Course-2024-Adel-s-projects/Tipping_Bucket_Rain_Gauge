import serial
import time
import datetime
import select
import sys

def send_and_receive(command, timeout=10):
    # Envía el comando
    ser.write(command.encode('utf-8'))
    print(f"Sent: {command}")

    # Espera una respuesta
    start_time = time.time()
    response = ""
    while time.time() - start_time < timeout:
        # Usa select para verificar si hay datos disponibles para leer
        rlist, _, _ = select.select([ser], [], [], 0.1)
        if rlist:
            response += ser.read(ser.in_waiting).decode('utf-8')
            if response.endswith('\n'):  # Asume que la respuesta termina con un salto de línea
                break
        time.sleep(0.1)

    if response:
        print(f"Received: {response.strip()}")
    else:
        print("No response received within the timeout period.")

def get_current_date_and_time() -> list[int]:
    current_date_time = datetime.datetime.now()

    return [
        current_date_time.year,
        current_date_time.month,
        current_date_time.day,
        current_date_time.hour,
        current_date_time.minute,
        current_date_time.second
    ]

def configure_date_and_time():
    for x in get_current_date_and_time():
        send_and_receive(str(x).zfill(2))

def configure_serial(path: str, baud_rate: int, timeout: int = 0) -> serial.Serial:
    return serial.Serial(path, baud_rate, timeout=timeout)

def print_date(year: int, month: int, day: int, hour: int, minute: int, second: int):
    print(f"\
        Year: {str(year).zfill(2)}, \
        Month: {str(month).zfill(2)}, \
        Day: {str(day).zfill(2)}, \
        Hour: {str(hour).zfill(2)}, \
        Minute: {str(minute).zfill(2)}, \
        Second: {str(second).zfill(2)}"
    )

def set_date_and_time():
    print("Configuring date and time using python script...")

    send_and_receive("2")
    configure_date_and_time()

    print("Date and time were configured...")


if __name__ == '__main__':
    ser = configure_serial('/dev/ttyACM0', 115200, 0)
    time.sleep(2)

    argument = sys.argv[1]

    if argument == '2':
        set_date_and_time()
    elif argument:
        send_and_receive(str(argument))
    else:
        print("Please provide an argument")
        exit()

    ser.flush()
    print("Serial flushed...")
    time.sleep(2)

    while ser.is_open:
        ser.close()
        print("Serial closed...")



    
