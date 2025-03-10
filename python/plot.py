#%%
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Creiamo dati per X, Y, Z
X = np.loadtxt("../data/regression.csv", usecols= 13)
Y = np.loadtxt("../data/regression.csv", usecols= 14)
Z = np.loadtxt("../data/regression.csv", usecols= 15)

# Creiamo la figura e l'asse 3D
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

# Creiamo la superficie
ax.scatter(X, Y, Z, c='b', marker='o')

# Etichette
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Plot Python example')

plt.show()

#%%
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Attiva la modalità interattiva
plt.ion()

# Leggere dati da file
X = np.loadtxt("data/the_hybrids_ML-CUP24-TS.csv", usecols= 1, delimiter = ',')
Y = np.loadtxt("data/the_hybrids_ML-CUP24-TS.csv", usecols= 2, delimiter = ',')
Z = np.loadtxt("data/the_hybrids_ML-CUP24-TS.csv", usecols= 3, delimiter = ',')

# Creare il grafico 3D
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
sc = ax.scatter(X, Y, Z, c=Z, cmap='viridis')

# Etichette
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Interactive Plot')

# Mostra il grafico in una finestra interattiva
plt.show(block=True)
