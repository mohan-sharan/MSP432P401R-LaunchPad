import serial
import matplotlib.pyplot as plt
plt.style.use("dark_background")
import numpy as np

#In interactive mode, pyplot functions automatically draw to the screen.
#Interactive mode may also be turned on via matplotlib.pyplot.ion(), and turned off via matplotlib.pyplot.ioff().
plt.ion()

msp432 = serial.Serial('COM4', 115200)  #(port number, baudrate) - create a serial object

i = 0
x0 = []
y0 = []

while True:
    msp432Serial = msp432.readline()
    lightSensorArray = int(msp432Serial)
    x0.append(i)
    y0.append(lightSensorArray)

    i += 1

    plt.xlim(left=max(0, i-20), right=i+20)  #set the x-limits of the current axis
    plt.ylim(0, 12000)  #set the y-limits of the current axis
    plt.yticks(np.arange(0, 12000, step=500))

    plt.ylabel('LUX Readings', fontname='Comic Sans MS', color='white', fontsize=14)  #set the label for the y-axis
    plt.title('AMBIENT LIGHT SENSOR DATA', fontname='Comic Sans MS', color='white', fontsize=16)  #set a title

    p1, = plt.plot(x0, y0, color='r', linewidth=2, marker='o')  #plot x0 versus y0 - red line

    plt.legend([p1], ['OPT3001'], loc='upper right', frameon=True)  #place legend in upper right corner of the chart

    plt.show()  #display the figure
    plt.pause(.000001)  #pause for interval seconds
