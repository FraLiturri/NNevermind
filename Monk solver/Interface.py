import numpy as np
import multiprocessing as mp
from Utils import HyperParameters, Grid
import sys
import subprocess
from itertools import product
from loguru import logger
import tkinter as tk
from tkinter import messagebox
import multiprocessing as mp
import os
IsCompilationGood =False

NomeFileDaCompilare = "main.cpp"

#parametri standard griglia
Eta_Min_Default = 0.01
Eta_Max_Default = 0.5
Lambda_Min_Default = 0
Lambda_Max_Default = 0
Alpha_Min_Default = 0
Alpha_Max_Default = 0
Step1_Default = 100
Step2_Default = 1
Step3_Default = 1
Training_Steps_Default = 200
CPU_Number = os.cpu_count()


#parametri standard single training
Eta_single = 0.2
Lambda_single = 0.001
Alpha_single = 0.00001

def CallMain(Inputs):
    command = ["./main.exe",str(Inputs[0]),str(Inputs[1]),str(Inputs[2]),str(Inputs[3])]
    result = subprocess.run(command, capture_output=True, text=True)
    print("Output:", result.stdout)
    print("Errori:", result.stderr)
    

def Compile():
    global IsCompilationGood
    try:
        process = subprocess.run(["g++", "-o", "main.exe", NomeFileDaCompilare], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text = True, check = True)
        IsCompilationGood = True
    except FileNotFoundError:
        logger.error("Errore fatale: file main non trovato")
        messagebox.showerror("Errore", "La compilazione non ha avuto buon fine: leggi l'errore da terminale dopo aver premuto Ok.")
        IsCompilationGood = False
    except subprocess.CalledProcessError as e:
        logger.error("Errore fatale: la compilazione del main ha prodotto un errore.")
        messagebox.showerror("Errore", "La compilazione non ha avuto buon fine: leggi l'errore da terminale dopo aver premuto Ok.")
        IsCompilationGood = False
        print(e.stderr)

def BuildGrid(eta_1, eta_2, lambda_1, lambda_2, alpha_1, alpha_2, step1, step2, step3):
    MyGrid = Grid(eta_1, eta_2, lambda_1, lambda_2, alpha_1, alpha_2, step1, step2, step3)
    return MyGrid
def submit_values():
    global IsCompilationGood
    if IsCompilationGood:
        subprocess.run(["rm" ,"InfoOnStuff.txt"], capture_output=True, text=True)
        try:
            #metti dei valori di default se non e' specificato nulla
            if(not eta_min_entry.get())&(not eta_max_entry.get())&(not lambda_min_entry.get())&(not lambda_max_entry.get())&(not alpha_min_entry.get())&(not alpha_max_entry.get())&(not steps_eta_entry.get())&(not steps_lambda_entry.get())&(not steps_alpha_entry.get())&(not training_steps_entry.get()):
                MyGrid  = BuildGrid(Eta_Min_Default,Eta_Max_Default, Lambda_Min_Default, Lambda_Max_Default, Alpha_Min_Default,Alpha_Max_Default, Step1_Default,Step2_Default,Step3_Default)
                messagebox.showinfo("Valori Inseriti di default: ", f"Eta: [{Eta_Min_Default}, {Eta_Max_Default}]\n"
                                                   f"Lambda: [{Lambda_Min_Default},{Lambda_Max_Default}]\n"
                                                   f"Alpha: [{Alpha_Min_Default},{Alpha_Max_Default}]\n"
                                                   f"Steps: [{Step1_Default}x{Step2_Default}x{Step3_Default}]\n"
                                                   f"Training Steps: [{Training_Steps_Default}]\n"

                                                   "Attenzione: potrebbero volerci qualche decina di secondi, i valori inseriti sono di default.")
            
                Inputs = [[x.Eta, x.Lambda, x.Alpha, Training_Steps_Default] for x in MyGrid.Grid]
                with mp.Pool(processes =  CPU_Number) as pool :
                    results = pool.map(CallMain, Inputs)
            else:
                # Legge i valori inseriti
                eta_min = float(eta_min_entry.get())
                eta_max = float(eta_max_entry.get())
                lambda_min = float(lambda_min_entry.get())
                lambda_max = float(lambda_max_entry.get())
                alpha_min = float(alpha_min_entry.get())
                alpha_max = float(alpha_max_entry.get())
                step1 = float(steps_eta_entry.get())
                step2 = float(steps_lambda_entry.get())
                step3 = float(steps_alpha_entry.get())
                training_steps = float(training_steps_entry.get())
                messagebox.showinfo("Valori Inseriti", f"Eta: [{eta_min}, {eta_max}]\n"
                                               f"Lambda: [{lambda_min}, {lambda_max}]\n"
                                               f"Alpha: [{alpha_min}, {alpha_max}]\n"
                                               f"Steps: [{step1}x{step2}x{step3}]\n"
                                               f"Training Steps: [{training_steps}]\n"
                                               "Attenzione: potrebbero volerci qualche decina di secondi.")
                #assicura che i valori inseriti siano consistenti...
                if (eta_min>eta_max)|(lambda_min > lambda_max)|(alpha_min>alpha_max):
                    raise ValueError
                if((step1<0)|(step2<0)|(step3<0)):
                    raise ValueError
                if(training_steps<0):
                    raise ValueError
                MyGrid = Grid(eta_min, eta_max, lambda_min, lambda_max, alpha_min, alpha_max, step1, step2, step3)
                Inputs = [[x.Eta, x.Lambda, x.Alpha, training_steps] for x in MyGrid.Grid]
                with mp.Pool(processes =  CPU_Number) as pool :
                    results = pool.map(CallMain, Inputs)

        except ValueError:
            messagebox.showerror("Errore", "Inserisci valori numerici validi.")
    else:
        messagebox.showinfo("Compilazione non riuscita", "Assicurati di aver corretto il codice e poi riesegui la compilazione.")


