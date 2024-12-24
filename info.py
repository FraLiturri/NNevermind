import sys


def StringPainter(color, string):  # Transforms a string in a colored one;
    if color == "blue":
        special_opener = "\033[94m"
        special_closer = "\033[0m"
    if color == "orange":
        special_opener = "\033[36m"
        special_closer = "\033[0m"
    elif ():
        print("Color unavailable...")
    painted_string = special_opener + string + special_closer
    return painted_string


guide = "..."


def main():
    questions_list = ""

    questions = [  # raws questions: pure strings;
        "How to perform a Backpropagation?",
        "How to add an hidden layer?",
        "What does hidden_layer class take in input?",
        "How to perform a Random Training?",
        "Which activatiion functions are available?",
        "Which loss functions are available? "
    ]

    answers = [  # answers;
        f"After passing {StringPainter('blue', 'true')} to the last hidden, call the method with -your_last_hidden_name-\033[94m.Backpropagation()\033[0m.",
        f"Test for {StringPainter('orange', 'painter')}",
        f"Hidden_layer class takes 3 arugments: a {StringPainter('blue', 'string')} (in lowercase format) corresponding to the layer's activation function (currently are available linear, relu and sigmoid), "
        + f"an {StringPainter('blue', 'int')} (depth) equal to the hidden layer's number and a {StringPainter('blue', 'bool')} (setted to false by default) to indicate if it's the output layer.",
        f"After passing {StringPainter('blue', 'true')} to the last hidden, call the method with -your_last_hidden_name-\033[94m.RandomTraining()\033[0m.",
        f"You can choose between: \n • linear \n • relu \n • sigmoid \n • threshold" ,
        "For now are available \n • MSE (mean square error) \n • BCE (binary cross entropy)"
    ]

    if len(sys.argv) == 1:  # No parameter passed;
        for q in questions:
            q = (
                "\n " + f"{questions.index(q)+1}. " + q
            )  # formatting strings in a certain way;
            questions_list += q
        print(
            f"\nHi welcome! I'll be your guide during this journey; try asking these questions: {questions_list}\n"
        )
        print(
            f"Note: ask question typing its number after\033[94m python info.py \033[0min the terminal. If you want to get general info type {StringPainter('blue', '0')}. \n"
        )

    else:  # Passed parameter;
        parametro = int(sys.argv[1])
        if parametro == 0:
            print(f"\n{guide}\n")
        elif parametro <= len(questions):
            print("\n" + answers[parametro - 1] + "\n")
        else:
            print(f"\nNumber {parametro} does not correspond to any question.\n")


if __name__ == "__main__":
    main()
