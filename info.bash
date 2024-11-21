crea_stringa() {
    local nome=$1
    echo "Ciao $nome, benvenuto nello script Bash!"
}

# Esempio di utilizzo
stringa=$(crea_stringa "Utente")
echo "$stringa"