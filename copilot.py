# %%
import sys
import python.analyzer as analyzer
import python.initializer as initializer
import python.grid_search as grid_search

def main():

    if len(sys.argv) == 1:
        print(
            "\nHi welcome! I'll be your guide during this journey. Here there's a list of commands: \n"
            "• Type\033[94m python copilot.py change_path\033[0m to update or change Eigen's path; \n"
            "• Type\033[94m python copilot.py plot\033[0m to show the results of training and validation process; \n"
            "• Type\033[94m python copilot.py search\033[0m to start a grid search over hyperparameters. \n"
        )

    elif str(sys.argv[1]) == "change_path":
        try:
            Eigen_path = str(input("\nInsert your Eigen's path here: "))
            initializer.create_hpp_file("include/eigen_path.hpp", Eigen_path)
        except EOFError:
            print("no data provided to input function")

    elif str(sys.argv[1]) == "plot":
        analyzer.plot()

    elif str(sys.argv[1]) == "search":
        grid_search.grid_search()

    else:
        print(
            "\nInvalid argument passed: please run\033[94m python copilot.py\033[0m to see the list of commands.\n"
        )


if __name__ == "__main__":
    main()

# %%