def submit_values_for_single_training():
    global IsCompilationGood
    if IsCompilationGood:
        subprocess.run(["rm","InfoOnStuff.txt"], capture_output=True, text=True)
        try:
            if((not single_eta_entry.get())&(not single_lambda_entry.get())&(not single_alpha_entry.get())&(not single_training_steps_entry.get())):
                messagebox.showinfo("Valori Inseriti di default: ", f"Eta: {Eta_single}\n"
                                                       f"Lambda: {Lambda_single}\n"
                                                       f"Alpha: {Alpha_single}\n"
                                                       f"Training Steps: [{Training_Steps_Default}]\n"

                                                       "Attenzione: potrebbero volerci qualche decina di secondi, i valori inseriti sono di default.")
                Inputs = [Eta_single, Lambda_single, Alpha_single, Training_Steps_Default] 
                CallMain(Inputs)
            else:   
                etaH = float(single_eta_entry.get())
                lambdaH = float(single_lambda_entry.get())
                alphaH = float(single_alpha_entry.get())
                training_Steps = float(single_training_steps_entry.get())
                messagebox.showinfo("Valori Inseriti di default: ", f"Eta: {etaH}\n"
                                                       f"Lambda: {lambdaH}\n"
                                                       f"Alpha: {alphaH}\n"
                                                       f"Training Steps: [{training_Steps}]\n"

                                                       "Attenzione: potrebbero volerci qualche decina di secondi.")
                Inputs = [etaH, lambdaH, alphaH, training_Steps]
                if(training_Steps<0):
                    raise ValueError
                if(etaH<0):
                    raise ValueError
                CallMain(Inputs)
        except ValueError:
            messagebox.showerror("Errore", "Inserisci valori numerici validi.")


    else:
        messagebox.showinfo("Compilazione non riuscita", "Assicurati di aver corretto il codice e poi riesegui la compilazione.")
    return 1







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



