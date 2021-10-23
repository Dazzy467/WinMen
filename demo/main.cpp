#include "input.h"
#include "Menu.h"

int main()
{
    bool isRun = true;
    int ins = 0;
    std::string in_str;
    std::string* ptr_str = &in_str;
    Menu men;
    input keys[3]{VK_DOWN, VK_UP, VK_RETURN};

    men.showConsoleCursor(false);
    men++;
    std::cout << men.GetIndex() << std::endl;
    men--;
    std::cout << men.GetIndex() << std::endl;

    men.Set({"Start", "Input test", "Exit"});
    men.SetPosition(30, 5);
    men.selectMenuAttr(Menu::Attribute::A_HIGHLIGHT, 0xF1);
    men.draw();
    printAt(40, 13, in_str);
    do
    {
        keys[0].doIfkeyPressed([&]()
                               {
                                   if (men.GetIndex() < men.GetMaxAvailIndex())
                                       men++;

                                   //men.draw();
                                   men.refresh();
                               });
        keys[1].doIfkeyPressed([&]()
                               {
                                   if (men.GetIndex() > 0)
                                       men--;

                                   //men.draw();
                                   men.refresh();
                               });
        keys[2].doIfkeyPressed([&]()
                               {
                                   switch (men.GetIndex())
                                   {
                                   case 1:
                                       men.InputForm_str(std::cin, "Ganti jadi: ",*ptr_str);
                                       printAt(40, 13, in_str);
                                       break;
                                   case 2:
                                       isRun = false;
                                       break;

                                   default:
                                       break;
                                   }
                               });
        Sleep(10);
    } while (isRun);
    return 0;
}