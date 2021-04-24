#pragma once

#include <vector>
#include <iostream>
#include <fstream>

struct Color {
    float r, g, b, a;

    Color();
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    ~Color();
};

class Image
{
    public:
        Image(int width, int height);
        ~Image();

        Color GetColor(int x, int y) const;
        void SetColor(const Color& color, int x, int y);
        unsigned int getHeight();
        unsigned int getWidth();

        unsigned char* toChar();
        void Read(const char* path);
        void Export(const char* path) const;
    private:
        int m_width;
        int m_height;
        std::vector<Color> m_colors;
};

Color::Color()
    : r(0), g(0), b(0), a(1)
{
}

Color::Color(float r, float g, float b)
    : r(r), g(g), b(b), a(1)
{
}

Color::Color(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
{
}

Color::~Color()
{
}

Image::Image(int width, int height)
    : m_width(width), m_height(height), m_colors(std::vector<Color>(width*height))
{
}

Image::~Image()
{
}

Color Image::GetColor(int x, int y) const
{
    return m_colors[y*m_width + x];
}

void Image::SetColor(const Color& color, int x, int y)
{
    m_colors[y*m_width + x].r = color.r;
    m_colors[y*m_width + x].g = color.g;
    m_colors[y*m_width + x].b = color.b;
    m_colors[y*m_width + x].a = color.a;
}

unsigned int Image::getHeight()
{
    return m_height;
}

unsigned int Image::getWidth()
{
    return m_width;
}

unsigned char* Image::toChar()
{
    unsigned char* data = new unsigned char[m_width*m_height*4];
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            data[y*m_width*4 + x*4    ] = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
            data[y*m_width*4 + x*4 + 1] = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
            data[y*m_width*4 + x*4 + 2] = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);
            data[y*m_width*4 + x*4 + 3] = static_cast<unsigned char>(GetColor(x, y).a * 255.0f);
        }
    }
    return data;
}

void Image::Read(const char* path)
{
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File could not be opened.\n";
        return;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M'){
        std::cout << "File is not a bitmap image.\n";
        return;
    }

    unsigned char informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
    m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    m_colors.resize(m_width*m_height);

    const int paddingAmount = ((4 - (m_width*3) % 4) % 4);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            m_colors[y*m_width + x].r = static_cast<float>(color[2])/255.0f;
            m_colors[y*m_width + x].g = static_cast<float>(color[1])/255.0f;
            m_colors[y*m_width + x].b = static_cast<float>(color[0])/255.0f;
        }
        f.ignore(paddingAmount);
    }
    f.close();

    std::cout << "File read successfully.\n";
}

void Image::Export(const char* path) const
{
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File could not be opened.\n";
        return;
    }

    unsigned char bmpPad[3] = {0, 0, 0};
    const int paddingAmount = ((4 - (m_width*3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize + m_width*m_height*3 + paddingAmount*m_height;

    unsigned char fileHeader[fileHeaderSize];

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // File size
    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;
    // Reserved 1 (Not Used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // Reserved 2 (Not Used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel data offset
    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    // Header Size
    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;
    // Image width
    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;
    // Image height
    informationHeader[8] = m_height;
    informationHeader[9] = m_height >> 8;
    informationHeader[10] = m_height >> 16;
    informationHeader[11] = m_height >> 24;
    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;
    // Bits per pixel (RGB)
    informationHeader[14] = 24;
    informationHeader[15] = 0;
    // Compression (no compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;
    // Image size (no compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;
    // X pixels per meter (not specified)
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;
    // Y pixels per meter (not specified)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;
    // Total colors (color palette not used)
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;
    // Important colors (generally ignored)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

            unsigned char color[3] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }

        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    f.close();

    std::cout << "File created.\n";
}