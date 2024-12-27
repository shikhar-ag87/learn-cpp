#include <stdint.h>

void splitChannels(uint8_t* srcData, int srcSize, int totalChannels, uint8_t* r, uint8_t* g, uint8_t* b) {
    for(int i=0, j=0; i<srcSize-totalChannels; i+=totalChannels, j++) {
        r[j] = srcData[i+0];
        g[j] = srcData[i+1];
        b[j] = srcData[i+2];
    }
}

void mergeChannels(uint8_t* dstData, int srcSize, int totalChannels, uint8_t* r, uint8_t* g, uint8_t* b) {
    for(int i=0, j=0; i<srcSize-totalChannels; i+=totalChannels, j++) {
        dstData[i+0] = r[j];
        dstData[i+1] = g[j];
        dstData[i+2] = b[j];
    }
}

void cartesianToPolar(uint8_t* srcData, int srcSize, int totalChannels) {

}

void resizeImage(uint8_t* srcData, int w, int h, int totChannels, uint8_t* dstData, int nw, int nh) {

    for(int i_a=0; i_a<nh; i_a++) {
        for(int j_a=0; j_a<nw; j_a++) {

            int a = i_a*nw + j_a; // idx in dst

            int i_b = (i_a*h/nh);
            int j_b = (j_a*w/nw);

            int b = i_b*w + j_b; // idx in src

            for(int c=0; c<totChannels; c++) {
                dstData[a*totChannels+c] = srcData[b*totChannels+c];
            }
        }
    }

}

void cropImage(uint8_t* srcData, int w, int h, int totChannels, uint8_t* dstData, int sx, int sy, int ex, int ey) {
    for(int i=0; i<(ey-sy); i++) {
        for(int j=0; j<(ex-sx); j++) {

            int a = i*(ex-sx) + j;
            int b = (i+sy)*w + (j+sx);


            for(int c=0; c<totChannels; c++) {
                dstData[a*totChannels+c] = srcData[b*totChannels+c];
                // dstData[a*totChannels+c] = 255;
            }
        }
    }
}


void centeredCropImage(uint8_t* srcData, int w, int h, int totChannels, uint8_t* dstData, int nw, int nh) {
    int ex = (w+nw)/2;
    int sx = (w-nw)/2;
    int ey = (h+nh)/2;
    int sy = (h-nh)/2;
    cropImage(srcData, w, h, totChannels, dstData, sx,sy,ex,ey);
}


void addChromatic(uint8_t* srcData, uint8_t* dstData, int w, int h, int totChannels, double strength=1.0) {
    int size = w*h*totChannels;

    int s = w*h;

    uint8_t* r; r = new uint8_t[s];
    
    uint8_t* g; g = new uint8_t[s];
    
    uint8_t* b; b = new uint8_t[s];
    
    splitChannels(srcData, size, totChannels, r, g, b);

    int g_nw = (int)((1.0 + 0.018 * strength)*(double)w);
    int g_nh = (int)((1.0 + 0.018 * strength)*(double)h);
    uint8_t* ng; 
    ng = new uint8_t[g_nw*g_nh*totChannels];
    resizeImage(g, w, h, 1, ng, g_nw, g_nh);
    centeredCropImage(ng, g_nw, g_nh, 1, g, w, h);

    int b_nw = (int)((1.0 + 0.044 * strength)*(double)w);
    int b_nh = (int)((1.0 + 0.044 * strength)*(double)h);
    uint8_t* nb; 
    nb = new uint8_t[b_nw*b_nh*totChannels];
    resizeImage(b, w, h, 1, nb, b_nw, b_nh);
    centeredCropImage(nb, b_nw, b_nh, 1, b, w, h);


    mergeChannels(dstData, size, totChannels, r, g, b);
    // resizeImage(b, w, h, 1, b, (1 + 0.018 * strength)*w, (1 + 0.018 * strength)*h);


        
    
    return;
}
