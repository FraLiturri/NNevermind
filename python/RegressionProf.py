#%%
import math
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import numpy as np
import keras
from keras.utils import plot_model
import pandas as pd
from tensorflow.keras.optimizers import Adam, SGD
from tensorflow.keras import backend as K

# Creazione dell'ottimizzatore con learning rate specifico
optimizer = Adam(learning_rate=0.001, weight_decay = 0, amsgrad = True, beta_2 = 0.91)
#optimizer = SGD(learning_rate=0.00001, momentum=0., nesterov=False)
# Caricamento del file per verificare il contenuto
file_path = '../data/regression.csv'

df_results = pd.read_csv(file_path, delim_whitespace=True, header=None)

print(df_results)

Y = df_results.iloc[:, 13:16].to_numpy()
def mee_loss(y_true, y_pred):
    return K.mean(K.sqrt(K.sum(K.square(y_true - y_pred), axis=-1)))

# Estrai le successive 6 colonne come array di liste di lunghezza 6
X = df_results.iloc[:, 1:13].to_numpy()
callback = keras.callbacks.EarlyStopping(monitor='loss',
                                             patience=200000)
inputs=keras.layers.Input(shape=(12,))
hidden=keras.layers.Dense(300,activation="relu")(inputs) #FILL HERE# create a new Dense layer with 500 nodes taking "inputs" as input , what is the most appropriate activation?
hidden2=keras.layers.Dense(300,activation="relu")(hidden)
outputs = keras.layers.Dense(3, activation='linear')(hidden2) #FILL THE DOTS# what is the most appropriate activation for the final node of a classifier?
model = keras.models.Model(inputs=inputs, outputs=outputs)

#model.compile(loss='MEE', optimizer=optimizer)
model.compile(loss=mee_loss, optimizer=optimizer)
model.summary()

history=model.fit(X,Y,validation_split=0,epochs=1000, verbose=0) #FILL THE DOTS# What is the name of the keras function to train a model

print(history.history.keys())
#print(history.history['loss'])
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.grid(ls = "dashed", axis = "both")
plt.show()


# %%
