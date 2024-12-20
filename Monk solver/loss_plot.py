import numpy as np
from matplotlib import pyplot as plt

filepath = "NN_results/training_loss.txt"
loss = np.loadtxt(filepath)

x = np.linspace(0, len(loss), len(loss))

plt.errorbar(x, loss, fmt = "--")
plt.grid(ls = 'dashed', axis = 'both')
plt.xlabel('Epochs')
plt.ylabel("Loss")
plt.title('Loss')
plt.show()
