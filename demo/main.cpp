#include "input.h"
#include "Menu.h"  

int main()
{
    bool isRun = true;
    Menu men;
    input keys[3];
    keys[0].setKey(VK_DOWN);
    keys[1].setKey(VK_UP);
    keys[2].setKey(VK_RETURN);

    men.showConsoleCursor(false);
    men++;
    std::cout << men.GetIndex() << std::endl;
    men--;
    std::cout << men.GetIndex() << std::endl;

    men.Set({"Start", "Option", "Exit"});
    men.SetPosition(30, 5);
    men.selectMenuAttr(Menu::Attribute::A_HIGHLIGHT, 0xF1);                                                       
    men.draw();                                   
    printAt(40,13,1);
    do
    {
        keys[0].doIfkeyPressed([&]()
                               {
                                   if (men.GetIndex() < men.GetMaxAvailIndex())
                                       men++;
                                  
                                   men.draw();
                                   //men.refresh();
                               });
        keys[1].doIfkeyPressed([&]()
                               {
                                   if (men.GetIndex() > 0)
                                       men--;
                                   
                                   men.draw();
                                   //men.refresh();
                               });
        keys[2].doIfkeyPressed([&]()
                               {
                                   if (men.GetIndex() == 2)
                                       isRun = false;
                               });
        Sleep(10);
    } while (isRun);
    return 0;
}