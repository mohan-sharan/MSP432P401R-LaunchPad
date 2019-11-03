import serial
import numpy as np
import matplotlib.pyplot as plt
plt.style.use('seaborn')
plt.ion()

msp432 = serial.Serial('COM4', 9600)

x0 = []
y0 = []
i = 0

while True:
    msp432Serial = msp432.readline()
    sensorData = int(msp432Serial)
    x0.append(i)
    y0.append(sensorData)

    i += 1

    plt.ylim(0, 300)
    plt.yticks(np.arange(0, 300, step=20))
    plt.xlim(left=max(0, i-50), right=i+40)

    plt.ylabel('OBJECT DISTANCE (cm)', fontname='monospace', color='black', fontsize=14)
    plt.title('ULTRASONIC SENSOR - ENVIRONMENT MAP', fontname='monospace', color='black', fontsize=16)

    p1, = plt.plot(x0, y0, color='b')
    plt.legend([p1], ['HC-SR04 Reading'], prop={'family': 'monospace'}, loc='upper right', frameon=True)

    plt.grid(True)
    plt.show()
    plt.pause(.000001)