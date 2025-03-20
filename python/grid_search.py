import os
import sys
import multiprocessing as mp
import subprocess
from dataclasses import dataclass
from typing import List, Tuple
from loguru import logger
from tkinter import messagebox

import customtkinter as ctk

# Add the path for importing the parameters module
sys.path.append(
    os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "include"))
)
import parameters as param

# Configure the logger with improved settings
def configure_logger():
    """Configure the logger with enhanced settings and formatting."""
    # Remove default handlers
    logger.remove()
    
    # Add a console handler with improved formatting
    logger.add(
        sys.stderr,
        format="<green>{time:HH:mm:ss}</green> | <level>{level: <8}</level> | <cyan>{name}</cyan>:<cyan>{function}</cyan>:<cyan>{line}</cyan> - <level>{message}</level>",
        level="INFO",
        colorize=True,
        backtrace=True,
        diagnose=True,
        enqueue=True,  # Thread-safe logging
    )
    
    # Add a file handler for persistent logs
    log_dir = "logs"
    os.makedirs(log_dir, exist_ok=True)
    logger.add(
        os.path.join(log_dir, "neural_network_trainer_{time}.log"),
        rotation="10 MB",
        retention="1 week",
        compression="zip",
        level="DEBUG",
        format="{time:YYYY-MM-DD HH:mm:ss} | {level: <8} | {name}:{function}:{line} - {message}",
    )

# Constants
FILE_TO_COMPILE = "main.cpp"
EXECUTABLE_PATH = "build/main.exe"
RESULTS_FILE = "results/grid_results.txt"
PLOT_SCRIPT = "copilot.py"


# Default values for grid search
@dataclass
class DefaultValues:
    # Grid search
    ETA_MIN = 0.01
    ETA_MAX = 0.1
    LAMBDA_MIN = 0.0
    LAMBDA_MAX = 0.0
    ALPHA_MIN = 0.0
    ALPHA_MAX = 0.0
    STEP_ETA = 10
    STEP_LAMBDA = 1
    STEP_ALPHA = 1
    TRAINING_STEPS = 1000

    # Single run
    ETA_SINGLE = 0.01
    LAMBDA_SINGLE = 0.0
    ALPHA_SINGLE = 0.0

# Funzione helper per il multiprocessing
def call_main_helper(inputs: List[float]) -> str:
    """Helper function to execute the compiled program with the provided parameters."""
    command = [EXECUTABLE_PATH] + [str(x) for x in inputs]
    result = subprocess.run(command, capture_output=True, text=True)
    return result.stdout


