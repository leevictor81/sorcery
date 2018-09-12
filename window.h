#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <map>
#include <vector>
#include <iostream>
#include <string>

class Xwindow : public Observer {
  Display *d;
  Window w;
  int s;
  GC gc;
  std::map<std::string, std::vector<int>> colourMap;
  unsigned long colours[10];
  int width, height;

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;
  void notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) override;
  void notify(Owner* me, Owner* opponent, std::string &event) override;
  TriggerType getTriggerType() const override;

  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour=Black);

  // Draws a string
  void drawBigString(int x, int y, std::string msg, int colour=Black);

  // Prints the first 10000 available fonts
  void showAvailableFonts();
};

#endif

