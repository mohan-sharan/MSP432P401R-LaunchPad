import serial
import matplotlib.pyplot as plt
plt.style.use("seaborn")
plt.ion()

msp432 = serial.Serial('COM4', 115200)

i = 0
x0 = []
y1 = []
y2 = []

while True:
    msp432Serial = msp432.readline()
    tempArray = msp432Serial.split(b'--')
    objTemp = float(tempArray[0])
    dieTemp = float(tempArray[1])
    x0.append(i)
    y1.append(objTemp)
    y2.append(dieTemp)
    i += 1

    plt.xlim(left=max(0, i-20), right=i+10)
    plt.ylim(20, 40)

    plt.ylabel('Temperature (C)', fontname='Comic Sans MS', color='blue', fontsize=14)
    plt.grid(True)
    plt.title('TMP006 Live Data', fontname='Comic Sans MS', color='red', fontsize=16)

    p1, = plt.plot(x0, y1, color='r', linewidth=2)
    p2, = plt.plot(x0, y2, color='g', linewidth=2)

    plt.legend([p1, p2], ['Object Temperature', 'Die Temperature'], loc='upper right', frameon=True)

    plt.show()
    plt.pause(.000001)
