#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <initializer_list>

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

  //accessor
  const std::string GetValue(unsigned int n) { return menu_container.at(n); }
  const int GetCount() { return menu_container.size(); }
  const int GetIndex() { return this->index; }
  const size_t GetMaxAvailIndex() { return this->menu_container.size() - 1; }

  const std::string CombineToStr();
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

  SHORT tempX, tempY;
};

// outside class function
template <typename T>
void printAt(SHORT x, SHORT y, T val)
{
  COORD tpl{x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tpl);
  std::cout << val;
}