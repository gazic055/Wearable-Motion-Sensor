import bluetooth
import struct
import matplotlib.pyplot as plt

# Set the name of the target device
target_name = "ESP32_BT"

# Search for nearby Bluetooth devices
nearby_devices = bluetooth.discover_devices()

# Look for the target device in the list of nearby devices
target_address = None
for address in nearby_devices:
    if target_name == bluetooth.lookup_name(address):
        target_address = address
        break

# If the target device was found, establish a Bluetooth serial connection
if target_address is not None:
    port = 1
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((target_address, port))
else:
    print("Could not find target device.")


fallDetected = False

# Receive data over the serial port
while True:
    #cleaned_data = int.from_bytes(data, byteorder="big")
    data = sock.recv(12)
    gfromaX, gfromaY, gfromaZ = struct.unpack('fff',data)
    
    print("gfromaX: ", gfromaX)
    print("gfromaY: ", gfromaY)
    print("gfromaZ: ", gfromaZ)
    print("fallDetected: ", fallDetected)
    
    if(abs(gfromaX) >= 2 or abs(gfromaY) >= 2 or abs(gfromaZ) >= 2):
        fallDetected = True
        

