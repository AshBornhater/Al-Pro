#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Pixel {
    int red, green, blue;
};

struct Image {
    int width, height;
    vector<vector<Pixel>> pixels;
};

// Inisialisasi gambar kosong
Image createImage(int width, int height) {
    Image image;
    image.width = width;
    image.height = height;
    image.pixels.assign(height, vector<Pixel>(width, {0, 0, 0}));
    return image;
}

// Membatasi nilai warna agar tetap berada di rentang 0-255
int clamp(int value, int minValue, int maxValue) {
    if (value < minValue) return minValue;
    if (value > maxValue) return maxValue;
    return value;
}

// Membaca File PPM
Image readPPM(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: File '" << filename << "' tidak ditemukan!" << endl;
        exit(1); 
    }

    string formatType;
    int width, height, maxColorValue;
    file >> formatType >> width >> height >> maxColorValue;

    if (formatType != "P3") {
        cout << "ERROR: Format bukan P3 PPM!" << endl;
        exit(1);
    }

    Image image = createImage(width, height);
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            file >> image.pixels[row][column].red 
                 >> image.pixels[row][column].green 
                 >> image.pixels[row][column].blue;
        }
    }
    file.close();
    return image;
}

// Menulis File PPM
void writePPM(const string& filename, const Image& image) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Gagal membuat file output '" << filename << "'" << endl;
        return;
    }

    file << "P3\n" << image.width << " " << image.height << "\n255\n";

    for (int row = 0; row < image.height; row++) {
        for (int column = 0; column < image.width; column++) {
            file << image.pixels[row][column].red << " " 
                 << image.pixels[row][column].green << " " 
                 << image.pixels[row][column].blue << "  ";
        }
        file << "\n";
    }
    file.close();
}

// Algoritma Grayscale
Image applyGrayscale(const Image& source) {
    Image destination = createImage(source.width, source.height);
    for (int row = 0; row < source.height; row++) {
        for (int column = 0; column < source.width; column++) {
            const Pixel& pixel = source.pixels[row][column];
            int grayValue = static_cast<int>(0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue);
            destination.pixels[row][column] = {grayValue, grayValue, grayValue};
        }
    }
    return destination;
}

// Algoritma Gaussian Blur (Konvolusi 5x5)
Image applyGaussianBlur(const Image& source) {
    const int kernel[5][5] = {
        { 1,  4,  6,  4,  1},
        { 4, 16, 24, 16,  4},
        { 6, 24, 36, 24,  6},
        { 4, 16, 24, 16,  4},
        { 1,  4,  6,  4,  1}
    };

    Image destination = createImage(source.width, source.height);
    for (int row = 0; row < source.height; row++) {
        for (int column = 0; column < source.width; column++) {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            
            for (int kernelRow = -2; kernelRow <= 2; kernelRow++) {
                for (int kernelColumn = -2; kernelColumn <= 2; kernelColumn++) {
                    int neighborRow = clamp(row + kernelRow, 0, source.height - 1);
                    int neighborColumn = clamp(column + kernelColumn, 0, source.width - 1);
                    int weight = kernel[kernelRow + 2][kernelColumn + 2];

                    sumRed += weight * source.pixels[neighborRow][neighborColumn].red;
                    sumGreen += weight * source.pixels[neighborRow][neighborColumn].green;
                    sumBlue += weight * source.pixels[neighborRow][neighborColumn].blue;
                }
            }
            destination.pixels[row][column] = {sumRed / 256, sumGreen / 256, sumBlue / 256};
        }
    }
    return destination;
}

int main() {
    string inputFileName = "oasis.ppm";

    cout << "[PROSES] Membaca file: " << inputFileName << "..." << endl;
    Image originalImage = readPPM(inputFileName);

    cout << "[PROSES] Menerapkan Grayscale..." << endl;
    Image grayscaleImage = applyGrayscale(originalImage);

    cout << "[PROSES] Menerapkan Gaussian Blur..." << endl;
    Image blurredImage = applyGaussianBlur(grayscaleImage);

    cout << "[PROSES] Menyimpan hasil..." << endl;
    writePPM("outputGrayscale.ppm", grayscaleImage);
    writePPM("outputBlur.ppm", blurredImage);

    cout << "Selesai! Gambar berhasil diproses." << endl;

    return 0;
}