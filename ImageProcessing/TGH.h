#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#pragma pack(push, 1)
struct Header
{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};
#pragma pack(pop)

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct Image {
    Header header;
    vector<Pixel> pixels;

    bool Load(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            return false;
        }
        
        // read the 18-byte header
        file.read(reinterpret_cast<char*>(&header), sizeof(Header));

        // Calculate total 
        int totalPixels = header.width * header.height;
        pixels.resize(totalPixels);

        // Read Pixel data into vector memory
        file.read(reinterpret_cast<char*>(pixels.data()), totalPixels * sizeof(Pixel));

        file.close();
        return true;
    }

    bool Save(const string& filename) {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            return false;
        }

        file.write(reinterpret_cast<const char*>(&header), sizeof(Header));
        file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(Pixel));

        file.close();
        return true;
    }
};