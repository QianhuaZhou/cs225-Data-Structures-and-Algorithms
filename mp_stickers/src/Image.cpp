#include "Image.h"
using namespace cs225;


/**
 * Lighten an Image by increasing the luminance of every pixel by 0.1.
 * This function ensures that the luminance remains in the range [0, 1].
**/
void Image::lighten(){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.l = std::min(1.0, pixel_.l + 0.1);
        }
    }
}

/**
 * Lighten an Image by increasing the luminance of every pixel by `amount`.
 * This function ensures that the luminance remains in the range [0, 1].
 *
 * @param amount The desired increase in luminance.
**/
void Image::lighten(double amount){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.l = std::min(1.0, pixel_.l + amount);
           pixel_.l = std::max(0.0, pixel_.l + amount);
        }
    }
}

/**
 * Darken an Image by decreasing the luminance of every pixel by 0.1.
 * This function ensures that the luminance remains in the range [0, 1].
**/
void Image::darken(){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.l = std::max(0.0, pixel_.l - 0.1);
        }
    }
}

/**
 * Darkens an Image by decreasing the luminance of every pixel by `amount`.
 * This function ensures that the luminance remains in the range [0, 1].
 *
 * @param amount The desired decrease in luminance.
**/
void Image::darken(double amount){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.l = pixel_.l - amount;
           pixel_.l = std::min(1.0, pixel_.l);
           pixel_.l = std::max(0.0, pixel_.l);
        }
    }
}


/**
 * Saturates an Image by increasing the saturation of every pixel by 0.1.
 * This function ensures that the saturation remains in the range [0, 1].
**/
void Image::saturate(){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.s = std::min(1.0, pixel_.s + 0.1);
        }
    }
}

/**
 * Saturates an Image by increasing the saturation of every pixel by `amount`.
 * This function ensures that the saturation remains in the range [0, 1].
 *
 * @param amount The desired increase in saturation.
**/
void Image::saturate(double amount){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.s = std::min(1.0, pixel_.s + amount);
           pixel_.s = std::max(0.0, pixel_.s + amount);
        }
    }
}

/**
 * Desaturates an Image by decreasing the saturation of every pixel by 0.1.
 * This function ensures that the saturation remains in the range [0, 1].
**/
void Image::desaturate(){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.s = std::max(0.0, pixel_.s - 0.1);
        }
    }
}

/**
 * Desaturates an Image by decreasing the saturation of every pixel by `amount`.
 * This function ensures that the saturation remains in the range [0, 1].
 *
 * @param amount The desired decrease in saturation.
**/
void Image::desaturate(double amount){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.s = std::min(1.0, pixel_.s - amount);
           pixel_.s = std::max(0.0, pixel_.s - amount);
        }
    }
}

/**
 * Turns the image grayscale.
**/
void Image::grayscale(){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.s = 0;
        }
    }
}


/**
 * Rotates the color wheel by `degrees`. Rotating in a positive direction increases the degree of the hue.
 * This function ensures that the hue remains in the range [0, 360].
 *
 * @param degrees The desired amount of rotation.
**/
void Image::rotateColor(double degrees){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           pixel_.h += degrees;
            // Ensure the hue is within the range [0, 360)
            if (pixel_.h >= 360.0) {
                pixel_.h -= 360.0;
            } else if (pixel_.h < 0.0) {
                pixel_.h += 360.0;
            }
        }
    }
}

/**
 * Illinify the image.
**/
void Image::illinify(){
    for(unsigned int x = 0; x < width(); ++x){
        for(unsigned int y = 0; y < height(); ++y){//first row, then column
           HSLAPixel & pixel_ = getPixel(x, y);
           
           if(std::abs(pixel_.h-11) > std::abs(pixel_.h-216)){
            pixel_.h = 11;
           }else{
            pixel_.h = 216;
           } 
        }
    }
}


/**
 * Scale the Image by a given `factor`.
 *
 * For example:
 * - A `factor` of 1.0 does not change the image.
 * - A `factor` of 0.5 results in an image with half the width and half the height.
 * - A `factor` of 2 results in an image with twice the width and twice the height.
 *
 * This function both resizes the Image and scales the contents.
 *
 * @param factor Scale factor.
**/
void Image::scale(double factor){
    Image temp;
    unsigned int newWidth = factor * width();
    unsigned int newHeight = factor * height();
    temp.resize(newWidth, newHeight);
    for (unsigned int x = 0; x < newWidth; ++x) {
        for (unsigned int y = 0; y < newHeight; ++y) {
            unsigned origX = x / factor;
            unsigned origY = y / factor;
            temp.getPixel(x, y) = getPixel(origX, origY);
        }
    }

    // Resize the current image and copy over the scaled pixel data
    resize(newWidth, newHeight);
    for (unsigned int x = 0; x < newWidth; ++x) {
        for (unsigned int y = 0; y < newHeight; ++y) {
            getPixel(x, y) = temp.getPixel(x, y);
        }
    }
}

/**
 * Scales the image to fit within the size (`w` x `h`).  This function preserves
 * the aspect ratio of the image, so the result will always be an image of width
 * `w` or of height `h` (not necessarily both).
 *
 * For example, if the Image is currently (10, 20) and we want to scale to
 * (100, 100), then this should scale the Image to (50, 100). Note that scaling
 * the image to (100, 200) does not fit within the (100,100) dimensions given
 * and is therefore incorrect.
 *
 * This function both resizes the Image and scales the contents.
 *
 * @param w Desired width of the scaled Image
 * @param h Desired height of the scaled Image
**/
void Image::scale(unsigned w, unsigned h){
    double widthFactor = static_cast<double>(w) / width();
    double heightFactor = static_cast<double>(h) / height();

    // Choose the smaller factor to maintain aspect ratio
    double factor = std::min(widthFactor, heightFactor);

    // Call the scaling function with the calculated factor
    scale(factor);
}