class NeuralNetworkTrainer:
    def __init__(self):
        self.is_compilation_successful = False
        self.counter = 0
        self.show_plot_enabled = False
        self.cpu_count = os.cpu_count()
        self.defaults = DefaultValues()
        self.logger = logger.bind(context="NeuralNetworkTrainer")

    def toggle_plot(self):
        self.show_plot_enabled = not self.show_plot_enabled
        self.logger.debug(f"Plot display toggled to: {self.show_plot_enabled}")
        return self.show_plot_enabled

    def show_plot(self):
        if self.show_plot_enabled:
            self.logger.info("Displaying plot...")
            subprocess.run(["python", PLOT_SCRIPT, "plot"])

    def compile(self) -> bool:
        """Compiles the source file and returns True if compilation was successful."""
        try:
            self.logger.info("Compilation in progress... please wait.")
            result = subprocess.run(
                ["g++", "-fopenmp", "-O3", "-o", EXECUTABLE_PATH, FILE_TO_COMPILE],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                check=True,
            )
            self.logger.success("Compilation completed successfully!")
            self.logger.debug(f"Compilation output: {result.stdout}")
            self.is_compilation_successful = True
            return True
        except FileNotFoundError:
            self.logger.error(f"Fatal error: {FILE_TO_COMPILE} not found.", exc_info=True)
            messagebox.showerror("Error", f"File {FILE_TO_COMPILE} not found.")
            self.is_compilation_successful = False
            return False
        except subprocess.CalledProcessError as e:
            self.logger.error("Fatal error: compilation failed.", exc_info=True)
            messagebox.showerror(
                "Error",
                "Compilation failed. Check the terminal for details.",
            )
            self.logger.error(f"Error details: {e.stderr}")
            self.is_compilation_successful = False
            return False

    def call_main(self, inputs: List[float]) -> str:
        """Executes the compiled program with the provided parameters."""
        command = [EXECUTABLE_PATH] + [str(x) for x in inputs]
        self.logger.debug(f"Executing command: {' '.join(command)}")
        result = subprocess.run(command, capture_output=True, text=True)
        if result.returncode != 0:
            self.logger.warning(f"Program returned non-zero exit code: {result.returncode}")
            self.logger.warning(f"Error output: {result.stderr}")
        return result.stdout

    def build_grid(
        self,
        eta_min: float,
        eta_max: float,
        lambda_min: float,
        lambda_max: float,
        alpha_min: float,
        alpha_max: float,
        step_eta: int,
        step_lambda: int,
        step_alpha: int,
    ) -> param.Grid:
        """Creates a grid of parameters for searching."""
        self.logger.debug(
            f"Building grid: eta=[{eta_min}-{eta_max}], lambda=[{lambda_min}-{lambda_max}], "
            f"alpha=[{alpha_min}-{alpha_max}], steps=[{step_eta},{step_lambda},{step_alpha}]"
        )
        return param.Grid(
            eta_min,
            eta_max,
            lambda_min,
            lambda_max,
            alpha_min,
            alpha_max,
            step_eta,
            step_lambda,
            step_alpha,
        )

    def clear_results_file(self):
        """Removes the previous results file."""
        try:
            if os.path.exists(RESULTS_FILE):
                self.logger.debug(f"Removing previous results file: {RESULTS_FILE}")
                os.remove(RESULTS_FILE)
            else:
                self.logger.debug(f"Results file doesn't exist: {RESULTS_FILE}")
                
            # Ensure the directory exists
            results_dir = os.path.dirname(RESULTS_FILE)
            if not os.path.exists(results_dir):
                self.logger.debug(f"Creating results directory: {results_dir}")
                os.makedirs(results_dir, exist_ok=True)
        except Exception as e:
            self.logger.warning(f"Unable to manage results file: {e}", exc_info=True)

    def run_grid_search(self, params: dict) -> bool:
        """Executes a grid search with the specified parameters."""
        if not self.is_compilation_successful:
            self.logger.error("Compilation failed. Unable to execute grid search.")
            return False

        self.logger.info("Grid search execution in progress...")
        self.clear_results_file()

        try:
            # Creating the parameter grid
            grid = self.build_grid(
                params.get("eta_min", self.defaults.ETA_MIN),
                params.get("eta_max", self.defaults.ETA_MAX),
                params.get("lambda_min", self.defaults.LAMBDA_MIN),
                params.get("lambda_max", self.defaults.LAMBDA_MAX),
                params.get("alpha_min", self.defaults.ALPHA_MIN),
                params.get("alpha_max", self.defaults.ALPHA_MAX),
                params.get("step_eta", self.defaults.STEP_ETA),
                params.get("step_lambda", self.defaults.STEP_LAMBDA),
                params.get("step_alpha", self.defaults.STEP_ALPHA),
            )

            # Preparing inputs for parallel execution
            inputs = [
                [
                    point.Eta,
                    point.Lambda,
                    point.Alpha,
                    params.get("training_steps", self.defaults.TRAINING_STEPS),
                ]
                for point in grid.Grid
            ]

            # Parallel execution
            total_points = len(inputs)
            self.logger.info(f"Starting {total_points} processes on {self.cpu_count} CPUs")
            self.logger.debug(f"Grid search parameters: {params}")
            
            with mp.Pool(processes=self.cpu_count) as pool:
                self.logger.debug("Pool created, starting tasks...")
                # Usa la funzione helper esterna invece di self.call_main
                results = pool.map(call_main_helper, inputs)
                self.logger.debug("All tasks completed")
                print(results)
                
            self.logger.success(f"Grid search completed successfully! Processed {total_points} parameter combinations.")
            return True
        except Exception as e:
            self.logger.error(f"Error during grid search: {e}", exc_info=True)
            return False

    def run_single_training(self, params: dict) -> bool:
        """Executes a single training with the specified parameters."""
        if not self.is_compilation_successful:
            self.logger.error("Compilation failed. Unable to execute training.")
            return False

        self.clear_results_file()

        try:
            inputs = [
                params.get("eta", self.defaults.ETA_SINGLE),
                params.get("lambda", self.defaults.LAMBDA_SINGLE),
                params.get("alpha", self.defaults.ALPHA_SINGLE),
                params.get("training_steps", self.defaults.TRAINING_STEPS),
            ]

            self.counter += 1
            self.logger.info(f"Executing run #{self.counter}")
            self.logger.debug(f"Parameters: eta={inputs[0]}, lambda={inputs[1]}, alpha={inputs[2]}, steps={inputs[3]}")

            output = self.call_main(inputs)
            print(output)

            self.show_plot()
            self.logger.success(f"Single training run #{self.counter} completed successfully!")
            return True
        except Exception as e:
            self.logger.error(f"Error during single training: {e}", exc_info=True)
            return False


