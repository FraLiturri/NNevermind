# %%
import numpy as np
from matplotlib import pyplot as plt

def plot():
    training_loss_path = "results/tr_loss.txt"
    validation_loss_path = "results/val_loss.txt"

    tr_loss = np.loadtxt(training_loss_path)
    val_loss = np.loadtxt(validation_loss_path)

    x_tr = np.linspace(1, len(tr_loss), len(tr_loss))
    x_val = np.linspace(1, len(val_loss), len(val_loss))

    plt.errorbar(x_tr, tr_loss, fmt="--", label="Training loss")
    plt.errorbar(x_val, val_loss, fmt="--", label="Validation loss")

    plt.grid(ls="dashed", axis="both")
    plt.xlabel("Epochs")
    plt.ylabel("Loss")
    plt.savefig("results/loss_plot.pdf")
    plt.legend(loc="best")
    plt.show()