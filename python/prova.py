# %%
import numpy as np
import multiprocessing as mp
import sys
import subprocess
from itertools import product
from loguru import logger
import tkinter as tk
from tkinter import messagebox
import os
from customtkinter import *
import customtkinter as ctk
from matplotlib import pyplot as plt

sys.path.append(
    os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "include"))
)

import parameters as param

# Configure logger
logger.remove()  # Remove default handler
# Add console handler with colorized output
logger.add(
    sys.stdout,
    level="INFO",
    format="<green>{time:YYYY-MM-DD HH:mm:ss}</green> | <level>{level: <8}</level> | <cyan>{name}</cyan>:<cyan>{function}</cyan>:<cyan>{line}</cyan> - <level>{message}</level>",
)

IsCompilationGood = False
NomeFileDaCompilare = "main.cpp"
run_command = ".build/main.exe"

# Standard parameters for grid search;
Eta_Min_Default = 5e-2
Eta_Max_Default = 1
Lambda_Min_Default = 0
Lambda_Max_Default = 1e-4
Alpha_Min_Default = 0
Alpha_Max_Default = 0.1
Step1_Default = 1
Step2_Default = 1
Step3_Default = 2
Training_Steps_Default = 500
CPU_Number = os.cpu_count()
GridSize = Step1_Default * Step2_Default * Step3_Default


# Standard parameters for single run;
Eta_single = 0.001
Lambda_single = 0
Alpha_single = 0.0

switcher_state = False


def toggle():
    switcher_state = not switcher_state


def show_plot():
    if switcher_state:
        subprocess.run(["python", "copilot.py ", "plot"])


def CallMain(Inputs):
    """Run the main executable with given parameters"""
    try:
        command = [
            run_command,
            str(Inputs[0]),
            str(Inputs[1]),
            str(Inputs[2]),
            str(Inputs[3]),
            str(Inputs[4]),
        ]
        logger.debug(f"Running command: {' '.join(command)}")
        result = subprocess.run(command, capture_output=True, text=True)
        if result.returncode != 0:
            logger.error(f"Command failed with error: {result.stderr}")
        return result
    except Exception as e:
        logger.error(f"Exception in CallMain: {str(e)}")
        return None


def CallMainForValidation(Inputs):
    """Run the main executable with validation parameters"""
    try:
        command = [
            run_command,
            str(Inputs[0]),
            str(Inputs[1]),
            str(Inputs[2]),
            str(Inputs[3]),
            str(Inputs[4]),
            str(Inputs[5]),
        ]
        logger.debug(f"Running validation command: {' '.join(command)}")
        result = subprocess.run(command, capture_output=True, text=True)
        if result.returncode != 0:
            logger.error(f"Validation command failed with error: {result.stderr}")
        return result
    except Exception as e:
        logger.error(f"Exception in CallMainForValidation: {str(e)}")
        return None


def Compile():
    """Compile the C++ source file"""
    global IsCompilationGood
    try:
        logger.info(f"Compiling {NomeFileDaCompilare}...")
        process = subprocess.run(
            ["g++", "-fopenmp", "-O3", "-o", "build/main.exe", NomeFileDaCompilare],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            check=True,
        )
        IsCompilationGood = True
        logger.success(f"Successfully compiled {NomeFileDaCompilare}")
        return True
    except FileNotFoundError:
        logger.error(f"Fatal error: {NomeFileDaCompilare} not found.")
        messagebox.showerror(
            "Error",
            f"Fatal error: {NomeFileDaCompilare} not found. Check console for details.",
        )
        IsCompilationGood = False
        return False
    except subprocess.CalledProcessError as e:
        logger.error(f"Fatal Error: compilation failed with error: {e.stderr}")
        messagebox.showerror(
            "Error",
            "Compilation failed. Please check the console for details.",
        )
        IsCompilationGood = False
        print(e.stderr)
        return False


def BuildGrid(eta_1, eta_2, lambda_1, lambda_2, alpha_1, alpha_2, step1, step2, step3):
    """Build parameter grid for hyperparameter search"""
    logger.info(f"Building grid with steps: eta={step1}, lambda={step2}, alpha={step3}")
    MyGrid = param.Grid(
        eta_1, eta_2, lambda_1, lambda_2, alpha_1, alpha_2, step1, step2, step3
    )
    logger.info(f"Grid built with {len(MyGrid.Grid)} total parameter combinations")
    return MyGrid


