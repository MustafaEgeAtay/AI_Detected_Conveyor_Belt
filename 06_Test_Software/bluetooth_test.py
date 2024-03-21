import time
import serial

print("UART Demonstration Program")
print("NVIDIA Jetson Nano Developer Kit")


serial_port = serial.Serial(
    port="/dev/ttyTHS1",
    baudrate=9600,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
)
# Wait a second to let the port initialize
time.sleep(1)

try:

    while True:
        serial_port.write("Test 12345 from Jetson".encode())
        # if we get a carriage return, add a line feed too
        # \r is a carriage return; \n is a line feed
        # This is to help the tty program on the other end 
        # Windows is \r\n for carriage return, line feed
        # Macintosh and Linux use \n
        time.sleep(2)


except KeyboardInterrupt:
    print("Exiting Program")

except Exception as exception_error:
    print("Error occurred. Exiting Program")
    print("Error: " + str(exception_error))

finally:
    serial_port.close()
    pass
