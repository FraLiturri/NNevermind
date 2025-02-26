#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

std::mutex file_mutex;

// Funzione che scrive sul file
void writeToFileSafely(const std::string& filename, const std::string& message) {
    std::lock_guard<std::mutex> lock(file_mutex); // Blocco thread-safe
    std::ofstream file(filename, std::ios::app); // Apri in modalità append
    if (file.is_open()) {
        file << message << "\n";
    } else {
        std::cerr << "Errore nell'apertura del file." << std::endl;
    }
}