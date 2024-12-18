
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "ImageTraversal.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG myImage;
  bool real_success = myImage.readFromFile("../data/i-rainbow-bfs-2.png");
  if (!real_success) {
      std::cerr << "Error: Could not read the file ../data/i-rainbow-bfs-2.png" << std::endl;
      return 1; // Exit early if the file was not read successfully
  }

  FloodFilledImage myFlood(myImage);

  Point startPoint(1, 1);
  Traversals::ImageTraversal dfs(myImage, startPoint, 0.2, {
    Traversals::dfs_add, Traversals::dfs_pop, Traversals::dfs_peek
  });
 // RainbowColorPicker picker(0.5);
  MyColorPicker picker;
  myFlood.addFloodFill(dfs, picker);

  Animation animation = myFlood.animate(50);

  PNG lastFrame = animation.getFrame(animation.frameCount() - 1 );

  for(int i=0; i<50; ++i)
	animation.addFrame( lastFrame );
  //std::cout << "Frame count: " << animation.frameCount() << std::endl;

  lastFrame.writeToFile("../data/myFloodFill.png");
  animation.write("../data/myFloodFill.gif");
  


  return 0;
}
