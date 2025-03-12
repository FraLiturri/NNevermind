# %%
import sys
import python.analyzer as analyzer
import python.initializer as initializer
#import include.parameters as param
import python.grid_search as grid_search


def main():

    if len(sys.argv) == 1:
        print(
            "\nHi welcome! I'll be your guide during this journey. Here there's a list of commands: \n"
        )

    elif str(sys.argv[1]) == "change_path":
        Eigen_path = str(input("\nInsert your Eigen's path here: "))
        initializer.create_hpp_file("include/eigen_path.hpp", Eigen_path)

    elif str(sys.argv[1]) == "plot":
        analyzer.plot()


if __name__ == "__main__":
    main()
