/**
 * Interactive drawing program
 * 
 * @author Keith Mburu
 * @date 2023-01-23
 * @file blobilism.cpp
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "tinygl-cpp.h"
using namespace tinygl;

struct Point {
  std::vector<float> color;
  float pointSize;
  int x;
  int y;
};

class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
    // set up palette
    for (int i = 0; i < colors.size(); i++) {
      Point palettePoint = {colors[i], 50, int(55 * (i + 0.6)), 35};
      palettePoints.push_back(palettePoint);
    }
  }

  virtual void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      // draw points
      points.push_back(Point{currentColor, pointSize, x, y});
    }
  }
  
  virtual void mouseDown(int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      float mx = mouseX();  // current mouse pos x
      float my = mouseY();  // current mouse pos y
      for (Point palettePoint : palettePoints) {
        // distance from pointer to palette color
        float dist = sqrt(pow(mx - palettePoint.x, 2) + pow(my - palettePoint.y, 2));
        // change color if user clicked on palette color
        if (dist <= palettePoint.pointSize / 2) {
          currentColor = palettePoint.color;
          currentColor.push_back(currentAlpha);
          std::cout << "Setting color to " << currentColor[0] << " " << currentColor[1] << " " << currentColor[2] << std::endl;
        }
      }
    }
  }

  void keyDown(int key, int mods) {
    if (key == GLFW_KEY_UP) {
      pointSize += 5;
      std::cout << "Pressed UP: Increase point size to " << pointSize << std::endl;
    } 
    else if (key == GLFW_KEY_DOWN) {
      if (pointSize >= 6) {
        pointSize -= 5;
        std::cout << "Pressed DOWN: Decrease point size to " << pointSize << std::endl;
      } else {
        std::cout << "Pressed DOWN: Point size is already at min value " << pointSize << std::endl;
      }
    }
    else if (key == GLFW_KEY_LEFT) {
      if (currentAlpha >= 0.05) {
        currentAlpha -= 0.05;
        currentColor[3] = currentAlpha;
        std::cout << "Pressed LEFT: Decrease alpha to " << currentAlpha << std::endl;
      } else {
        std::cout << "Pressed LEFT: Alpha is already at min value " << currentAlpha << std::endl;
      }
    }
    else if (key == GLFW_KEY_RIGHT) {
      if (currentAlpha <= 0.95) {
        currentAlpha += 0.05;
        currentColor[3] = currentAlpha;
        std::cout << "Pressed RIGHT: Increase alpha to " << currentAlpha << std::endl;
      } else {
        std::cout << "Pressed RIGHT: Alpha is already at max value " << currentAlpha << std::endl;
      }
    }
    else if (key == GLFW_KEY_C) {
      points.clear();
      std::cout << "Pressed C: Clear canvas" << std::endl;
    }
  }

  void draw() override {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    // draw points
    for (Point point : points) {
      color(point.color[0], point.color[1], point.color[2], point.color[3]);
      // keyhole paint brush
      circle(point.x, point.y, point.pointSize);
      triangle(point.x, point.y, point.pointSize * 0.8, point.pointSize);
    }

    // draw palette
    color(0.1f, 0.1f, 0.1f);
    // background 
    square(width() / 2.0f, 35, width(), 70);
    // points
    for (int i = 0; i < palettePoints.size(); i++) {
      color(palettePoints[i].color[0], palettePoints[i].color[1], palettePoints[i].color[2]);
      circle(55*(i + 0.6), 35, 50);
    }
  }
 private:

  // current point size
  float pointSize = 5;
  // current transparency
  float currentAlpha = 1;
  // current color
  std::vector<float> currentColor = {1.0f, 1.0f, 0.0f, currentAlpha};
  // list of points to draw each frame
  std::vector<Point> points;
  // palette colors
  std::vector<std::vector<float>> colors = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.65f, 0.7f}, {1.0f, 0.65f, 0.0f}, {0.8f, 0.8f, 0.8f}};
  // list of points for each palette color
  std::vector<Point> palettePoints;
};

int main() {
  MyWindow window(500, 500);
  window.run();
}
