#%%
import numpy as np
from matplotlib import pyplot as plt

training_loss_path = "NN_results/training_loss.txt"
tr_loss = np.loadtxt(training_loss_path)

test_loss_path = "NN_results/test_loss.txt"
te_loss = np.loadtxt(test_loss_path)

x_tr = np.linspace(0, len(tr_loss), len(tr_loss))

plt.errorbar(x_tr, tr_loss, color="red", fmt="--", label="Training loss")

plt.grid(ls="dashed", axis="both")
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.title("Test and training loss")
plt.savefig("NN_results/loss_plot.pdf")

handles, labels = plt.gca().get_legend_handles_labels()
extra_label = f"Test loss = {te_loss}"
plt.legend(handles, [f"{label}, {extra_label}" for label in labels])

plt.show()

# %%
