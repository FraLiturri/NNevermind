import sys

questions = [
    "\n 1. How to perform a Backpropagation?", 
    "\n 2. How to add an hidden layer?", 
]

answers = [
    '\n After passing\033[94m true \033[0mto the last hidden, call the method with -your_hidden_name-\033[94m .Backpropagation() \033[0m ',
]

def main():
    list = ""
    if len(sys.argv) == 1: #No parameter passed; 
        for q in questions:
            list += q
        print(f"\nHi welcome! I'll we your guide during this journey; try asking these questions: {list} \n")
        print("Note: ask questions once and typing it's number after\033[94m python info.py \033[0min the terminal. \n")
    else: #passed parameter; 
        parametro = sys.argv[1]
        parametro = int(parametro) 
        if parametro <= len(questions):
            print(answers[parametro-1])
        else:
            print(f"Il parametro '{parametro}' non è riconosciuto.")

if __name__ == "__main__":
    main()
