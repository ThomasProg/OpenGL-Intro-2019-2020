#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include "macros.h"

GLuint loadBMP_custom(const char* path)
{
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;

    unsigned char* data;

    FILE* file = fopen(path, "rb");
    if (!file) 
    {
        printf("error on image loading"); 
        return 0;
    }

    if (fread(header, 1, 54, file) != 54)
    {
        printf("error on image loading"); 
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("error on image loading"); 
        return 0;
    }

    dataPos = *(int*) &(header[0x0A]);
    imageSize = *(int*) &(header[0x22]);
    width = *(int*) &(header[0x12]);
    height = *(int*) &(header[0x16]);

    if (imageSize == 0)
        imageSize = width * height * 3;

    if (dataPos == 0)
        dataPos = 54;

    data = new unsigned char[imageSize];

    fread(data, 1, imageSize, file);

    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
        width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
}



#endif