#include "Menu.h"

Menu::Menu()
{
    this->index = 0;
    pos = {0, 0};
    hndl = GetStdHandle(STD_OUTPUT_HANDLE);
    W_ATR_CLR = 7;
    attr = Menu::Attribute::A_ARROW;
    tempX = 0;
    tempY = 0;
}
Menu::~Menu()
{
}

void Menu::draw()
{
    pos.Y = tempY;
    for (size_t i = 0; i < menu_container.size(); i++)
    {
        pos.Y++;

        SetConsoleCursorPosition(hndl, pos);

        switch (attr)
        {
        case Menu::Attribute::A_ARROW:
            if (index == i)
                std::cout << "->";
            else
                std::cout << "\0";
            std::cout << menu_container.at(i) << "  ";   /// Add extra whitespace to clear the weirdness
            break;
        case Menu::Attribute::A_HIGHLIGHT:
            if (index == i)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), W_ATR_CLR);
            else
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            std::cout << menu_container.at(i);
            break;
        default:
            break;
        }
    }
    if (attr == Menu::Attribute::A_HIGHLIGHT)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Menu::Append(const std::string &str)
{
    menu_container.push_back(str);
}

void Menu::setIndex(int N)
{
    this->index = N;
}

void Menu::SetPosition(short int x, short int y)
{
    this->pos.X = x;
    this->pos.Y = y;

    tempY = pos.Y;
}

void Menu::Set(std::initializer_list<std::string> l)
{
    menu_container = l;
}

void Menu::SetValue(unsigned int n, const std::string &str)
{
    menu_container.at(n) = str;
}

void Menu::showConsoleCursor(bool flag)
{
    CONSOLE_CURSOR_INFO c_info;

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c_info);
    c_info.bVisible = flag;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c_info);
}

void Menu::selectMenuAttr(Attribute attrb = Menu::Attribute::A_ARROW, WORD dWORD = 7)
{
    this->attr = attrb;
    this->W_ATR_CLR = dWORD;
}

void Menu::refresh()
{
    clearScr();
    draw();
}

void Menu::clearScr()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = {0, 0};

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi))
    {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

//accessor definition
const std::string Menu::CombineToStr()
{
    std::string temp;
    for (auto& i : menu_container)
    {
        temp = temp + i + '\n';
    }
    return temp;
}