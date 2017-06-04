#include "RawLoader.h"

unsigned char* loadRaw(char* filename, int w, int h)
{
    FILE* f = fopen(filename, "rb");

    unsigned char* out = malloc(sizeof(unsigned char)*w*h*3);
    memset(out, 0, sizeof(unsigned char)*w*h*3);

    if (f)
    {
        int i;
        for (i = 0; i < 3*w*h; i+=3)
        {
            fread(&out[i], sizeof(unsigned char), 3, f);
        }
    }

    if (!feof(f))
        printf("END OF FILE NOT REACHED");
    if(ferror(f))
        printf("ERROROFSOMESOR?T");

    fclose(f);

    return out;
}

unsigned char* loadGreyRaw(char* filename, int w, int h)
{
    FILE* f = fopen(filename, "rb");

    unsigned char* out = malloc(sizeof(unsigned char)*w*h);
    memset(out, 0, sizeof(unsigned char)*w*h);

    if (f)
    {
        int i;
        for (i = 0; i < w*h; i++)
        {
            fread(&out[i], sizeof(unsigned char), 1, f);
        }
    }

    if (!feof(f))
        printf("END OF FILE NOT REACHED");
    if(ferror(f))
        printf("ERROROFSOMESOR?T");

    fclose(f);

    return out;
}

void saveRawImage(char* filename, unsigned char* data, int size_in_bytes)
{
    FILE* f = fopen(filename, "wb");

    if(f)
    {
        int i;
        for (i = 0; i < size_in_bytes; i++)
            fwrite(&data[i], sizeof(unsigned char), 1, f);
    }
}

unsigned char getPix(image* img, int x, int y)
{
    int colours = 1;

    if (x < 0)
        x = 0;
    else if (x >= img->width)
        x = img->width - 1;

    if (y < 0)
        y = 0;
    else if (y >= img->height)
        y = img->height - 1;

    return img->data[(x*colours) + (y*colours*img->width)];
}

void allocateImage(image* img, GLuint *texID)
{
    if (img->data != NULL)
    {
        glGenTextures(1, texID);
        glBindTexture(GL_TEXTURE_2D, *texID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
}

void displayImage(GLuint texID, int x, int y, int w, int h)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(x, y);

        glTexCoord2f(1,0);
        glVertex2f(x + w, y);

        glTexCoord2f(1,1);
        glVertex2f(x + w, y + h);

        glTexCoord2f(0,1);
        glVertex2f(x, y + h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