def open_single_value_window():
    single_window = tk.Toplevel(root)
    single_window.title("Inserisci Parametri Singoli")

    tk.Label(single_window, text="Eta:").grid(row=0, column=0, padx=5, pady=5)
    global single_eta_entry
    single_eta_entry = tk.Entry(single_window)
    single_eta_entry.grid(row=0, column=1, padx=5, pady=5)

    tk.Label(single_window, text="Lambda:").grid(row=1, column=0, padx=5, pady=5)
    global single_lambda_entry
    single_lambda_entry = tk.Entry(single_window)
    single_lambda_entry.grid(row=1, column=1, padx=5, pady=5)

    tk.Label(single_window, text="Alpha:").grid(row=2, column=0, padx=5, pady=5)
    global single_alpha_entry
    single_alpha_entry = tk.Entry(single_window)
    single_alpha_entry.grid(row=2, column=1, padx=5, pady=5)

    tk.Label(single_window, text="Training Steps:").grid(row=3, column=0, padx=5, pady=5)
    global single_training_steps_entry
    single_training_steps_entry = tk.Entry(single_window)
    single_training_steps_entry.grid(row=3, column=1, padx=5, pady=5)

    submit_button = tk.Button(single_window, text="Conferma", command=submit_values_for_single_training)
    submit_button.grid(row=4, column=0, columnspan=2, pady=10)

    recompile_button = tk.Button(single_window, text="Ricompila", command=Compile)
    recompile_button.grid(row=4, column=2, columnspan=2, pady=10)


# Creazione della finestra principale
root = tk.Tk()
root.title("Intervalli di Parametri")
try:
    process = subprocess.run(["g++", "-o", "main.exe", NomeFileDaCompilare], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text = True, check = True)
    IsCompilationGood = True
except FileNotFoundError:
    logger.error("Errore fatale: file main non trovato")
    messagebox.showerror("Errore", "La compilazione non ha avuto buon fine: leggi l'errore da terminale dopo aver premuto Ok.")
    IsCompilationGood = False
except subprocess.CalledProcessError as e:
    logger.error("Errore fatale: la compilazione del main ha prodotto un errore.")
    messagebox.showerror("Errore", "La compilazione non ha avuto buon fine: leggi l'errore da terminale dopo aver premuto Ok.")
    IsCompilationGood = False
    print(e.stderr)

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
tk.Label(root, text="Eta Steps:").grid(row=4, column=0, padx=5, pady=5)
steps_eta_entry = tk.Entry(root)
steps_eta_entry.grid(row=4, column=1, padx=5, pady=5)

#Sezione per specificare il numero di passi dello spazio delle fasi(es: 2 vuol dire che ho 8 punti)
tk.Label(root, text="Lambda Steps:").grid(row=4, column=2, padx=5, pady=5)
steps_lambda_entry = tk.Entry(root)
steps_lambda_entry.grid(row=4, column=3, padx=5, pady=5)

#Sezione per specificare il numero di passi dello spazio delle fasi(es: 2 vuol dire che ho 8 punti)
tk.Label(root, text="Alpha Steps:").grid(row=4, column=4, padx=5, pady=5)
steps_alpha_entry = tk.Entry(root)
steps_alpha_entry.grid(row=4, column=5, padx=5, pady=5)


#Sezione per specificare il numero di iterazioni di training
tk.Label(root, text="Training Steps:").grid(row=5, column=0, padx=5, pady=5)
training_steps_entry = tk.Entry(root)
training_steps_entry.grid(row=5, column=1, padx=5, pady=5)



# Pulsante per avviare il training, da migliorare
submit_button = tk.Button(root, text="Conferma", command=submit_values)
submit_button.grid(row=7, column=0, columnspan=4, pady=10)

recompile_button = tk.Button(root, text = "Ricompila", command = Compile)
recompile_button.grid(row =7, column = 3, columnspan = 4, pady = 10)



# Pulsante per aprire la finestra secondaria
single_value_button = tk.Button(root, text="Inserisci Parametri Singoli", command=open_single_value_window)
single_value_button.grid(row=7, column=6, columnspan=4, pady=10)

# Piccolo improvement della qualita' di vita...
for widget in [eta_min_entry, eta_max_entry, lambda_min_entry, lambda_max_entry, alpha_min_entry, alpha_max_entry, steps_eta_entry, steps_lambda_entry,steps_alpha_entry, training_steps_entry , submit_button, recompile_button]:
    widget.bind("<Up>", navigate)
    widget.bind("<Down>", navigate)

root.mainloop()


