#include "input.h"
#include "Menu.h"

class Akun
{
public:
    std::string nama;
    std::string password;
    std::string chk_password;

    void Cek()
    {
        if (chk_password == password)
        {
            std::cout << "Password benar ";
            std::cout << "Selamat datang " << nama;
        }
    }
};

int main()
{
    bool created = false;
    //std::string password;
    Menu obj_menu;

    obj_menu.showConsoleCursor(false);
    obj_menu.selectMenuAttr(Menu::Attribute::A_HIGHLIGHT, 0xF1);
    Akun temp;
    std::vector<Akun> usr_acc;
    input keys[3]{VK_DOWN, VK_UP, VK_RETURN};

    obj_menu.Set({"Buat akun", "Login", "Keluar"});
    obj_menu.SetPosition(30, 5);
    obj_menu.draw();
    //printAt(40, 13, password);
    do
    {

        keys[0].doIfkeyPressed([&]()
                               {
                                   if (obj_menu.GetIndex() < obj_menu.GetMaxAvailIndex())
                                       obj_menu++;

                                   obj_menu.refresh();
                               });
        keys[1].doIfkeyPressed([&]()
                               {
                                   if (obj_menu.GetIndex() > 0)
                                       obj_menu--;

                                   obj_menu.refresh();
                               });

        keys[2].doIfkeyPressed([&]()
                               {
                                   switch (obj_menu.GetIndex())
                                   {
                                   case 0:
                                       obj_menu.InputForm_str(std::cin, "Masukan nama: ", temp.nama);
                                       obj_menu.InputForm_str(std::cin, "Masukan password: ", temp.password);
                                       created = true;
                                       usr_acc.push_back(temp);
                                       //printAt(40, 13, password);
                                       break;

                                   case 1:
                                   {
                                       if (created)
                                       {
                                           obj_menu.clearScr();
                                           Menu logins;
                                           for (size_t i = 0; i < usr_acc.size(); i++)
                                               logins.Append(usr_acc[i].nama);
                                           logins.Append("Kembali");

                                           logins.SetPosition(30, 10);

                                           logins.draw();
                                           while (logins.IsRun())
                                           {
                                               keys[0].doIfkeyPressed([&]()
                                                                      {
                                                                          if (logins.GetIndex() < logins.GetMaxAvailIndex())
                                                                              logins++;

                                                                          logins.refresh();
                                                                      });
                                               keys[1].doIfkeyPressed([&]()
                                                                      {
                                                                          if (logins.GetIndex() > 0)
                                                                              logins--;
                                                                          logins.refresh();
                                                                      });
                                               keys[2].doIfkeyPressed([&]()
                                                                      {
                                                                          if (logins.GetIndex() < usr_acc.size())
                                                                          {
                                                                              logins.InputForm_str(std::cin, "Masukan password: ", usr_acc[logins.GetIndex()].chk_password);
                                                                              logins.clearScr();
                                                                              usr_acc[logins.GetIndex()].Cek();

                                                                              printAt(30, 10, "Tekan apa saja untuk melanjutkan");
                                                                              system("pause>nul");
                                                                              logins.clearScr();
                                                                              logins.Kill();
                                                                              obj_menu.draw();
                                                                          }
                                                                          if (logins.GetIndex() == usr_acc.size())
                                                                          {
                                                                              logins.clearScr();

                                                                              logins.Kill();
                                                                              obj_menu.draw();
                                                                          }
                                                                      });
                                               Sleep(10);
                                           }

                                           logins.clearContainer();
                                       }
                                       break;
                                   }

                                   case 2:
                                       obj_menu.Kill();
                                       break;

                                   default:
                                       break;
                                   }
                               });
        Sleep(10);
    } while (obj_menu.IsRun());

    return 0;
}