def DoAnalysis(training_steps, MyGrid):
    """Analyze grid search results and find optimal parameters"""
    logger.info("Starting analysis of grid search results")
    try:
        grid_cell_number = np.loadtxt("results/grid_results.txt", usecols=1)
        val_loss = np.loadtxt("results/grid_results.txt", usecols=10)
        sort = np.argsort(val_loss)
        val_loss = val_loss[sort]
        grid_cell_number = grid_cell_number[sort]

        # Take the 8 best validation losses
        Best_grid_Numbers = grid_cell_number[0:8].astype(int)
        logger.info(f"Best grid indices: {Best_grid_Numbers}")
        BestParamsGrid = MyGrid.Grid[Best_grid_Numbers]
        logger.debug(f"Best parameter combinations: {BestParamsGrid}")
        logger.debug(f"Number of best combinations: {len(BestParamsGrid)}")

        Inputs = [
            [x.Eta, x.Alpha, x.Lambda, training_steps, i, str(1)]
            for i, x in enumerate(BestParamsGrid)
        ]

        final_val_loss = np.array([])
        for i in range(8):
            logger.info(f"Validation round {i+1}/8")
            with mp.Pool(processes=CPU_Number) as pool:
                results = pool.map(CallMainForValidation, Inputs)
                grid_cell_number = np.loadtxt("results/TopGridResults.txt", usecols=1)[
                    i * len(BestParamsGrid) : (i + 1) * len(BestParamsGrid)
                ]
                val_loss = np.loadtxt("results/TopGridResults.txt", usecols=10)[
                    i * len(BestParamsGrid) : (i + 1) * len(BestParamsGrid)
                ]
                sort = np.argsort(grid_cell_number)
                val_loss = val_loss[sort]
                final_val_loss = np.append(final_val_loss, val_loss)

        final_val_loss = final_val_loss.reshape(-1, len(BestParamsGrid)).T

        # Calculate statistics
        val_mean = np.mean(final_val_loss, axis=1)
        val_std = np.std(final_val_loss, axis=1)
        Index = np.argmin(val_mean)
        Best_val_loss = val_mean[Index]
        Best_val_std = val_std[Index]

        Message = f"Best result index: {Index} with validation loss: {Best_val_loss:.6f} ± {Best_val_std:.6f}.\nOptimal parameters (Eta, Alpha, Lambda) = {BestParamsGrid[Index].Eta}, {BestParamsGrid[Index].Alpha}, {BestParamsGrid[Index].Lambda}"
        logger.success(Message)
        print(Message)

        return {
            "index": Index,
            "best_loss": Best_val_loss,
            "best_std": Best_val_std,
            "best_params": {
                "eta": BestParamsGrid[Index].Eta,
                "alpha": BestParamsGrid[Index].Alpha,
                "lambda": BestParamsGrid[Index].Lambda,
            },
        }
    except Exception as e:
        logger.error(f"Error in analysis: {str(e)}")
        messagebox.showerror("Error", f"Analysis failed: {str(e)}")
        return None