class TrainerGUI:
    def __init__(self, trainer: NeuralNetworkTrainer):
        self.trainer = trainer
        self.logger = logger.bind(context="TrainerGUI")

        # Configure the GUI
        ctk.set_appearance_mode("Dark")
        ctk.set_default_color_theme("blue")

        self.root = ctk.CTk()
        self.root.title("Neural Network Trainer")
        self.root.wm_attributes("-topmost", True)

        self.create_ui()

    def create_ui(self):
        """Creates the user interface."""
        self.logger.debug("Creating user interface components")
        # Tab view
        self.tab_view = ctk.CTkTabview(self.root)
        self.tab_view.pack(expand=True, fill="both", padx=20, pady=20)

        # Tab for grid search
        self.grid_tab = self.tab_view.add("Grid Search")
        self.create_grid_search_tab()

        # Tab for single training
        self.single_run_tab = self.tab_view.add("Single Run")
        self.create_single_run_tab()
        self.logger.debug("UI components created successfully")

    def create_grid_search_tab(self):
        """Creates the tab for grid search."""
        # Fields for Eta parameters
        self.eta_min_entry = ctk.CTkEntry(
            self.grid_tab, placeholder_text=f"Eta min [{self.trainer.defaults.ETA_MIN}]"
        )
        self.eta_max_entry = ctk.CTkEntry(
            self.grid_tab, placeholder_text=f"Eta max [{self.trainer.defaults.ETA_MAX}]"
        )
        self.eta_min_entry.grid(row=0, column=0, padx=10, pady=5, sticky="w")
        self.eta_max_entry.grid(row=0, column=3, padx=10, pady=5, sticky="w")

        # Fields for Lambda parameters
        self.lambda_min_entry = ctk.CTkEntry(
            self.grid_tab,
            placeholder_text=f"Lambda min [{self.trainer.defaults.LAMBDA_MIN}]",
        )
        self.lambda_max_entry = ctk.CTkEntry(
            self.grid_tab,
            placeholder_text=f"Lambda max [{self.trainer.defaults.LAMBDA_MAX}]",
        )
        self.lambda_min_entry.grid(row=1, column=0, padx=10, pady=5, sticky="w")
        self.lambda_max_entry.grid(row=1, column=3, padx=10, pady=5, sticky="w")

        # Fields for Alpha parameters
        self.alpha_min_entry = ctk.CTkEntry(
            self.grid_tab,
            placeholder_text=f"Alpha min [{self.trainer.defaults.ALPHA_MIN}]",
        )
        self.alpha_max_entry = ctk.CTkEntry(
            self.grid_tab,
            placeholder_text=f"Alpha max [{self.trainer.defaults.ALPHA_MAX}]",
        )
        self.alpha_min_entry.grid(row=2, column=0, padx=10, pady=5, sticky="w")
        self.alpha_max_entry.grid(row=2, column=3, padx=10, pady=5, sticky="w")

        # Fields for search steps and number of epochs
        self.steps_eta_entry = ctk.CTkEntry(
            self.grid_tab,
            placeholder_text=f"Eta steps [{self.trainer.defaults.STEP_ETA}]",
        )
        self.steps_lambda_entry = ctk.CTkEntry(
            self.grid_tab,
            placeholder_text=f"Lambda steps [{self.trainer.defaults.STEP_LAMBDA}]",
        )
        self.steps_alpha_entry = ctk.CTkEntry(
            self.grid_tab,
            placeholder_text=f"Alpha steps [{self.trainer.defaults.STEP_ALPHA}]",
        )
        self.training_steps_entry = ctk.CTkEntry(
            self.grid_tab,
            placeholder_text=f"Epochs [{self.trainer.defaults.TRAINING_STEPS}]",
        )
        self.steps_eta_entry.grid(row=3, column=0, padx=10, pady=5, sticky="w")
        self.steps_lambda_entry.grid(row=3, column=3, padx=10, pady=5, sticky="w")
        self.steps_alpha_entry.grid(row=4, column=0, padx=10, pady=5, sticky="w")
        self.training_steps_entry.grid(row=4, column=3, padx=10, pady=5, sticky="w")

        # Buttons
        self.run_button = ctk.CTkButton(
            self.grid_tab, text="Run", command=self.submit_grid_search
        )
        self.run_button.grid(row=5, column=0, columnspan=2, pady=20)

        self.recompile_button = ctk.CTkButton(
            self.grid_tab, text="Recompile", command=self.trainer.compile
        )
        self.recompile_button.grid(row=5, column=2, columnspan=2, pady=20)

    def create_single_run_tab(self):
        """Creates the tab for single training."""
        # Fields for parameters
        self.single_eta_entry = ctk.CTkEntry(
            self.single_run_tab,
            placeholder_text=f"Eta [{self.trainer.defaults.ETA_SINGLE}]",
        )
        self.single_lambda_entry = ctk.CTkEntry(
            self.single_run_tab,
            placeholder_text=f"Lambda [{self.trainer.defaults.LAMBDA_SINGLE}]",
        )
        self.single_alpha_entry = ctk.CTkEntry(
            self.single_run_tab,
            placeholder_text=f"Alpha [{self.trainer.defaults.ALPHA_SINGLE}]",
        )
        self.single_training_steps_entry = ctk.CTkEntry(
            self.single_run_tab,
            placeholder_text=f"Epochs [{self.trainer.defaults.TRAINING_STEPS}]",
        )

        self.single_eta_entry.grid(row=0, column=0, padx=10, pady=5, sticky="w")
        self.single_lambda_entry.grid(row=0, column=3, padx=10, pady=5, sticky="w")
        self.single_alpha_entry.grid(row=1, column=0, padx=10, pady=5, sticky="w")
        self.single_training_steps_entry.grid(
            row=1, column=3, padx=10, pady=5, sticky="w"
        )

        # Checkbox for showing the plot
        self.plot_checkbox = ctk.CTkCheckBox(
            self.single_run_tab,
            border_width=2,
            hover=False,
            text="Show plot",
            command=self.trainer.toggle_plot,
        )
        self.plot_checkbox.grid(row=10, column=0, sticky="w", pady=20, padx=10)

        # Buttons
        self.run_button_single = ctk.CTkButton(
            self.single_run_tab, text="Run", command=self.submit_single_run
        )
        self.run_button_single.grid(row=15, column=0, columnspan=2, pady=10)

        self.recompile_button_single = ctk.CTkButton(
            self.single_run_tab, text="Recompile", command=self.trainer.compile
        )
        self.recompile_button_single.grid(row=15, column=2, columnspan=2, pady=10)

    def get_grid_params(self) -> dict:
        """Gets the parameters for grid search from entries."""
        params = {}
        try:
            # Eta
            if self.eta_min_entry.get():
                params["eta_min"] = float(self.eta_min_entry.get())
            if self.eta_max_entry.get():
                params["eta_max"] = float(self.eta_max_entry.get())

            # Lambda
            if self.lambda_min_entry.get():
                params["lambda_min"] = float(self.lambda_min_entry.get())
            if self.lambda_max_entry.get():
                params["lambda_max"] = float(self.lambda_max_entry.get())

            # Alpha
            if self.alpha_min_entry.get():
                params["alpha_min"] = float(self.alpha_min_entry.get())
            if self.alpha_max_entry.get():
                params["alpha_max"] = float(self.alpha_max_entry.get())

            # Steps
            if self.steps_eta_entry.get():
                params["step_eta"] = int(self.steps_eta_entry.get())
            if self.steps_lambda_entry.get():
                params["step_lambda"] = int(self.steps_lambda_entry.get())
            if self.steps_alpha_entry.get():
                params["step_alpha"] = int(self.steps_alpha_entry.get())

            # Training steps
            if self.training_steps_entry.get():
                params["training_steps"] = int(self.training_steps_entry.get())

            # Validation
            if (
                "eta_min" in params
                and "eta_max" in params
                and params["eta_min"] > params["eta_max"]
            ):
                raise ValueError("Eta min must be less than or equal to Eta max")
            if (
                "lambda_min" in params
                and "lambda_max" in params
                and params["lambda_min"] > params["lambda_max"]
            ):
                raise ValueError("Lambda min must be less than or equal to Lambda max")
            if (
                "alpha_min" in params
                and "alpha_max" in params
                and params["alpha_min"] > params["alpha_max"]
            ):
                raise ValueError("Alpha min must be less than or equal to Alpha max")
            if "step_eta" in params and params["step_eta"] <= 0:
                raise ValueError("Eta steps must be greater than zero")
            if "step_lambda" in params and params["step_lambda"] <= 0:
                raise ValueError("Lambda steps must be greater than zero")
            if "step_alpha" in params and params["step_alpha"] <= 0:
                raise ValueError("Alpha steps must be greater than zero")
            if "training_steps" in params and params["training_steps"] < 0:
                raise ValueError("Epochs must be greater than or equal to zero")

            self.logger.debug(f"Grid parameters validated: {params}")
            return params
        except ValueError as e:
            self.logger.error(f"Parameter validation error: {str(e)}")
            messagebox.showerror("Error", str(e))
            return None

    def get_single_run_params(self) -> dict:
        """Gets the parameters for single training from entries."""
        params = {}
        try:
            # Eta
            if self.single_eta_entry.get():
                params["eta"] = float(self.single_eta_entry.get())
                if params["eta"] < 0:
                    raise ValueError("Eta must be greater than or equal to zero")

            # Lambda
            if self.single_lambda_entry.get():
                params["lambda"] = float(self.single_lambda_entry.get())

            # Alpha
            if self.single_alpha_entry.get():
                params["alpha"] = float(self.single_alpha_entry.get())

            # Training steps
            if self.single_training_steps_entry.get():
                params["training_steps"] = int(self.single_training_steps_entry.get())
                if params["training_steps"] < 0:
                    raise ValueError("Epochs must be greater than or equal to zero")

            self.logger.debug(f"Single run parameters validated: {params}")
            return params
        except ValueError as e:
            self.logger.error(f"Parameter validation error: {str(e)}")
            messagebox.showerror("Error", str(e))
            return None

    def submit_grid_search(self):
        """Executes the grid search with the entered parameters."""
        self.logger.info("Grid search requested")
        params = self.get_grid_params()
        if params is not None:
            self.trainer.run_grid_search(params)

    def submit_single_run(self):
        """Executes the single training with the entered parameters."""
        self.logger.info("Single run requested")
        params = self.get_single_run_params()
        if params is not None:
            self.trainer.run_single_training(params)

    def run(self):
        """Starts the user interface."""
        # Compile the code at startup
        self.logger.info("Starting the application")
        self.trainer.compile()

        # Start the main loop
        self.logger.info("Starting main UI loop")
        self.root.mainloop()


# Main function
def grid_search():
    # Configure the logger
    configure_logger()

    logger.info("Neural Network Trainer application starting")
    logger.debug(f"Python version: {sys.version}")
    logger.debug(f"Operating system: {os.name} - {sys.platform}")

    # Create the trainer instance
    trainer = NeuralNetworkTrainer()

    # Create and start the graphical interface
    gui = TrainerGUI(trainer)
    gui.run()


if __name__ == "__main__":
    grid_search()