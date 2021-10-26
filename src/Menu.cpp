
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
    isRun = true;
}
Menu::~Menu()
{
}

void Menu::draw()
{
    pos.Y = tempY;
    pos.X = tempX;
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
            std::cout << menu_container.at(i) << "  "; /// Add extra whitespace to clear the weirdness
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

    tempX = pos.X;
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
    ex_ClearScr();
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

void Menu::ex_ClearScr()
{
    std::cout.flush();
    pos.Y = tempY;
    pos.X = tempX;
    for (size_t i = 0; i < menu_container.size(); i++)
    {
        pos.Y++;
        pos.X = tempX;
        for (size_t j = 0; j < menu_container[i].length(); j++)
        {
            SetConsoleCursorPosition(hndl, pos);
            std::cout << " ";
            pos.X++;
        }
    }
}

void Menu::pause(const std::string &prompt)
{

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << prompt;

    while (!kbhit())
        Sleep(80); // <- using this makes the performance worse but it can do the trick
}

// accessor definition
const std::string Menu::CombineToStr()
{
    std::string temp;
    for (auto &i : menu_container)
    {
        temp = temp + i + '\n';
    }
    return temp;
}

template <typename T>
void Menu::InputForm(std::istream &in_stream, const std::string &msg, T &in_var)
{
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    clearScr();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << msg;
    in_stream >> in_var;

    if (in_stream.fail())
    {
        clearScr();
        in_stream.clear();
        in_stream.ignore(INT_MAX, '\n');
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        pause("Input error, tekan apa saja untuk melanjutkan");
        clearScr();
        draw();
        return;
    }

    in_stream.ignore(INT_MAX, '\n');
    clearScr();
    draw();
}

void Menu::InputForm_str(std::istream &in_streams, const std::string &msg, std::string &in_var)
{
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    clearScr();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << msg;
    std::getline(in_streams, in_var);

    if (in_streams.fail())
    {
        clearScr();
        in_streams.clear();
        in_streams.ignore(in_streams.rdbuf()->in_avail());
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        pause("Input error, tekan apa saja untuk melanjutkan");
        clearScr();
        draw();
        return;
    }

    clearScr();
    draw();
}

// Template explicit definiton
template void Menu::InputForm<int>(std::istream &in_stream, const std::string &msg, int &in_var);
template void Menu::InputForm<float>(std::istream &in_stream, const std::string &msg, float &in_var);
template void Menu::InputForm<char>(std::istream &in_stream, const std::string &msg, char &in_var);
template void Menu::InputForm<double>(std::istream &in_stream, const std::string &msg, double &in_var);