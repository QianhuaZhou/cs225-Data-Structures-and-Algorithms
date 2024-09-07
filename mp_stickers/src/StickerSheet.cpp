#include "StickerSheet.h"
using namespace cs225;
  StickerSheet::StickerSheet(){
    maxLayers_ = 0;
    //stickers_.resize(0);
    //positions_.resize(0);
  }
/*
**
   * Initializes this StickerSheet with a deep copy of the base picture.
   *
   * @param picture The base picture to use in the StickerSheet
   */
  StickerSheet::StickerSheet(const Image& picture){
    basePicture_ = picture;
    maxLayers_ = 0;
    //stickers_.resize(1);
    //positions_.resize(1);

  }

  /**
   * Adds a `sticker` to the StickerSheet, so that the top-left of the sticker's
   * `Image` is at `(x, y)` on the StickerSheet.
   *
   * The sticker must be added to the lowest possible layer available.
   *
   * If all available layers have been filled, a new layer must be added above
   * all existing layers.
   *
   * @param sticker The Image of the sticker.
   * @param x The x location of the sticker on the StickerSheet
   * @param y The y location of the sticker on the StickerSheet
   *
   * @return The zero-based layer index the sticker was added to.
   */
  int StickerSheet::addSticker(Image& sticker, int x, int y){
    std::cout << "In addSticker(), maxLayers_= " << maxLayers_ << std::endl;
    if(maxLayers_ != 0){
      for(unsigned int i = 0; i < maxLayers_; ++i){
      if(stickers_[i] == nullptr){
        stickers_[i] = &sticker;
        positions_[i] = {x, y};
        break;
      }
    }
    }
    // Resize the vectors if maxLayers_ exceeds their current size
    if (maxLayers_ >= stickers_.size()) {
        stickers_.resize(maxLayers_ + 1, nullptr);
        positions_.resize(maxLayers_ + 1);
    }

    // Add the sticker at the current maxLayers_ position
    stickers_[maxLayers_] = &sticker;
    positions_[maxLayers_] = {x, y};
    
    //std::cout << "line 52, in addSticker(), sticker->height() = " << stickers_[maxLayers_]->height() << std::endl;
    std::cout << "After addSticker, maxLayers_ = " << maxLayers_ << std::endl;
    maxLayers_ ++;
    
    return maxLayers_ - 1;//return maxLayers_++;
  }

  /**
   * Adds a `sticker` to the StickerSheet at layer `layer`, so that the top-left
   * of the sticker's `Image` is at `(x, y)` on the StickerSheet. If there is already
   * a sticker at `layer` it should be replaced 
   * and if `layer` is beyond the top of the
   * existing layers, add a new layer on top.
   *
   * @param sticker The Image of the sticker.
   * @param layer The layer where the sticker is to be placed.
   * @param x The x location of the sticker on the StickerSheet
   * @param y The y location of the sticker on the StickerSheet
   *
   * @return The zero-based layer index the sticker was added to.
   */
  int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y){
    if(layer < maxLayers_){
      //replace or add at this empty place
      stickers_[layer] = &sticker;
      positions_[layer] = {x, y};
      return layer;
    }
    //add a layer at maxLayers_
    stickers_.push_back(&sticker);
    positions_.push_back({x, y});
    maxLayers_ ++;
    return maxLayers_ - 1;
    
  }

  /**
   * Changes the x and y coordinates of the Image in the specified layer.
   *
   * If the layer is invalid or does not contain a sticker, this function
   * must return false. Otherwise, this function returns true.
   *
   * @param index Zero-based layer index of the sticker.
   * @param x The new x location of the sticker on the StickerSheet
   * @param y The new y location of the sticker on the StickerSheet
   *
   * @return `true` if the translate was successful; otherwise `false`.
   */
  bool StickerSheet::translate(unsigned index, int x, int y){
    if(index < 0 || index >= maxLayers_ || stickers_[index] == nullptr) return false;
    positions_[index] = {x, y};
    return true;
  }

  /**
   * Removes the sticker at the given zero-based layer index. Make sure that the
   * other stickers don't change order.
   *
   * @param index The layer in which to delete the png
   */
 void StickerSheet::removeSticker(unsigned index) {
    // Check if index is valid
    if (index >= stickers_.size()) {
        std::cerr << "Invalid index: " << index << std::endl;
        return;
    }

    // Free the memory at the specified index
    //delete stickers_[index];

    // Set the sticker pointer to nullptr instead of erasing
    stickers_[index] = nullptr;

    // Reset the position for the removed sticker
    positions_[index] = {0, 0};

    // Adjust maxLayers_ if needed
    // Decrement maxLayers_ if the sticker was at the highest layer
    if (index == maxLayers_ - 1) {
        maxLayers_--;
        /*
        while (maxLayers_ > 0 && stickers_[maxLayers_ - 1] == nullptr) {
            maxLayers_--;  // Adjust maxLayers_ to the highest valid layer
        }
        */
        
    }

    std::cout << "=================================" << std::endl;
    std::cout <<  "stickers_.size(): " << stickers_.size() << std::endl;
    std::cout << "Removed sticker at index: " << index << std::endl;
    std::cout << "maxLayers_ = " << maxLayers_ << std::endl;
}


  /**
   * Returns a pointer to the sticker at the specified index,
   * not a copy of it. That way, the user can modify the Image.
   *
   * If the index is invalid, return NULL.
   *
   * @param index The layer in which to get the sticker.
   *
   * @return A pointer to a specific Image in the StickerSheet
   */
  Image* StickerSheet::getSticker(unsigned index){
    if(index < 0 || index >= maxLayers_) return nullptr;
    return stickers_[index];
  }

  /**
   * Returns the total number of layers available on the Stickersheet.
   *
   * @return The total number of layers
   */
  int StickerSheet::layers() const {
    //is not existed included in inavailable?
    return maxLayers_;
  }

  /**
   * Renders the whole StickerSheet on one Image and returns that Image.
   *
   * The base picture is drawn first and then each sticker is drawn in order
   * starting with layer zero (0), then layer one (1), and so on.
   *
   * If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn
   * for that sticker at that pixel. If the alpha channel is non-zero, a pixel is drawn. (Alpha blending is awesome, but not required.)
   *
   * The returned image always includes the full contents of the picture and
   * all stickers. It should expand in each corresponding direction if
   * stickers go beyond the edge of the picture.
   *
   * @return An Image object representing the drawn scene
   */
  
  

  Image StickerSheet::render() const{
    const Image& base = basePicture_;
    std::pair<int, int> basePos = {0, 0};
    std::pair<int, int> basePosPlus = {base.width(), base.height()};
    
    for(unsigned i = 0; i < maxLayers_; ++i){
      Image* sticker = stickers_[i];
      if(sticker == nullptr) continue;
      //std::cout << "line 195, in render(), sticker->height() = " << sticker->height() << std::endl;
      std::pair pos = positions_[i];
      int& x_cor = pos.first;
      int& y_cor = pos.second;
      basePos.first = std::min(x_cor, basePos.first);
      basePos.second = std::min(y_cor, basePos.second);
      
      int width_ = sticker->width();
      int height_ = sticker->height();
      //std::cout << "line 169 sticker->height() = " << sticker->height() << std::endl;
      basePosPlus.first = std::max(basePosPlus.first, x_cor + width_);
      basePosPlus.second = std::max(basePosPlus.second, y_cor + height_);
      if(basePosPlus.second == 827){
        //std::cout << "At line 202, height_ = " << height_ << std::endl;
        //std::cout << "At line 203, y_cor = " << y_cor << std::endl;
        break;
      }
    }
    Image output(basePosPlus.first - basePos.first, basePosPlus.second - basePos.second);
    //std::cout << "Output dimensions: " << output.width() << "x" << output.height() << std::endl;
    //std::cout << "Base dimensions: " << base.width() << "x" << base.height() << std::endl;

    //deal with base picture
    for(unsigned int x = 0; x < base.width(); ++ x){
      for(unsigned int y = 0; y < base.height(); ++y){
        HSLAPixel & basePixel_ = output.getPixel(x - basePos.first, y - basePos.second);
        HSLAPixel const & stickerPixel = base.getPixel(x, y);
        basePixel_ = stickerPixel;
      }
    }
    for(unsigned index = 0; index < maxLayers_; ++index){
      Image* sticker = stickers_[index];
      if(sticker == nullptr) continue;
      unsigned int width_ = sticker->width();
      unsigned int height_ = sticker->height();
      int x_pos = positions_[index].first;
      int y_pos = positions_[index].second;
      //std::cout << "line 180" << std::endl;
      for(unsigned int x = 0; x < width_; ++ x){
            for(unsigned int y = 0; y < height_; ++y){
              if(sticker->getPixel(x, y).a != 0) {
                HSLAPixel & basePixel = output.getPixel(x_pos + x - basePos.first, y_pos + y - basePos.second);
                HSLAPixel const & stickerPixel = sticker->getPixel(x, y);
                basePixel = stickerPixel;
              }
  
            }
      }
    }
  return output;
  }

  