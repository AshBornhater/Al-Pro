#include <iostream>

int main() {
    // \033[2J  -> Menghapus seluruh layar
    // \033[H   -> Memindahkan kursor ke pojok kiri atas (baris 1, kolom 1)
    std::cout << "Start small. Ship something.\n";
    std::cout << "\033[2J\033[H";

    std::cout << "Layar telah dibersihkan dan kursor di atas!" << std::endl;

    return 0;
}