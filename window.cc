#include "triggerType.h"
#include "owner.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height): width(width), height(height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), BlackPixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  this->colourMap.insert(pair<string, vector<int>>("Air Elemental", {0, 4, 5}));
  this->colourMap.insert(pair<string, vector<int>>("Earth Elemental", {1, 8, 9}));
  this->colourMap.insert(pair<string, vector<int>>("Fire Elemental", {2, 4, 5, 6, 7, 8}));
  this->colourMap.insert(pair<string, vector<int>>("Potion Seller", {0, 1, 8, 9}));
  this->colourMap.insert(pair<string, vector<int>>("Novice Pyromancer", {2, 4, 5, 6, 7, 8}));
  this->colourMap.insert(pair<string, vector<int>>("Apprentice Summoner", {0, 3, 4, 5, 6}));
  this->colourMap.insert(pair<string, vector<int>>("Master Summoner", {1, 2, 7, 8, 9}));
  this->colourMap.insert(pair<string, vector<int>>("Banish", {2, 3, 4, 5, 9}));
  this->colourMap.insert(pair<string, vector<int>>("Unsummon", {4, 5, 8, 9}));
  this->colourMap.insert(pair<string, vector<int>>("Recharge", {2, 3, 4, 5, 6, 7, 8}));
  this->colourMap.insert(pair<string, vector<int>>("Disenchant", {2, 5, 6, 7, 8, 9}));
  this->colourMap.insert(pair<string, vector<int>>("Raise Dead", {0,1,2,3,4,5,6,7,8,9}));
  this->colourMap.insert(pair<string, vector<int>>("Blizzard", {0,4,5,6}));
  this->colourMap.insert(pair<string, vector<int>>("Giant Strength", {1,2,3,4,5,6,7,8,9}));
  this->colourMap.insert(pair<string, vector<int>>("Magic Fatigue", {0,2,3,6,7,8,9}));
  this->colourMap.insert(pair<string, vector<int>>("Silence", {0,1}));
  this->colourMap.insert(pair<string, vector<int>>("Dark Ritual", {1,2,9}));
  this->colourMap.insert(pair<string, vector<int>>("Aura of Power", {0,1,2,3,4,5,6,7,8,9}));
  this->colourMap.insert(pair<string, vector<int>>("Standstill", {0,1,4,5}));
  this->colourMap.insert(pair<string, vector<int>>("Cloud Drake", {2,4,5,6,7,8,9}));
  this->colourMap.insert(pair<string, vector<int>>("Lady Luck", {0,2,6,7,8}));
  this->colourMap.insert(pair<string, vector<int>>("Fireball", {2,4,5,6,7,8,9}));
  this->colourMap.insert(pair<string, vector<int>>("Pot of Greed", {6,8,9}));
  this->colourMap.insert(pair<string, vector<int>>("Goose Jacket", {0,1,2}));
  this->colourMap.insert(pair<string, vector<int>>("Random Forest", {3,5,8}));
  this->colourMap.insert(pair<string, vector<int>>("King of Spades", {0,6,7,8,9}));
  this->colourMap.insert(pair<string, vector<int>>("Heads", {0,3,4,5,6}));
  this->colourMap.insert(pair<string, vector<int>>("Tail", {1,2,9}));
  this->colourMap.insert(pair<string, vector<int>>("Start", {0,3,4,5,6}));
  this->colourMap.insert(pair<string, vector<int>>("End", {1,2,9}));

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 10; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::notify(Owner* owner, Owner* opponent, string &event) {
  vector<int> v = this->colourMap.at(event);
  string fileName = event + ".txt";
  for (int j = 0; j < 20; j++) {
  ifstream asci(fileName);
  string s;
  int i = 2;
  while(getline(asci, s)){
    this->drawString(10, 10*i, s, v[j%v.size()]);
    i++;
  }
  }
  this->fillRectangle(0, 0, 500, 500, 1);
}

void Xwindow::notify(Owner* owner, Owner* opponent, int fieldIndex, int whoSummon) {}

TriggerType Xwindow::getTriggerType() const {
  return TriggerType::Xwindow;
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  Font f = XLoadFont(d, "6x13");
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}


void Xwindow::drawBigString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
  ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";

  XFontStruct * f = XLoadQueryFont(d, name.str().c_str());
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f->fid;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}

void Xwindow::showAvailableFonts() {
  int count;
  char** fnts = XListFonts(d, "*", 10000, &count);

  for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
}

