#include <iostream>

int main() {
    const int W = 40, H = 20;
    const int N = 15;          // jumlah meteor

    int mx[N], my[N], mlen[N]; // posisi & panjang ekor
    const char tail[] = "*+:. ";

    // inisialisasi meteor di posisi acak-deterministik
    for (int i = 0; i < N; i++) {
        mx[i]   = (i * 7 + 3) % W;
        my[i]   = -(i * 4);        // mulai di atas layar
        mlen[i] = 3 + (i % 3);
    }

    while (true) {
        std::cout << "\033[H";

        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {

                char c = ' ';
                for (int i = 0; i < N; i++) {
                    if (mx[i] != x) continue;
                    int dist = my[i] - y;      // jarak dari kepala
                    if (dist >= 0 && dist < mlen[i])
                        c = tail[dist];
                }
                std::cout << c;
            }
            std::cout << '\n';
        }

        std::cout.flush();
        for (volatile long i = 0; i < 2'500'000; i++);

        // gerakkan meteor ke bawah, reset jika keluar layar
        for (int i = 0; i < N; i++) {
            my[i]++;
            if (my[i] > H + mlen[i]) {
                my[i] = -((i * 5 + 2) % 10);
                mx[i] = (mx[i] + 13) % W; // geser kolom
            }
        }
    }
}