def main():
    global switcher_state
    logger.info("Application started")

    def submit_values():
        """Handle grid search submission"""
        global IsCompilationGood
        if not IsCompilationGood:
            logger.warning(
                "Attempted to run grid search without successful compilation"
            )
            messagebox.showinfo("Error", "Compilation failed. Please compile first.")
            return

        logger.info("Starting grid search")

        # Clean previous results
        try:
            subprocess.run(
                ["rm", "results/grid_results.txt"], capture_output=True, text=True
            )
            subprocess.run(
                ["touch", "results/grid_results.txt"], capture_output=True, text=True
            )
            subprocess.run(
                ["rm", "results/TopGridResults.txt"], capture_output=True, text=True
            )
            subprocess.run(
                ["touch", "results/TopGridResults.txt"], capture_output=True, text=True
            )
            logger.info("Cleaned previous result files")
        except Exception as e:
            logger.error(f"Failed to clean result files: {str(e)}")

        try:
            # Check if using default values
            if (
                (not eta_min_entry.get())
                & (not eta_max_entry.get())
                & (not lambda_min_entry.get())
                & (not lambda_max_entry.get())
                & (not alpha_min_entry.get())
                & (not alpha_max_entry.get())
                & (not steps_eta_entry.get())
                & (not steps_lambda_entry.get())
                & (not steps_alpha_entry.get())
                & (not training_steps_entry.get())
            ):
                logger.info("Using default parameters for grid search")
                MyGrid = BuildGrid(
                    Eta_Min_Default,
                    Eta_Max_Default,
                    Lambda_Min_Default,
                    Lambda_Max_Default,
                    Alpha_Min_Default,
                    Alpha_Max_Default,
                    Step1_Default,
                    Step2_Default,
                    Step3_Default,
                )

                Inputs = [
                    [x.Eta, x.Alpha, x.Lambda, Training_Steps_Default, i]
                    for i, x in enumerate(MyGrid.Grid)
                ]

                logger.info(
                    f"Running grid search with {len(Inputs)} parameter combinations"
                )
                with mp.Pool(processes=CPU_Number) as pool:
                    results = pool.map(CallMain, Inputs)

                DoAnalysis(Training_Steps_Default, MyGrid)

            else:
                # Parse user-provided values
                logger.info("Parsing user parameters for grid search")
                eta_min = float(eta_min_entry.get())
                eta_max = float(eta_max_entry.get())
                lambda_min = float(lambda_min_entry.get())
                lambda_max = float(lambda_max_entry.get())
                alpha_min = float(alpha_min_entry.get())
                alpha_max = float(alpha_max_entry.get())
                step1 = int(steps_eta_entry.get())
                step2 = int(steps_lambda_entry.get())
                step3 = int(steps_alpha_entry.get())
                training_steps = int(training_steps_entry.get())

                # Validate parameters
                if (
                    (eta_min > eta_max)
                    | (lambda_min > lambda_max)
                    | (alpha_min > alpha_max)
                ):
                    logger.error(
                        "Invalid parameter ranges: min values must be less than max values"
                    )
                    raise ValueError("Min values must be less than max values")

                if (step1 <= 0) | (step2 <= 0) | (step3 <= 0):
                    logger.error("Invalid step values: steps must be positive")
                    raise ValueError("Steps must be positive")

                if training_steps < 0:
                    logger.error("Invalid training steps: must be non-negative")
                    raise ValueError("Training steps must be non-negative")

                logger.info(
                    f"Building grid with user parameters: eta=[{eta_min},{eta_max}], "
                    f"lambda=[{lambda_min},{lambda_max}], alpha=[{alpha_min},{alpha_max}], "
                    f"steps=({step1},{step2},{step3}), training_steps={training_steps}"
                )

                MyGrid = param.Grid(
                    eta_min,
                    eta_max,
                    lambda_min,
                    lambda_max,
                    alpha_min,
                    alpha_max,
                    step1,
                    step2,
                    step3,
                )

                Inputs = [
                    [x.Eta, x.Alpha, x.Lambda, training_steps, i]
                    for i, x in enumerate(MyGrid.Grid)
                ]

                logger.info(
                    f"Running grid search with {len(Inputs)} parameter combinations"
                )
                with mp.Pool(processes=CPU_Number) as pool:
                    results = pool.map(CallMain, Inputs)

                DoAnalysis(training_steps, MyGrid)

            logger.success("Grid search completed successfully")
            messagebox.showinfo(
                "Success", "Grid search completed. Check console for details."
            )

        except ValueError as e:
            logger.error(f"Value error in grid search: {str(e)}")
            messagebox.showerror("Error", f"Please insert valid values: {str(e)}")
        except Exception as e:
            logger.error(f"Unexpected error in grid search: {str(e)}")
            messagebox.showerror("Error", f"Unexpected error: {str(e)}")

    def submit_values_for_single_training():
        """Handle single training run submission"""
        global IsCompilationGood
        if not IsCompilationGood:
            logger.warning(
                "Attempted to run single training without successful compilation"
            )
            messagebox.showinfo("Error", "Compilation failed. Please compile first.")
            return

        logger.info("Starting single training run")

        # Clean previous results
        try:
            subprocess.run(
                ["rm", "results/grid_results.txt"], capture_output=True, text=True
            )
            logger.info("Cleaned previous result file")
        except Exception as e:
            logger.error(f"Failed to clean result file: {str(e)}")

        try:
            # Check if using default values
            if (
                (not single_eta_entry.get())
                & (not single_lambda_entry.get())
                & (not single_alpha_entry.get())
                & (not single_training_steps_entry.get())
            ):
                Inputs = [
                    Eta_single,
                    Alpha_single,
                    Lambda_single,
                    Training_Steps_Default,
                    0,
                ]
                CallMain(Inputs)
                show_plot()

            else:
                # Parse user-provided values
                logger.info("Parsing user parameters for single training")
                etaH = float(single_eta_entry.get())
                lambdaH = float(single_lambda_entry.get())
                alphaH = float(single_alpha_entry.get())
                training_Steps = float(single_training_steps_entry.get())

                # Validate parameters
                if training_Steps < 0:
                    logger.error("Invalid training steps: must be non-negative")
                    raise ValueError("Training steps must be non-negative")

                if etaH < 0:
                    logger.error("Invalid eta: must be non-negative")
                    raise ValueError("Eta must be non-negative")

                Inputs = [etaH, alphaH, lambdaH, training_Steps, 0]
                CallMain(Inputs)
                show_plot()

            logger.success("Single training run completed successfully")
            messagebox.showinfo(
                "Success", "Single training completed. Check console for details."
            )

        except ValueError as e:
            logger.error(f"Value error in single training: {str(e)}")
            messagebox.showerror("Error", f"Please insert valid values: {str(e)}")
        except Exception as e:
            logger.error(f"Unexpected error in single training: {str(e)}")
            messagebox.showerror("Error", f"Unexpected error: {str(e)}")

        return 1

    # Initial compilation
    logger.info("Performing initial compilation")
    compilation_result = Compile()
    if compilation_result:
        logger.info("Initial compilation successful")
    else:
        logger.warning("Initial compilation failed")

    # Set the appearance mode and theme
    ctk.set_appearance_mode("Dark")
    ctk.set_default_color_theme("blue")
    logger.info("Setting up GUI with Dark theme")

    # Create the main application window
    root = ctk.CTk()
    root.title("Grid Search and Single Run")
    root.attributes("-topmost", True)
    logger.info("Main application window created")

    # Create a tab view
    tab_view = ctk.CTkTabview(root)
    tab_view.pack(expand=True, fill="both", padx=20, pady=20)

    grid_tab = tab_view.add("Grid Search")
    single_run_tab = tab_view.add("Single Run")
    logger.info("Tab view created with Grid Search and Single Run tabs")

    # Grid Search Tab UI
    eta_min_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Eta min [{Eta_Min_Default}]"
    )
    eta_max_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Eta max [{Eta_Max_Default}]"
    )

    eta_min_entry.grid(row=0, column=0, padx=10, pady=5, sticky="w")
    eta_max_entry.grid(row=0, column=3, padx=10, pady=5, sticky="w")

    lambda_min_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Lambda min [{Lambda_Min_Default}]"
    )
    lambda_max_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Lambda max [{Lambda_Max_Default}]"
    )

    lambda_min_entry.grid(row=1, column=0, padx=10, pady=5, sticky="w")
    lambda_max_entry.grid(row=1, column=3, padx=10, pady=5, sticky="w")

    alpha_min_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Alpha min [{Alpha_Min_Default}]"
    )
    alpha_max_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Alpha max [{Alpha_Max_Default}]"
    )

    alpha_min_entry.grid(row=2, column=0, padx=10, pady=5, sticky="w")
    alpha_max_entry.grid(row=2, column=3, padx=10, pady=5, sticky="w")

    steps_eta_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Eta steps [{Step1_Default}]"
    )
    steps_lambda_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Lambda steps [{Step2_Default}]"
    )
    steps_alpha_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Alpha steps [{Step3_Default}]"
    )
    training_steps_entry = ctk.CTkEntry(
        grid_tab, placeholder_text=f"Epochs [{Training_Steps_Default}]"
    )

    steps_eta_entry.grid(row=3, column=0, padx=10, pady=5, sticky="w")
    steps_lambda_entry.grid(row=3, column=3, padx=10, pady=5, sticky="w")
    steps_alpha_entry.grid(row=4, column=0, padx=10, pady=5, sticky="w")
    training_steps_entry.grid(row=4, column=3, padx=10, pady=5, sticky="w")

    done_button = ctk.CTkButton(grid_tab, text="Run Grid Search", command=submit_values)
    done_button.grid(row=5, column=0, columnspan=2, pady=20)

    recompile_button = ctk.CTkButton(grid_tab, text="Recompile", command=Compile)
    recompile_button.grid(row=5, column=2, columnspan=2, pady=20)

    # Single Run Tab UI
    single_eta_entry = ctk.CTkEntry(
        single_run_tab, placeholder_text=f"Eta [{Eta_single}]"
    )
    single_lambda_entry = ctk.CTkEntry(
        single_run_tab, placeholder_text=f"Lambda [{Lambda_single}]"
    )
    single_alpha_entry = ctk.CTkEntry(
        single_run_tab, placeholder_text=f"Alpha [{Alpha_single}]"
    )
    single_training_steps_entry = ctk.CTkEntry(
        single_run_tab, placeholder_text=f"Epochs [{Training_Steps_Default}]"
    )

    single_eta_entry.grid(row=0, column=0, padx=10, pady=5, sticky="w")
    single_lambda_entry.grid(row=0, column=3, padx=10, pady=5, sticky="w")
    single_alpha_entry.grid(row=1, column=0, padx=10, pady=5, sticky="w")
    single_training_steps_entry.grid(row=1, column=3, padx=10, pady=5, sticky="w")

    checkbox = ctk.CTkCheckBox(
        master=single_run_tab, text="Show plot", command=show_plot
    )
    checkbox.grid(row=5, column=0, pady=15, padx=10, sticky="w")

    done_button_single = ctk.CTkButton(
        single_run_tab,
        text="Run Single Training",
        command=submit_values_for_single_training,
    )
    done_button_single.grid(row=10, column=0, columnspan=2, pady=20)

    recompile_button_single = ctk.CTkButton(
        single_run_tab, text="Recompile", command=Compile
    )
    recompile_button_single.grid(row=10, column=2, columnspan=2, pady=20)

    logger.info("GUI setup complete, starting main loop")
    root.lift()
    root.mainloop()
    logger.info("Application closed")


# %%
