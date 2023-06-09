//
// Created by boery on 21.03.2022.
//

#ifndef CGPRAKT1_RGBIMAGE_H
#define CGPRAKT1_RGBIMAGE_H

#include <iostream>

class Color;

class RGBImage {
public:
    RGBImage(unsigned int Width, unsigned Height);

    ~RGBImage();

    void setPixelColor(unsigned int x, unsigned int y, const Color &c);

    const Color &getPixelColor(unsigned int x, unsigned int y) const;

    bool saveToDisk(const char *Filename);

    unsigned int width() const;

    unsigned int height() const;

    static unsigned char convertColorChannel(float v);

protected:
    Color *m_Image;
    unsigned int m_Height;
    unsigned int m_Width;


};

#endif //CGPRAKT1_RGBIMAGE_H
