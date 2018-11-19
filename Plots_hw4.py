import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
################## ODEs #############################
#genera arreglos con los archivos de datos
RG_45 = np.genfromtxt("RG_45.txt")
RG_10 = np.genfromtxt("RG_10.txt")
RG_20 = np.genfromtxt("RG_20.txt")
RG_30 = np.genfromtxt("RG_30.txt")
RG_40 = np.genfromtxt("RG_40.txt")
RG_50 = np.genfromtxt("RG_50.txt")
RG_60 = np.genfromtxt("RG_60.txt")
RG_70 = np.genfromtxt("RG_70.txt")
#toma los valores de (x, y) para cada angulo (un angulo por archivo). Las columnas 1 y 2 de cada archivo son sus correspondientes valores de (x,y)
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
#grafica la trayectoria con 45 grados
plt.plot(x_45, y_45)
plt.xlabel("x (m)")
plt.ylabel("y (m)")
plt.title("Trayectoria con angulo de lanzamiento de 45 grados")
plt.savefig("Tray_45.pdf")
plt.close()
#grafica todas las trayectorias encontradas
plt.plot(x_10, y_10, label = "10 grados")
plt.plot(x_20, y_20, label = "20 grados")
plt.plot(x_30, y_30, label = "30 grados")
plt.plot(x_40, y_40, label = "40 grados")
plt.plot(x_45, y_45, label = "45 grados")
plt.plot(x_50, y_50, label = "50 grados")
plt.plot(x_60, y_60, label = "60 grados")
plt.plot(x_70, y_70, label = "70 grados")
plt.title("Trayectorias con varios angulos de lanzamiento")
plt.xlabel("x (m)")
plt.ylabel("y (m)")
plt.legend()
plt.savefig("Tray_varias.pdf")
plt.close()

#################### PDEs ######################
def plotTemps(nombre, condicion, out_nombre):
    fil, col = np.genfromtxt(nombre).shape #determina el numero de filas y columnas en el archivo de entrada
    a = np.arange(0, col-1) #determina las columnas que componen la distribucion de temperaturas
    T = np.genfromtxt(nombre, usecols = (a)) #crea el arreglo de distribucion de temperaturas
    tiempo = np.genfromtxt(nombre, usecols = (-1))[0]#toma el valor del tiempo correspondiente
    plt.imshow(T, cmap = "jet", vmin = 10, vmax = 100, extent = [0, 50, 0, 50])#muestra un mapa de calor de la imagen entre las temperaturas limite del problema
    plt.xlabel("x (cm)")
    plt.ylabel("y (cm)")
    plt.colorbar(label = "Temperatura (grados C)")
    plt.title(str(tiempo) + " segundos, fronteras "+condicion)
    plt.savefig(out_nombre+".pdf") #guarda la figura
    plt.close()
    #graficas en 3D
    x = np.linspace(0, 50, T.shape[0]) #crea arreglos de x y y para hacer una mesh
    y = np.linspace(0, 50, T.shape[1])
    X, Y = np.meshgrid(x, y) #crea la mesh
    f = plt.figure() #crea una nueva figura
    ax = f.gca(projection='3d') #crea los ejes tridimensionales
    temps = ax.plot_surface(X, Y, T, cmap="jet", linewidth=0, antialiased=False, vmin = 10, vmax = 100) #crea la superficie de temperaturas
    ax.set_zlim(10, 100) #pone limites en el eje z entre 10 y 100 grados, las temperaturas limite del problema
    f.colorbar(temps, label = "Temperatura (grados C)") #pone la barra de color
    plt.title(str(tiempo) + " segundos, fronteras "+condicion)
    plt.xlabel("x (cm)")
    plt.ylabel("y(cm)")
    plt.savefig(out_nombre+"_3D.pdf")#guarda la figura
    plt.close()

#grafica para cada condicion de frontera y cada estado
plotTemps("inicial.txt", "fijas", "inicial_F")
plotTemps("intermedio1_F.txt", "fijas", "intermedio1_F")
plotTemps("intermedio2_F.txt", "fijas", "intermedio2_F")
plotTemps("final_F.txt", "fijas", "final_F")

plotTemps("inicial.txt", "abiertas", "inicial_A")
plotTemps("intermedio1_A.txt", "abiertas", "intermedio1_A")
plotTemps("intermedio2_A.txt", "abiertas", "intermedio2_A")
plotTemps("final_A.txt", "abiertas", "final_A")

plotTemps("inicial.txt", "periodicas", "inicial_P")
plotTemps("intermedio1_P.txt", "periodicas", "intermedio1_P")
plotTemps("intermedio2_P.txt", "periodicas", "intermedio2_P")
plotTemps("final_P.txt", "periodicas", "final_P")
#grafica las temperaturas promedio en el tiempo de cada condicion de frontera 
proms = np.genfromtxt("promedios.txt")
t = proms[:, 0]
T_Fijas = proms[:, 1]
T_Abiertas = proms[:, 2]
T_Periodicas = proms[:, 3]
plt.plot(t, T_Fijas, label = "Fronteras fijas")
plt.plot(t, T_Abiertas, label = "Fronteras abiertas")
plt.plot(t, T_Periodicas, label = "Fronteras periodicas")
plt.title("Temperaturas promedio")
plt.xlabel("Tiempo (s)")
plt.ylabel("Temperatura (grados C)")
plt.legend()
plt.savefig("promedios.pdf")
