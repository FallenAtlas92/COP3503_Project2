#include <iostream>
#include <fstream>
#include "TGH.h"

using namespace std;

unsigned char MultiplyChannels(unsigned char top, unsigned char bottom) {
    // normalize both to 0-1, multiply them, scale back to 255, and round
    float result = ((top / 255.0f) * (bottom / 255.0f)) * 255.0f + 0.5f;
    return static_cast<unsigned char>(result);
}

unsigned char SubtractChannels(unsigned char top, unsigned char bottom) {
    int result = static_cast<int>(bottom) - static_cast<int>(top);
    if (result < 0) {
        result = 0;
    }
    return static_cast<unsigned char>(result);
}

int main() {
    
    // --- Task 1: Multiply Blend ---
    {
        Image layer1;
        Image pattern1;

        if (!layer1.Load("input/layer1.tga") || !pattern1.Load("input/pattern1.tga")) {
            cout << "Error: Could not load input files for Task 1!" << endl;
            return 1;
        }

        Image outputImage = layer1;

        for (size_t i = 0; i < layer1.pixels.size(); ++i) {
            outputImage.pixels[i].red = MultiplyChannels(layer1.pixels[i].red, pattern1.pixels[i].red);
            outputImage.pixels[i].green = MultiplyChannels(layer1.pixels[i].green, pattern1.pixels[i].green);
            outputImage.pixels[i].blue = MultiplyChannels(layer1.pixels[i].blue, pattern1.pixels[i].blue);
        }

        if (!outputImage.Save("output/part1.tga")) {
            cout << "Error: Could not save part1.tga!" << endl;
            return 1;
        }

        cout << "Task 1 complete! Saved output/part1.tga" << endl;
    }

    // --- Task 2: Subtract Blend ---
    {
        Image layer2;
        Image car;

        if (!layer2.Load("input/layer2.tga") || !car.Load("input/car.tga")) {
            cout << "Error: Could not load input files for Task 2!" << endl;
            return 1;
        }

        Image outputImage2 = car;

        for (size_t i = 0; i < car.pixels.size(); ++i) {
            outputImage2.pixels[i].red = SubtractChannels(layer2.pixels[i].red, car.pixels[i].red);
            outputImage2.pixels[i].green = SubtractChannels(layer2.pixels[i].green, car.pixels[i].green);
            outputImage2.pixels[i].blue = SubtractChannels(layer2.pixels[i].blue, car.pixels[i].blue);
        }

        if (!outputImage2.Save("output/part2.tga")) {
            cout << "Error: Could not save part2.tga!" << endl;
            return 1;
        }

        cout << "Task 2 complete! Saved output/part2.tga" << endl;
    }

    return 0;
}