#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <iostream>
#include <ios>
#include <vector>
#include <initializer_list>
#include <climits>
#include <string>
#include <conio.h>

/*
AUTH: DAVID YUSUF DE WASKITO
DESC: COMMAND LINE MENU LIBRARY 
      USE THIS TO MAKE SIMPLE NAVIGATION MENU
      IT'S EASY TO USE.

THIS LIBRARY IS OPEN SOURCE
YOU CAN EDIT, DISTRIBUTE, AND USE IT AT YOUR OWN LEISURE
*/

class Menu
{
public: //Constructor / destructor
  Menu();
  ~Menu();

public:
  enum class Attribute
  {
    A_HIGHLIGHT = 0,
    A_ARROW
  };

public: //method
  void draw();
  void Append(const std::string &str);
  void setIndex(int N);
  void SetPosition(short int x, short int y);
  void Set(std::initializer_list<std::string> l);
  void SetValue(unsigned int n, const std::string &str);
  void showConsoleCursor(bool flag);

  void selectMenuAttr(Attribute attrb, WORD dWORD);
  void refresh();
  void clearScr();
  void ex_ClearScr();
  void pause(const std::string& prompt);

  //accessor
  void clearContainer() { this->menu_container.clear(); }
  const std::string GetValue(unsigned int n) { return menu_container.at(n); }
  const int GetCount() { return menu_container.size(); }
  const int GetIndex() { return this->index; }
  const size_t GetMaxAvailIndex() { return this->menu_container.size() - 1; }
  const bool IsRun() { return this->isRun; }
  void Kill() { this->isRun = false; }

  // Inputting  
  template <typename T>
  void InputForm(std::istream &in_stream, const std::string &msg, T &in_var);
  void InputForm_str(std::istream &in_streams, const std::string &msg, std::string &in_var);

  const std::string CombineToStr();
  // in class definition
  //operator
  // untuk increment dan decrement index nya
  Menu &operator++(int)
  {
    index++;
    return *this;
  }
  Menu &operator--(int)
  {
    index--;
    return *this;
  }



private: //variabel
  std::vector<std::string> menu_container;
  COORD pos;
  int index;
  HANDLE hndl;
  WORD W_ATR_CLR;
  Attribute attr;
  bool isRun;

  SHORT tempX, tempY;
};

// outside class function
template <typename T>
void printAt(SHORT x, SHORT y, const T &val)
{
  COORD tpl{x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tpl);
  std::cout << val;
}