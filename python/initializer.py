import sys

def create_hpp_file(file_name, include_path):
    try:
        # Apri il file in modalità scrittura
        with open(file_name, "w") as file:
            # Scrivi la direttiva #include con il percorso specificato
            file.write(f'#include "{include_path}"\n')
        print(f"\nPath added to '{file_name}' successfully!\n")
    except Exception as e:
        print(f"Error: {e}")
    
