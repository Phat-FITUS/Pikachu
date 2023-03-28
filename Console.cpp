#include "Console.h"

void Console::Clear() {
    //Unix user
    //std::cout << "\033[2J\033[1;1H";
    //Window user
    system("cls");
}

void Console::SetWindowSize(int w, int h) {
    SHORT width = w;
    SHORT height = h;

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void Console::DisableResizeWindow() {
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void Console::DisableMaximizeButton() {
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
}

void Console::DisableCur() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = false;

    SetConsoleCursorInfo(handle, &ConCurInf);
}

void Console::HideScrollbar() {
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, false);
}

void Console::GoTo(int x, int y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = x;
    Position.Y = y;

    SetConsoleCursorPosition(hStdout, Position);
}

void Console::SetColor(int backgoundColor, int textColor) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgoundColor * 16 + textColor;
    SetConsoleTextAttribute(hStdout, color_code);
}

void Console::MoveConsole(int x, int y) {
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    GetClientRect(hWnd, &rectClient);
    GetWindowRect(hWnd, &rectWindow);
    MoveWindow(hWnd, x, y, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);
}