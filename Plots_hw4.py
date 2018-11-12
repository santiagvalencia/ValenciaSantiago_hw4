import numpy as np
import matplotlib.pyplot as plt

RG_45 = np.genfromtxt("RG_45.txt")
RG_10 = np.genfromtxt("RG_10.txt")
RG_20 = np.genfromtxt("RG_20.txt")
RG_30 = np.genfromtxt("RG_30.txt")
RG_40 = np.genfromtxt("RG_40.txt")
RG_50 = np.genfromtxt("RG_50.txt")
RG_60 = np.genfromtxt("RG_60.txt")
RG_70 = np.genfromtxt("RG_70.txt")

x_45 = RG_45[:, 1]
y_45 = RG_45[:, 2]
x_10 = RG_10[:, 1]
y_10 = RG_10[:, 2]
x_20 = RG_20[:, 1]
y_20 = RG_20[:, 2]
x_30 = RG_30[:, 1]
y_30 = RG_30[:, 2]
x_40 = RG_40[:, 1]
y_40 = RG_40[:, 2]
x_50 = RG_50[:, 1]
y_50 = RG_50[:, 2]
x_60 = RG_60[:, 1]
y_60 = RG_60[:, 2]
x_70 = RG_70[:, 1]
y_70 = RG_70[:, 2]

plt.plot(x_45, y_45)
plt.xlabel("x (m)")
plt.ylabel("y (m)")
plt.title("Trayectoria con angulo de lanzamiento de 45 grados")
plt.savefig("Tray_45.pdf")
plt.close()

plt.plot(x_45, y_45, label = "45 grados")
plt.plot(x_10, y_10, label = "10 grados")
plt.plot(x_20, y_20, label = "20 grados")
plt.plot(x_30, y_30, label = "30 grados")
plt.plot(x_40, y_40, label = "40 grados")
plt.plot(x_50, y_50, label = "50 grados")
plt.plot(x_60, y_60, label = "60 grados")
plt.plot(x_70, y_70, label = "70 grados")
plt.title("Trayectorias con varios angulos de lanzamiento")
plt.xlabel("x (m)")
plt.ylabel("y (m)")
plt.legend()
plt.savefig("Tray_varias.pdf")
