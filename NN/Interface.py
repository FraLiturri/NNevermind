import numpy as np
import subprocess
import sys
from itertools import product
from loguru import logger
import multiprocessing as mp
"""
Eta_hyperparameter = np.linspace(-1,1,2)
Lambda_hyperparameter = np.linspace(-1,1,2)
Alpha_hyperparameter =np.linspace(-1,1,2)



# Genera tutte le combinazioni
combinations = product(Eta_hyperparameter, Lambda_hyperparameter, Alpha_hyperparameter)
subprocess.run(["g++", "Main.cpp", "-o", "Main"], check=True)
# Esegui il comando per ogni combinazione

for eta, lambd, alpha in combinations:
    command = ["./Main", str(eta), str(lambd), str(alpha)]
    result = subprocess.run(command, capture_output=True, text=True)
    print(f"Parametri: eta={eta}, lambda={lambd}, alpha={alpha}")
    print("Output:", result.stdout)
    print("Errori:", result.stderr)




"""
import tkinter as tk
from tkinter import messagebox


def submit_values():
    try:
        #metti dei valori di default se non e' specificato nulla
        if(not eta_min_entry.get())&(not eta_max_entry.get())&(not lambda_min_entry.get())&(not lambda_max_entry.get())&(not alpha_min_entry.get())&(not alpha_max_entry.get()&(not steps_entry.get())):
            messagebox.showinfo("Valori Inseriti di default: ", f"Eta: [-1, 1]\n"
                                               f"Lambda: [-1, 1]\n"
                                               f"Alpha: [-1, 1]\n"
                                               f"Steps: [{2}]\n"
                                               "Attenzione: potrebbero volerci qualche decina di secondi, i valori inseriti sono di default.")
            command = ["./main.exe","-1","1","-1","1","-1","1", "2"]
            result = subprocess.run(command, capture_output=True, text=True)
            print("Output:", result.stdout)
            print("Errori:", result.stderr)
        #metti i valori inseriti dall'utente
        else:
            # Legge i valori inseriti
            eta_min = float(eta_min_entry.get())
            eta_max = float(eta_max_entry.get())
            lambda_min = float(lambda_min_entry.get())
            lambda_max = float(lambda_max_entry.get())
            alpha_min = float(alpha_min_entry.get())
            alpha_max = float(alpha_max_entry.get())
            steps = float(steps_entry.get())
            messagebox.showinfo("Valori Inseriti", f"Eta: [{eta_min}, {eta_max}]\n"
                                               f"Lambda: [{lambda_min}, {lambda_max}]\n"
                                               f"Alpha: [{alpha_min}, {alpha_max}]\n"
                                               f"Steps: [{steps}]\n"
                                               "Attenzione: potrebbero volerci qualche decina di secondi.")
            command = ["./main.exe", str(eta_min),str(eta_max), str(lambda_min),str(lambda_max), str(alpha_min),str(alpha_max), str(steps_entry)]
            result = subprocess.run(command, capture_output=True, text=True)
            print("Output:", result.stdout)
            print("Errori:", result.stderr)
            #assicurati che i valori inseriti siano consistenti...
            if (eta_min>eta_max)|(lambda_min > lambda_max)|(alpha_min>alpha_max):
                raise ValueError
            if(steps<0):
                raise ValueError
    except ValueError:
        messagebox.showerror("Errore", "Inserisci valori numerici validi.")



def navigate(event):
    """Naviga tra i campi con le frecce della tastiera."""
    widget = event.widget
    if event.keysym == "Down":
        # Passa al prossimo widget
        widget.tk_focusNext().focus()
    elif event.keysym == "Up":
        # Torna al widget precedente
        widget.tk_focusPrev().focus()
    return "break"  # Impedisce il comportamento predefinito

# Creazione della finestra principale
root = tk.Tk()
root.title("Intervalli di Parametri")
try:
    process = subprocess.run(["g++",  "-fopenmp", "-o", "main.exe", "main.cpp"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text = True, check = True)
except FileNotFoundError:
    logger.error("Errore fatale: file main non trovato")
    sys.exit()
except subprocess.CalledProcessError as e:
    logger.error("Errore fatale: la compilazione del main ha prodotto un errore.")
    print(e.stderr)
    sys.exit()
# Sezione per il parametro eta
tk.Label(root, text="Eta Min:").grid(row=0, column=0, padx=5, pady=5)
eta_min_entry = tk.Entry(root)
eta_min_entry.grid(row=0, column=1, padx=5, pady=5)

tk.Label(root, text="Eta Max:").grid(row=0, column=2, padx=5, pady=5)
eta_max_entry = tk.Entry(root)
eta_max_entry.grid(row=0, column=3, padx=5, pady=5)

# Sezione per il parametro lambda
tk.Label(root, text="Lambda Min:").grid(row=1, column=0, padx=5, pady=5)
lambda_min_entry = tk.Entry(root)
lambda_min_entry.grid(row=1, column=1, padx=5, pady=5)

tk.Label(root, text="Lambda Max:").grid(row=1, column=2, padx=5, pady=5)
lambda_max_entry = tk.Entry(root)
lambda_max_entry.grid(row=1, column=3, padx=5, pady=5)

# Sezione per il parametro alpha
tk.Label(root, text="Alpha Min:").grid(row=2, column=0, padx=5, pady=5)
alpha_min_entry = tk.Entry(root)
alpha_min_entry.grid(row=2, column=1, padx=5, pady=5)

tk.Label(root, text="Alpha Max:").grid(row=2, column=2, padx=5, pady=5)
alpha_max_entry = tk.Entry(root)
alpha_max_entry.grid(row=2, column=3, padx=5, pady=5)

#Sezione per specificare il numero di passi dello spazio delle fasi(es: 2 vuol dire che ho 8 punti)
tk.Label(root, text="Steps Number:").grid(row=3, column=0, padx=5, pady=5)
steps_entry = tk.Entry(root)
steps_entry.grid(row=3, column=1, padx=5, pady=5)


# Pulsante per avviare il training, da migliorare
submit_button = tk.Button(root, text="Conferma", command=submit_values)
submit_button.grid(row=4, column=0, columnspan=4, pady=10)


# Piccolo improvement della qualita' di vita...
for widget in [eta_min_entry, eta_max_entry, lambda_min_entry, lambda_max_entry, alpha_min_entry, alpha_max_entry, ste]:
    widget.bind("<Up>", navigate)
    widget.bind("<Down>", navigate)

root.mainloop()

