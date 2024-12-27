#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdint.h>
#include <string>
#include <iostream>
#include "stb_image.h"
#include "stb_image_write.h"
#include "kromo.cpp"


using namespace std;

enum ImageType {
    PNG, JPG, BMP, TGA
};


struct Image {

public:
    // used uint8_t* since we cant tell it to store as we would need size beforehand
    
    uint8_t* data = NULL;
    size_t size = 0;
    int w;
    int h;
    int channels;

    // constructors 

    Image(const char* filename) {
        if(read(filename)) {
            size = w*h*channels;
        }
    }

    Image(int w, int h, int channels) {
        size = w*h*channels;
        data = new uint8_t[size];

    }
    
    // the part after : initializes values before constructor is called
    Image(const Image& img): w(img.w), h(img.h), channels(img.channels), size(img.size) {
        // copies img.data into data, for size number of bytes
        // used memccpy since initializing it would copy only the address
        memcpy(data, img.data, size);

    }
    
    ~Image() {
        stbi_image_free(data);
    }
    


    // methods

    bool read(const char* filename) {
        data = stbi_load(filename, &w, &h, &channels, 0);
        size = w*h*channels;
        return (data != NULL);
    }

    bool write(const char* filename) {
        ImageType type = getFileType(filename);
        int success;
        switch(type) {
            case PNG:
                success = stbi_write_png(filename, w, h, channels, data, w*channels);
            case JPG:
                success = stbi_write_jpg(filename, w, h, channels, data, 100);
            case TGA:
                success = stbi_write_tga(filename, w, h, channels, data);
            case BMP:
                success = stbi_write_bmp(filename, w, h, channels, data);

        }

        return success != 0;
    }

    void resize(double fx, double fy) {
        
        if (fx<=0) throw out_of_range("argument fx out of range");
        if (fy<=0) throw out_of_range("argument fy out of range");

        double fxy = fx*fy;
        int nw = (int)((double)w*fx);
        int nh = (int)((double)h*fy);

        uint8_t* dstData;
        dstData = new uint8_t[nw*nh*channels];
        
        for(int i=0; i<nw*nh; i++) {
            int a = i;
            int b = i/fxy;
            for(int c=0; c<channels; c++) {
                dstData[a*channels+c] = data[b*channels+c];
            }
        }

        data = dstData;
        w = nw;
        h = nh;
        size = w*h*channels;
    }

    void resizeToSize(int nw, int nh) {
        if (nw<=0) throw out_of_range("argument nw out of range");
        if (nh<=0) throw out_of_range("argument nh out of range");

        uint8_t* dstData;
        dstData = new uint8_t[nw*nh*channels];
        
        for(int i_a=0; i_a<nh; i_a++) {
            for(int j_a=0; j_a<nw; j_a++) {

                int a = i_a*nw + j_a; // idx in dst

                int i_b = (i_a*h/nh);
                int j_b = (j_a*w/nw);

                int b = i_b*w + j_b; // idx in src

                for(int c=0; c<channels; c++) {
                    dstData[a*channels+c] = data[b*channels+c];
                }
            }
        }

        data = dstData;
        w = nw;
        h = nh;
        size = w*h*channels;
    }

    void crop(int sx, int sy, int ex, int ey) {
        
        if (sx<0 || sx >= ex) throw out_of_range("argument sx out of range");
        if (sy<0 || sy >= ey) throw out_of_range("argument sy out of range");
        if (ex>w || ex <= sx) throw out_of_range("argument ex out of range");
        if (ey>h || ey <= sy) throw out_of_range("argument ey out of range");


        uint8_t* dstData;
        dstData = new uint8_t[(ex-sx)*(ey-sy)*channels];
        
        for(int i=0; i<(ey-sy); i++) {
            for(int j=0; j<(ex-sx); j++) {

                int a = i*(ex-sx) + j;
                int b = (i+sy)*w + (j+sx);


                for(int c=0; c<channels; c++) {
                    dstData[a*channels+c] = data[b*channels+c];
                }
            }
        }


        data = dstData;
        w = ex-sx;
        h = ey-sy;
        size = w*h*channels;
    }

    void centerCrop(int nw, int nh) {

        if (nw<=0 || nw>w) throw out_of_range("argument nw out of range");
        if (nh<=0 || nh>h) throw out_of_range("argument nh out of range");

        uint8_t* dstData;
        dstData = new uint8_t[(nw)*(nh)*channels];
        
        int ex = (w+nw)/2;
        int sx = (w-nw)/2;
        int ey = (h+nh)/2;
        int sy = (h-nh)/2;
        crop(sx,sy,ex,ey);

        data = dstData;
        w = nw;
        h = nh;
        size = w*h*channels;

    }

    void addImage(const Image& img) {
        if(img.size != size || img.w != w || img.h != h) throw invalid_argument("argument img not of same size as current image");

        for(int i=0; i<size; i++) {
            data[i] =  data[i] + img.data[i];
        }

    }

    void addChromaticEffect(double strength=1.0) {

        if (strength < 0.0 || strength > 1.0) throw out_of_range("argument strength out of range");

        uint8_t* dstData;
        dstData = new uint8_t[w*h*channels];
        
        addChromatic(data, dstData, w, h, channels, strength);

        data = dstData;
    }


    uint8_t** splitChannels() {
        int s = w*h;

        uint8_t* r; r = new uint8_t[s];
        
        uint8_t* g; g = new uint8_t[s];
        
        uint8_t* b; b = new uint8_t[s];

        uint8_t** x;
        x = new uint8_t*[channels];

        for(int i=0, j=0; i<size-channels; i+=channels, j++) {
            for(int c=0; c<channels; c++) {
                x[c][j] = data[i+c];
            }
        }
        
        return x;
    }



private:
    ImageType getFileType(const char* filename) {
        // strrchr returns the pointer to last occurence of a char in string
        // so we essentially get the extension string pointer with "."
        // nullptr if not found
        const char* ext = strrchr(filename, '.');
        if(ext == nullptr) return PNG; // png becomes default
        pair<string, ImageType> exts[] = { 
            {".png", PNG},
            {".jpeg", JPG},
            {".jpg", JPG},
            {".bmp", BMP},
            {".tga", TGA},
        };
        for(auto val : exts) {
            if(strcmp(val.first.c_str(), ext) == 0) return val.second;
        }
        return PNG;
    }
};