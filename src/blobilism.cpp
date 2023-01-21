#include <iostream>
#include <vector>
#include <variant>
#include <cmath>
#include "tinygl-cpp.h"
using namespace tinygl;

struct Circle {
  std::vector<float> color;
  float circleSize;
  int x;
  int y;
};

class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
    for (int i = 0; i < colors.size(); i++) {
      Circle paletteCirc = {colors[i], 50, 55*(i+0.6), 35};
      paletteCircles.push_back(paletteCirc);
    }
  }

  virtual void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      // todo: store a circle with the current color, size, x, y
      circles.push_back(Circle{currentColor, circleSize, x, y});
    }
  }
  
  virtual void mouseDown(int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      // todo: check if user clicked a color 
      float mx = mouseX();  // current mouse pos x
      float my = mouseY();  // current mouse pos y
      for (Circle paletteCirc : paletteCircles) {
        float dist = sqrt(pow(mx - paletteCirc.x, 2) + pow(my - paletteCirc.y, 2));
        if (dist <= paletteCirc.circleSize/2) {
          currentColor = paletteCirc.color;
          currentColor.push_back(currentAlpha);
          std::cout << "Changed current color to " << currentColor[0] << " " << currentColor[1] << " " << currentColor[2] << std::endl;
        }
      }
    }
  }

  void keyDown(int key, int mods) {
    if (key == GLFW_KEY_UP) {
      // increase size of circle
      circleSize += 5;
      std::cout << "Pressed UP: Increase point size to " << circleSize << std::endl;
    } 
    else if (key == GLFW_KEY_DOWN) {
      if (circleSize >= 6) {
        // decrease size of circle
        circleSize -= 5;
        std::cout << "Pressed DOWN: Decrease point size to " << circleSize << std::endl;
      }
    }
    else if (key == GLFW_KEY_LEFT) {
      if (currentAlpha >= 0.05) {
        // decrease alpha
        currentAlpha -= 0.05;
        currentColor[3] = currentAlpha;
        std::cout << "Pressed LEFT: Increase transparency to " << currentAlpha << std::endl;
      }
    }
    else if (key == GLFW_KEY_RIGHT) {
      // increase alpha
      currentAlpha += 0.05;
      currentColor[3] = currentAlpha;
      std::cout << "Pressed RIGHT: Decrease transparency to " << currentAlpha << std::endl;
    }
    else if (key == GLFW_KEY_C) {
      // clear vector of circles
      circles.clear();
      std::cout << "Pressed C: Clear canvas" << std::endl;
    }
  }

  void draw() override {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    for (Circle circ : circles) {
      color(circ.color[0], circ.color[1], circ.color[2], circ.color[3]);
      circle(circ.x, circ.y, circ.circleSize);
    }

    // todo : draw pallet
    color(0.1f, 0.1f, 0.1f);
    square(width()/2.0f, 35, width(), 70);
    for (int i = 0; i < paletteCircles.size(); i++) {
      color(paletteCircles[i].color[0], paletteCircles[i].color[1], paletteCircles[i].color[2]);
      circle(55*(i+0.6), 35, 50);
    }
  }
 private:

  // todo: create member variables for 
  // current circle size
  float circleSize = 5;
  // current transparency
  float currentAlpha = 1;
  // current color
  std::vector<float> currentColor = {1.0f, 1.0f, 0.0f, currentAlpha};
  // list of circles to draw each frame
  std::vector<Circle> circles;
  // color pallet
  std::vector<std::vector<float>> colors = {{1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}};
  std::vector<Circle> paletteCircles;
};

int main() {
  MyWindow window(500, 500);
  window.run();
}
