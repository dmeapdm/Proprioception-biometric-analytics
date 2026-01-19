import serial
import matplotlib.pyplot as plt
from collections import deque

arduino = serial.Serial("/dev/ttyUSB0", 9600, timeout=1)

# buffers de datos
buffer_size = 100
x_data = deque([0]*buffer_size, maxlen=buffer_size)
y_data = deque([0]*buffer_size, maxlen=buffer_size)
z_data = deque([0]*buffer_size, maxlen=buffer_size)

plt.ion()
fig, ax = plt.subplots()
line_x, = ax.plot(x_data, label="X")
line_y, = ax.plot(y_data, label="Y")
line_z, = ax.plot(z_data, label="Z")
ax.legend()

while True:
    data = arduino.readline().decode().strip()
    if data:
        try:
            x, y, z = map(int, data.split(","))
            x_data.append(x)
            y_data.append(y)
            z_data.append(z)

            line_x.set_ydata(x_data)
            line_x.set_xdata(range(len(x_data)))
            line_y.set_ydata(y_data)
            line_y.set_xdata(range(len(y_data)))
            line_z.set_ydata(z_data)
            line_z.set_xdata(range(len(z_data)))

            ax.relim()
            ax.autoscale_view()
            plt.pause(0.01)
        except:
            continue
