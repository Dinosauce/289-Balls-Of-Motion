/**
 * @author Jayden Grant
 * Provides functionality for loading raw image data from RGB or GRAYSCALE images.
 * Currently handles RGB and greyscale images seperatly (currently does not
 * support RGBA or others); the image struct does not record image channel count.
 */
#ifndef RAWLOADER_H
#define RAWLOADER_H

#include <stdio.h>
#include <gl/freeglut.h>

// #define GREYSCALE 1
// #define RGB 3
// #define RGBA 4

typedef struct {
    unsigned char* data;
    int width;
    int height;
} image;

/** @brief Load a 3 channel (RGB) raw image.
 */
unsigned char* loadRaw(char* filename, int width, int height);
/** @brief Load a 1 channel (GREYSCALE) raw image.
 */
unsigned char* loadGreyRaw(char* filename, int width, int height);

/** @brief Save the raw byte data to filename
 * @param filename - The file to save the data to
 * @param data -  the raw byte data to write to the filename
 * @param size_in_bytes - the number of bytes to write to the file (typically width * height * number of channels)
 */
void saveRawImage(char* filename, unsigned char* data, int size_in_bytes);

/** @brief returns the pixel data at given position (GREYSCALE IMAGES)
 */
unsigned char getPix(image* img, int x, int y);

/** @brief Allocates an image in openGL and sets texID
 * @param image - the image to allocate in GL memory
 * @param texID - will be set to the openGL texID
 * @pre image - will contain the raw image data and correct image width and height
 * @post texID - is set to the openGL texID, which can be used when displaying image
 */
void allocateImage(image* img, GLuint *texID);

/** @brief Displays the image to the screen using openGL
 * @param texID - the openGL texID of the image to be displayed
 * @param x - the x screen position to display image at.
 * @param y - the y screen position to display image at.
 * @param w - the width to display the image at.
 * @param h - the height to display the image at.
 */
void displayImage(GLuint texID, int x, int y, int w, int h);

#endif // RAWLOADER_H
