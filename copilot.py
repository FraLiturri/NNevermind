# %%
import sys
import python.info as info
import python.analyzer as analyzer
import python.initializer as initializer
import NN.grid_search as grid_search


def main():

    if len(sys.argv) == 1:
        print(
            "\nHi welcome! I'll be your guide during this journey. Here there's a list of commands: \n \n"
            f" 1. {info.StringPainter("blue", "help")}: to show a list of questions about code implementation. \n"
            f" 2. {info.StringPainter("blue", "iterate file_path N")}: to iterate the execution of a .exe file N times. \n"
        )

    elif (
        str(sys.argv[1]) == "initialize"
    ):  # C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"
        Eigen_path = str(input("\nInsert Eigen path here: "))
        initializer.create_hpp_file("NN/eigen_path.hpp", Eigen_path)

    elif str(sys.argv[1]) == "help":  # No parameter passed;
        for q in info.questions:
            q = (
                "\n " + f"{info.questions.index(q)+1}. " + q
            )  # formatting strings in a certain way;
            info.questions_list += q
        print(
            f"\nHi welcome! I'll be your guide during this journey; try asking these questions: {info.questions_list}\n"
        )
        print(
            f"Note: ask question typing its number after\033[94m python info.py \033[0min the terminal. If you want to get general info type {info.StringPainter('blue', '0')}. \n"
        )

    elif str(sys.argv[1]) == "plot":
        analyzer.plot()

    else:  # Passed parameter;
        parametro = int(sys.argv[1])
        if parametro == 0:
            print(f"\n{info.guide}\n")
        elif parametro <= len(info.questions):
            print("\n" + info.answers[parametro - 1] + "\n")
        else:
            print(f"\nNumber {parametro} does not correspond to any question.\n")


if __name__ == "__main__":
    main()
