import sys

def StringPainter(color, string): 
    if color == 'blue': 
        special_opener = "\033[94m"
        special_closer = "\033[0m"
    if color == 'red': 
        special_opener = ''
    elif(): 
        print("Color unavailable...")
    painted_string = special_opener + string + special_closer
    return painted_string
        

def main():
    list = ""

    questions = [ #raws questions: pure strings; 
    "How to perform a Backpropagation?", 
    "How to add an hidden layer?", 
    ]

    answers = [ #raws answers; 
    f'After passing {StringPainter('blue', 'true')} to the last hidden, call the method with -your_hidden_name-\033[94m.Backpropagation()\033[0m.',
    f'Test for {StringPainter('blue', 'painter')}', 
    ]

    if len(sys.argv) == 1: #No parameter passed; 
        for q in questions:
            q = "\n " + f"{questions.index(q)+1}. " + q #formatting strings in a certain way; 
            list += q
        print(f"\nHi welcome! I'll be your guide during this journey; try asking these questions: {list}\n")
        print("Note: ask question typing its number after\033[94m python info.py \033[0min the terminal.\n")

    else: #passed parameter; 
        parametro = sys.argv[1]
        parametro = int(parametro) 
        if parametro <= len(questions):
            print("\n" + answers[parametro - 1] + "\n")
        else:
            print(f"\nNumber {parametro} does not correspond to any question.\n")

if __name__ == "__main__":
    main()
