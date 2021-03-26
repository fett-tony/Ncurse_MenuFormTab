#include "MenuWinClass.h"

using namespace WinFormMenu;
using namespace std;

MenuWinClass *MenuWinClassMWC = new MenuWinClass();
FILE * world;

MenuWinClass::MenuWinClass() {
    START.WCX(); // = 80;
    START.HRY(); // = 24;
    START.WinSize.WCX(); // = 80;
    START.WinSize.HRY(); // = 24;
    START.WinSize.WCX_Real();
    START.WinSize.HRY_Real();
    START.WinSize.WCX_Center();
    START.WinSize.HRY_Center();
    START.WinSize.WCX_TmpWin(stdscr);
    START.WinSize.HRY_TmpWin(stdscr);
    START.WinSize.WCX_TmpWinReal(stdscr);
    START.WinSize.HRY_TmpWinReal(stdscr);
    START.WinSize.WCX_TmpWinCenter(stdscr);
    START.WinSize.HRY_TmpWinCenter(stdscr);
    FORMPAGE.WCXform = static_cast<int>(roundf(START.WCXw3() - 2)); //START.WinSize.WCX_TmpWinReal(START.TMPWin2);
    FORMPAGE.HRYform = static_cast<int>(roundf(START.HRYw3() - 2)); //START.WinSize.HRY_TmpWinReal(START.TMPWin2);
}
/*################################################################################*/
WinID& operator++(WinID& WID, int) {
    return WID = (WID == WinID::ENDWIN) ? WinID::MENU_Win_1 : static_cast<WinID>(static_cast<int>(WID) + 1);
};
WinID& operator--(WinID& WID, int) {
    return WID = (WID == WinID::ENDWIN) ? WinID::MENU_Win_1 : static_cast<WinID>(static_cast<int>(WID) - 1);
};
ostream& operator<<(ostream& WID, WinID e) {
    static const vector<string> EnumString = { "MENU_Win_1",
                                               "MAIN_Win_2",
                                               "FORM_Win_3",
                                               "MENU_Win_4",
                                               "MENU_Win_5",
                                               "ALLWIN",
                                               "ENDWIN" };
    return WID << EnumString[static_cast<WinID>(e)];
};
MenuFormID& operator++(MenuFormID& MID, int) {
    return MID = (MID == MenuFormID::ENDMENUFORM) ? MenuFormID::FORMWIN1 : static_cast<MenuFormID>(static_cast<int>(MID) + 1);
};
MenuFormID& operator--(MenuFormID& MID, int) {
    return MID = (MID == MenuFormID::ENDMENUFORM) ? MenuFormID::FORMWIN1 : static_cast<MenuFormID>(static_cast<int>(MID) - 1);
};
ostream& operator<<(ostream& MID, MenuFormID e) {
    static const vector<string> EnumString = {"FORMWIN1",
                                              "FORMWIN2",
                                              "FORMWIN3",
                                              "FORMWIN4",
                                              "FORMWIN5",
                                              "FORMWIN6",
                                              "FORMWIN7",
                                              "FORMWIN8",
                                              "INLINEMENU1",
                                              "INLINEMENU2",
                                              "MENU_MAIN",
                                              "ENDMENUFORM" };
    return MID << EnumString[static_cast<MenuFormID>(e)];
};
TabID& operator++(TabID& TID, int) {
    return TID = (TID == TabID::MainTab3) ? TabID::MainTab1 : static_cast<TabID>(static_cast<int>(TID) + 1);
};
TabID& operator--(TabID& TID, int) {
    return TID = (TID == TabID::MainTab3) ? TabID::MainTab1 : static_cast<TabID>(static_cast<int>(TID) - 1);
};
ostream& operator<<(ostream& TID, TabID e) {
    static const vector<string> EnumString = {"MainTab1",
                                              "MainTab2",
                                              "MainTab3"};
    return TID << EnumString[static_cast<TabID>(e)];
};
vector<ID_Setup_> MenuWinClass::IDSet = {
    {0, FORMWIN1,    "FORMWIN1",    FORM_Win_3, "Form Window 1!"},
    {1, FORMWIN2,    "FORMWIN2",    FORM_Win_3, "Form Window 2!"},
    {2, FORMWIN3,    "FORMWIN3",    FORM_Win_3, "Form Window 3!"},
    {3, FORMWIN4,    "FORMWIN4",    FORM_Win_3, "Form Window 4!"},
    {4, FORMWIN5,    "FORMWIN5",    FORM_Win_3, "Form Window 5!"},
    {5, FORMWIN6,    "FORMWIN6",    FORM_Win_3, "Form Window 6!"},
    {6, FORMWIN7,    "FORMWIN7",    FORM_Win_3, "Form Window 7!"},
    {7, FORMWIN8,    "FORMWIN8",    FORM_Win_3, "Form Window 8!"},
    {8, INLINEMENU1, "INLINEMENU1", MENU_Win_4, "Menu Window 1!"},
    {9, INLINEMENU2, "INLINEMENU2", MENU_Win_5, "Menu Window 2!"},
    {10, MENU_MAIN,  "MENU_MAIN",   MENU_Win_1, "Hauptmenü!"},
    {11, ENDMENUFORM,"ENDMENUFORM", ENDWIN, "ENDE!"},
};
MenuFormID MenuWinClass::GetIDtoStr(string ID_Name){
    for (int X = 0; X < (int)MenuWinClass::IDSet.size(); X++){
        if (ID_Name.compare(IDSet[X].MFIDtoStr)==0){
            return IDSet[X].MFID;
        }
    }
}
/*################################################################################*/
FormSwitch MenuWinClass::SetFormWin[] = {
  [FORMWIN1] = {FORMWIN1, MenuWinClass::CreateForm1, MenuWinClass::ControlFormInput, MenuWinClass::DeleteForm},
  [FORMWIN2] = {FORMWIN2, MenuWinClass::CreateForm2, MenuWinClass::ControlFormInput, MenuWinClass::DeleteForm},
  [FORMWIN3] = {FORMWIN3, MenuWinClass::CreateForm3, MenuWinClass::ControlFormInput, MenuWinClass::DeleteForm},
  [FORMWIN4] = {FORMWIN4, MenuWinClass::CreateForm4, MenuWinClass::ControlFormInput, MenuWinClass::DeleteForm},
  [FORMWIN5] = {FORMWIN5, MenuWinClass::CreateForm5, MenuWinClass::ControlFormInput, MenuWinClass::DeleteForm},
  [FORMWIN6] = {FORMWIN6, nullptr, MenuWinClass::ControlFormInput, MenuWinClass::DeleteForm},
  [FORMWIN7] = {FORMWIN7, nullptr, MenuWinClass::ControlFormInput, MenuWinClass::DeleteForm},
  [FORMWIN8] = {FORMWIN8, nullptr, MenuWinClass::ControlFormInput, MenuWinClass::DeleteForm},
};
vector<MenuSetup_> MenuWinClass::MenuSetup = {
    {0,"Name","Menü Punkt 1"},
    {1,"Name","Menü Punkt 2"},
    {2,"Name","Menü Punkt 3"},
    {3,"Name","Menü Punkt 4"},
    {4,"Name","Menü Punkt 5"},
};
/*################################################################################*/
void MenuWinClass::StartWin() {
    setlocale(LC_CTYPE, "de_DE.UTF-8");
    setlocale(LC_ALL, "de_DE.UTF-8");
    initscr();
    atexit([]{ MenuWinClassMWC->ENDE(); MenuWinClassMWC->StopWin(); });
    clear();
    noecho();
    curs_set(0);
    cbreak();
    //nl();
    keypad(stdscr, TRUE);
    start_color();
    if (has_colors() == FALSE) { endwin(); cout << "Your terminal does not support color\n" << endl; exit(1);}
    AppColor();
}
void MenuWinClass::StopWin() {
    endwin();
}
void MenuWinClass::AppColor() {
    start_color();
    use_default_colors();
    short MY_MARIN_BLUE = 240, MY_LIGHT_BLUE = 250, MY_DARK_BLACK = 0, MY_LIGHT_WHITE = 100;
    short R = 0, G = 0, B = 0;
    init_color(MY_MARIN_BLUE, R, G, static_cast<short int>(300));
    init_color(MY_LIGHT_BLUE, R, G, static_cast<short int>(850));
    init_color(MY_DARK_BLACK, R, G, B);
    init_color(MY_LIGHT_WHITE, 1000, 1000, 1000);
    int Transparent = -1;
    /* 0 black, 1 red, 2 green, 3 yellow, 4 blue, 5 magenta, 6 cyan, 7 white, 8 marin blue, 9 light blue */
    /* hintergrund Transparent */
    init_pair(0,  MY_DARK_BLACK,  Transparent);
    init_pair(10, COLOR_RED,      Transparent);
    init_pair(20, COLOR_GREEN,    Transparent);
    init_pair(30, COLOR_YELLOW,   Transparent);
    init_pair(40, COLOR_BLUE,     Transparent);
    init_pair(50, COLOR_MAGENTA,  Transparent);
    init_pair(60, COLOR_CYAN,     Transparent);
    init_pair(70, MY_LIGHT_WHITE, Transparent);
    init_pair(80, MY_MARIN_BLUE,  Transparent);
    init_pair(90, MY_LIGHT_BLUE,  Transparent);
    /* hintergrund Red */
    init_pair(1, MY_DARK_BLACK,  COLOR_RED);
    init_pair(11, COLOR_RED,      COLOR_RED);
    init_pair(21, COLOR_GREEN,    COLOR_RED);
    init_pair(31, COLOR_YELLOW,   COLOR_RED);
    init_pair(41, COLOR_BLUE,     COLOR_RED);
    init_pair(51, COLOR_MAGENTA,  COLOR_RED);
    init_pair(61, COLOR_CYAN,     COLOR_RED);
    init_pair(71, MY_LIGHT_WHITE, COLOR_RED);
    init_pair(81, MY_MARIN_BLUE,  COLOR_RED);
    init_pair(91, MY_LIGHT_BLUE,  COLOR_RED);
    /* hintergrund Green */
    init_pair(2, MY_DARK_BLACK,  COLOR_GREEN);
    init_pair(12, COLOR_RED,      COLOR_GREEN);
    init_pair(22, COLOR_GREEN,    COLOR_GREEN);
    init_pair(32, COLOR_YELLOW,   COLOR_GREEN);
    init_pair(42, COLOR_BLUE,     COLOR_GREEN);
    init_pair(52, COLOR_MAGENTA,  COLOR_GREEN);
    init_pair(62, COLOR_CYAN,     COLOR_GREEN);
    init_pair(72, MY_LIGHT_WHITE, COLOR_GREEN);
    init_pair(82, MY_MARIN_BLUE,  COLOR_GREEN);
    init_pair(92, MY_LIGHT_BLUE,  COLOR_GREEN);
    /* hintergrund Yellow */
    init_pair(3, MY_DARK_BLACK,  COLOR_YELLOW);
    init_pair(13, COLOR_RED,      COLOR_YELLOW);
    init_pair(23, COLOR_GREEN,    COLOR_YELLOW);
    init_pair(33, COLOR_YELLOW,   COLOR_YELLOW);
    init_pair(43, COLOR_BLUE,     COLOR_YELLOW);
    init_pair(53, COLOR_MAGENTA,  COLOR_YELLOW);
    init_pair(63, COLOR_CYAN,     COLOR_YELLOW);
    init_pair(73, MY_LIGHT_WHITE, COLOR_YELLOW);
    init_pair(83, MY_MARIN_BLUE,  COLOR_YELLOW);
    init_pair(93, MY_LIGHT_BLUE,  COLOR_YELLOW);
    /* hintergrund Blue */
    init_pair(4, MY_DARK_BLACK,  COLOR_BLUE);
    init_pair(14, COLOR_RED,      COLOR_BLUE);
    init_pair(24, COLOR_GREEN,    COLOR_BLUE);
    init_pair(34, COLOR_YELLOW,   COLOR_BLUE);
    init_pair(44, COLOR_BLUE,     COLOR_BLUE);
    init_pair(54, COLOR_MAGENTA,  COLOR_BLUE);
    init_pair(64, COLOR_CYAN,     COLOR_BLUE);
    init_pair(74, MY_LIGHT_WHITE, COLOR_BLUE);
    init_pair(84, MY_MARIN_BLUE,  COLOR_BLUE);
    init_pair(94, MY_LIGHT_BLUE,  COLOR_BLUE);
    /* hintergrund Magenta */
    init_pair(5, MY_DARK_BLACK,  COLOR_MAGENTA);
    init_pair(15, COLOR_RED,      COLOR_MAGENTA);
    init_pair(25, COLOR_GREEN,    COLOR_MAGENTA);
    init_pair(35, COLOR_YELLOW,   COLOR_MAGENTA);
    init_pair(45, COLOR_BLUE,     COLOR_MAGENTA);
    init_pair(55, COLOR_MAGENTA,  COLOR_MAGENTA);
    init_pair(65, COLOR_CYAN,     COLOR_MAGENTA);
    init_pair(75, MY_LIGHT_WHITE, COLOR_MAGENTA);
    init_pair(85, MY_MARIN_BLUE,  COLOR_MAGENTA);
    init_pair(95, MY_LIGHT_BLUE,  COLOR_MAGENTA);
    /* hintergrund Cyan */
    init_pair(6, MY_DARK_BLACK,  COLOR_CYAN);
    init_pair(16, COLOR_RED,      COLOR_CYAN);
    init_pair(26, COLOR_GREEN,    COLOR_CYAN);
    init_pair(36, COLOR_YELLOW,   COLOR_CYAN);
    init_pair(46, COLOR_BLUE,     COLOR_CYAN);
    init_pair(56, COLOR_MAGENTA,  COLOR_CYAN);
    init_pair(66, COLOR_CYAN,     COLOR_CYAN);
    init_pair(76, MY_LIGHT_WHITE, COLOR_CYAN);
    init_pair(86, MY_MARIN_BLUE,  COLOR_CYAN);
    init_pair(96, MY_LIGHT_BLUE,  COLOR_CYAN);
    /* hintergrund White */
    init_pair(7, MY_DARK_BLACK,  MY_LIGHT_WHITE);
    init_pair(17, COLOR_RED,      MY_LIGHT_WHITE);
    init_pair(27, COLOR_GREEN,    MY_LIGHT_WHITE);
    init_pair(37, COLOR_YELLOW,   MY_LIGHT_WHITE);
    init_pair(47, COLOR_BLUE,     MY_LIGHT_WHITE);
    init_pair(57, COLOR_MAGENTA,  MY_LIGHT_WHITE);
    init_pair(67, COLOR_CYAN,     MY_LIGHT_WHITE);
    init_pair(77, MY_LIGHT_WHITE, MY_LIGHT_WHITE);
    init_pair(87, MY_MARIN_BLUE,  MY_LIGHT_WHITE);
    init_pair(97, MY_LIGHT_BLUE,  MY_LIGHT_WHITE);
    /* hintergrund Marin Blau */
    init_pair(8,  MY_DARK_BLACK,  MY_MARIN_BLUE);
    init_pair(18, COLOR_RED,      MY_MARIN_BLUE);
    init_pair(28, COLOR_GREEN,    MY_MARIN_BLUE);
    init_pair(38, COLOR_YELLOW,   MY_MARIN_BLUE);
    init_pair(48, COLOR_BLUE,     MY_MARIN_BLUE);
    init_pair(58, COLOR_MAGENTA,  MY_MARIN_BLUE);
    init_pair(68, COLOR_CYAN,     MY_MARIN_BLUE);
    init_pair(78, MY_LIGHT_WHITE, MY_MARIN_BLUE);
    init_pair(88, MY_MARIN_BLUE,  MY_MARIN_BLUE);
    init_pair(98, MY_LIGHT_BLUE,  MY_MARIN_BLUE);
    /* hintergrund Light Blue */
    init_pair(9,  MY_DARK_BLACK,  MY_LIGHT_BLUE);
    init_pair(19, COLOR_RED,      MY_LIGHT_BLUE);
    init_pair(29, COLOR_GREEN,    MY_LIGHT_BLUE);
    init_pair(39, COLOR_YELLOW,   MY_LIGHT_BLUE);
    init_pair(49, COLOR_BLUE,     MY_LIGHT_BLUE);
    init_pair(59, COLOR_MAGENTA,  MY_LIGHT_BLUE);
    init_pair(69, COLOR_CYAN,     MY_LIGHT_BLUE);
    init_pair(79, MY_LIGHT_WHITE, MY_LIGHT_BLUE);
    init_pair(89, MY_MARIN_BLUE,  MY_LIGHT_BLUE);
    init_pair(99, MY_LIGHT_BLUE,  MY_LIGHT_BLUE);
}
void MenuWinClass::SetWinSize() {
    START.WCX();
    START.HRY();
    START.HRYw1();
    START.WCXw1();
    START.HRYw2();
    START.WCXw2();
    START.HRYw3();
    START.WCXw3();
    START.HRYw4();
    START.WCXw4();
    START.HRYw5();
    START.WCXw5();
    START.TMPWin1 = newwin(START.HRYw1(), START.WCXw1(), 0, 0);
    START.TMPWin2 = newwin(START.HRYw2(), START.WCXw2(), 0, START.WCXw1());
    START.TMPWin3 = newpad(START.HRYw3(), START.WCXw3());
    START.TMPWin4 = newwin(START.HRYw4(), START.WCXw4(), 1, START.WCXw1()+1);
    START.TMPWin5 = newpad(START.HRYw5(), START.WCXw5());
}
void MenuWinClass::CreateWin(WINDOW* win, WinID WID, int TempHRY = MenuWinClassMWC->START.HRYw3(), int TempWCX = MenuWinClassMWC->START.WCXw3()) {
    switch (WID) {
    case MENU_Win_1: { /*TMPWin1*/
        if (!win) { win = newwin(START.HRYw1(), START.WCXw1(), 0, 0); };
        box(win, 0, 0);
        wbkgd(win, COLOR_PAIR(START.WinColor.BK_MENUWIN));
        Hauptmenu();
        break; }
    case MAIN_Win_2: { /*TMPWin2*/
        if (!win) { win = newwin(START.HRYw2(), START.WCXw2(), 0, START.WCXw1()); };
        box(win, 0, 0);
        wbkgd(win, COLOR_PAIR(START.WinColor.BK_MAINWIN));
        wattr_on(win, COLOR_PAIR(START.WinColor.BK_MAINWIN) | A_BOLD, nullptr);
        mvwaddnstr(win, START.HRYw2() -1, START.WCXw2() - 14, "[ EXIT F12 ]", -1); //12+2
        mvwaddnstr(win, START.HRYw2() -1, START.WCXw2() - 26, "[ MENÜ TAB ]", -1); //11+2
        wattr_off(win, COLOR_PAIR(START.WinColor.BK_MAINWIN) | A_BOLD, nullptr);
        wsetscrreg(win, 0, START.HRYw2() - 2);
        scrollok(win, true);
        syncok(win, true);
        break; }
    case FORM_Win_3: { /*TMPWin3*/
        if (!win) { win = newpad(START.HRYw3(), START.WCXw3()); };
        win = derwin(START.TMPWin2, TempHRY, TempWCX, 1, START.WCXw1()+1);
        wbkgd(win, COLOR_PAIR(START.WinColor.BK_MAINWIN));
        break; }
    case MENU_Win_4: { /*TMPWin4 */
        if (!win) { win = newwin(START.HRYw4(), START.WCXw4(), 1, START.WCXw1()+1); };
        win = subwin(START.TMPWin2, 6, START.WCXw4(), 1, START.WCXw1()+1);
        wbkgd(win, COLOR_PAIR(START.WinColor.BK_LISTPAD));
        break; }
    case MENU_Win_5: {
        if (!win) { win = newwin(START.HRYw5(), START.WCXw5(), 1, 1); };
        wbkgd(win, COLOR_PAIR(START.WinColor.BK_MAINWIN));
        break; }
    case ENDWIN:  { break; }
    }
    refresh();
    wrefresh(win);
}
void MenuWinClass::ResizeHandler(int signal){
    UNUSED(signal);
    MenuWinClassMWC->StopWin();
    MenuWinClassMWC->StartWin();
    MenuWinClassMWC->SetWinSize();
    MenuWinClassMWC->CreateWin(MenuWinClassMWC->START.TMPWin1, MENU_Win_1);
    MenuWinClassMWC->CreateWin(MenuWinClassMWC->START.TMPWin2, MAIN_Win_2);
    MenuWinClassMWC->CreateWin(MenuWinClassMWC->START.TMPWin3, FORM_Win_3);
    MenuWinClassMWC->CreateWin(MenuWinClassMWC->START.TMPWin4, MENU_Win_4);
    MenuWinClassMWC->CreateWin(MenuWinClassMWC->START.TMPWin5, MENU_Win_5, MenuWinClassMWC->START.HRYw5(), MenuWinClassMWC->START.WCXw5());
    refresh();
    wrefresh(MenuWinClassMWC->START.TMPWin1);
    touchwin(MenuWinClassMWC->START.TMPWin2);
    wrefresh(MenuWinClassMWC->START.TMPWin2);
    prefresh(MenuWinClassMWC->START.TMPWin3, 0, 0, 6, MenuWinClassMWC->START.WCXw1() +1, MenuWinClassMWC->START.HRY() -2, MenuWinClassMWC->START.WCX() -2);
    prefresh(MenuWinClassMWC->START.TMPWin4, 0, 0, 1, MenuWinClassMWC->START.WCXw1() +1, 4, MenuWinClassMWC->START.WCX() -2);
}
void MenuWinClass::FensterDraw() {
    CreateWin(START.TMPWin1, MENU_Win_1);
    CreateWin(START.TMPWin2, MAIN_Win_2);
    CreateWin(START.TMPWin3, FORM_Win_3);
    CreateWin(START.TMPWin4, MENU_Win_4);
}
/*################################################################################*/
void MenuWinClass::StartMenuAuswahl(string MenuPoint){
    if (MenuPoint.compare("Form 1") == 0) {
        MenuWinClassMWC->TabWin = { .ActiveTab = MainTab2, .MaxTab = MainTab3,
                                    .MFID1 = MENU_MAIN, .MFID2 = INLINEMENU1, .MFID3 = FORMWIN1 };
        //MenuWinClassMWC->SetFormWin[MenuWinClassMWC->TabWin.MFID2].FormStart();
        MenuWinClassMWC->CreateForm1();
        MenuWinClassMWC->AusWahlMenu();
    } else if (MenuPoint.compare("Form 2") == 0) {
        MenuWinClassMWC->TabWin = { .ActiveTab = MainTab2, .MaxTab = MainTab3,
                                    .MFID1 = MENU_MAIN, .MFID2 = INLINEMENU1, .MFID3 = FORMWIN2 };
        MenuWinClassMWC->CreateForm2();
        MenuWinClassMWC->AusWahlMenu();
    } else if (MenuPoint.compare("Form 3") == 0) {
        MenuWinClassMWC->TabWin = { .ActiveTab = MainTab2, .MaxTab = MainTab2,
                                    .MFID1 = MENU_MAIN, .MFID2 = FORMWIN3, .MFID3 = ENDMENUFORM };
        MenuWinClassMWC->CreateForm3();
    } else if (MenuPoint.compare("Form 4") == 0) {
        MenuWinClassMWC->TabWin = { .ActiveTab = MainTab2, .MaxTab = MainTab2,
                                    .MFID1 = MENU_MAIN, .MFID2 = FORMWIN4, .MFID3 = ENDMENUFORM };
        MenuWinClassMWC->CreateForm4();
    } else if (MenuPoint.compare("Form 5") == 0) {
        MenuWinClassMWC->TabWin = { .ActiveTab = MainTab2, .MaxTab = MainTab2,
                                    .MFID1 = MENU_MAIN, .MFID2 = FORMWIN5, .MFID3 = ENDMENUFORM };
        MenuWinClassMWC->CreateForm5();
    } else if (MenuPoint.compare("Form 6") == 0) {
        MenuWinClassMWC->TabWin = { .ActiveTab = MainTab2, .MaxTab = MainTab2,
                                    .MFID1 = MENU_MAIN, .MFID2 = FORMWIN6, .MFID3 = ENDMENUFORM };

    } else if (MenuPoint.compare("Form 7") == 0) {
        MenuWinClassMWC->TabWin = { .ActiveTab = MainTab1, .MaxTab = MainTab2,
                                    .MFID1 = MENU_MAIN, .MFID2 = FORMWIN7, .MFID3 = ENDMENUFORM };

    } else if (MenuPoint.compare("Form 8") == 0) {
        MenuWinClassMWC->TabWin = { .ActiveTab = MainTab2, .MaxTab = MainTab2,
                                    .MFID1 = MENU_MAIN, .MFID2 = FORMWIN8, .MFID3 = ENDMENUFORM };

    }
}
void MenuWinClass::Hauptmenu() {
    TOPMENU.HMItem = static_cast<ITEM**>(calloc(10, sizeof(ITEM*)));
    TOPMENU.HMItem[0] = new_item("Form 1", "FORMWIN1");
    TOPMENU.HMItem[1] = new_item("Form 2", "FORMWIN2");
    TOPMENU.HMItem[2] = new_item("Form 3", "FORMWIN3");
    TOPMENU.HMItem[3] = new_item("Form 4", "FORMWIN4");
    TOPMENU.HMItem[4] = new_item("Form 5", "FORMWIN5");
    TOPMENU.HMItem[5] = new_item("─────────────────", "─────────────────");
    TOPMENU.HMItem[6] = new_item("Form 6", "FORMWIN6");
    TOPMENU.HMItem[7] = new_item("Form 7", "FORMWIN7");
    TOPMENU.HMItem[8] = new_item("Form 8", "FORMWIN8");
    TOPMENU.HMItem[9] = nullptr;
    TOPMENU.HMMenu = new_menu(TOPMENU.HMItem);
    START.TMPWin1 = newwin(START.HRYw1(), START.WCXw1(), 0, 0);
    set_menu_win(TOPMENU.HMMenu, START.TMPWin1);
    set_menu_sub(TOPMENU.HMMenu, derwin(START.TMPWin1, 0, 0, 1, 1));
    set_menu_spacing(TOPMENU.HMMenu, 0, 0, 0);
    set_menu_format(TOPMENU.HMMenu, 11, 0);
    item_opts_off(TOPMENU.HMItem[5], O_SELECTABLE);
    menu_opts_off(TOPMENU.HMMenu, O_SHOWDESC);
    menu_opts_off(TOPMENU.HMMenu, O_NONCYCLIC);
    wbkgd(START.TMPWin1, COLOR_PAIR(TOPMENU.MenuColor.BK_MAINMENU));
    box(START.TMPWin1, 0, 0);
    set_menu_fore(TOPMENU.HMMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_AKTIVHAME) | A_BOLD);
    set_menu_back(TOPMENU.HMMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_MAINMENU));
    set_menu_grey(TOPMENU.HMMenu, COLOR_PAIR(TOPMENU.MenuColor.BK_UNUSEDHM));
    set_menu_mark(TOPMENU.HMMenu, ">");
    post_menu(TOPMENU.HMMenu);
}
void MenuWinClass::AusWahlMenu() {
    if (INAPPMENU.InApMenu1 != nullptr) { DeleteMenu(INAPPMENU.InApMenu1, INAPPMENU.InApItem1); };
    if (START.TMPWin4 != nullptr) { delwin(START.TMPWin4); endwin();}
    int MenuFelder = (int)MenuSetup.size(), mrows, mcols;

    mvwhline(START.TMPWin2, 5, 0, ACS_LTEE, 1);
    mvwhline(START.TMPWin2, 5, START.WCX()-START.WCXw1()-1, ACS_RTEE, 1);
    mvwhline(START.TMPWin2, 5, 1, ACS_HLINE, START.WCX()-START.WCXw1()-2);

    INAPPMENU.InApItem1 = static_cast<ITEM**>(calloc(MenuFelder, sizeof(ITEM*)));
    for (int X = 0;X < MenuFelder;X++ ) {
        INAPPMENU.InApItem1[X] = new_item(MenuWinClassMWC->MenuSetup[X].Value.c_str(), "FORMWIN1");
    }
    INAPPMENU.InApItem1[MenuFelder] = nullptr;

    INAPPMENU.InApMenu1 = new_menu(INAPPMENU.InApItem1);
    scale_menu(INAPPMENU.InApMenu1, &mrows, &mcols);
    START.TMPWin4 = newwin(mrows, START.WCXw4(), 1, START.WCXw1() + 1);
    START.TMPWin4 = subwin(START.TMPWin2, 4, START.WCXw4(), 1, START.WCXw1()+1);
    set_menu_win(INAPPMENU.InApMenu1, START.TMPWin2);
    set_menu_sub(INAPPMENU.InApMenu1, START.TMPWin4);

    set_menu_spacing(INAPPMENU.InApMenu1, 0, 0, 0);
    set_menu_format(INAPPMENU.InApMenu1, MenuFelder+1, 0);
    menu_opts_off(INAPPMENU.InApMenu1, O_SHOWDESC);
    menu_opts_on(INAPPMENU.InApMenu1, O_ROWMAJOR|O_NONCYCLIC);

    wbkgd(START.TMPWin4, COLOR_PAIR(INAPPMENU.InAppColor.BK_InAppMENU));
    set_menu_fore(INAPPMENU.InApMenu1, COLOR_PAIR(INAPPMENU.InAppColor.BK_InAppMENU) | A_BOLD);
    set_menu_back(INAPPMENU.InApMenu1, COLOR_PAIR(INAPPMENU.InAppColor.BK_InAppMENU));
    set_menu_grey(INAPPMENU.InApMenu1, COLOR_PAIR(INAPPMENU.InAppColor.BK_InAppMENU));
    set_menu_mark(INAPPMENU.InApMenu1, "");
    post_menu(INAPPMENU.InApMenu1);
};

void MenuWinClass::CreateForm1(){
    if (MenuWinClassMWC->FORMPAGE.TMPForm1 != nullptr) { MenuWinClassMWC->DeleteForm(MenuWinClassMWC->FORMPAGE.TMPForm1,MenuWinClassMWC->FORMPAGE.TMPField1); }
    if (MenuWinClassMWC->START.TMPWin3 != nullptr) { delwin(MenuWinClassMWC->START.TMPWin3); endwin(); };

    /* Felder erzeugen */
    int FieldWCX = 57, Felder = 2, StartFeld = 6;
    MenuWinClassMWC->FORMPAGE.TMPField1 = static_cast<FIELD **>(calloc(Felder, sizeof(FIELD *)));
    for (int X = 0,B = 0; X < Felder; X++, B++ ) {
        MenuWinClassMWC->FORMPAGE.TMPField1[X] = new_field(1, FieldWCX, StartFeld+X+B, 1, 0, 0);
        set_field_back(MenuWinClassMWC->FORMPAGE.TMPField1[X], COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.BK_CONFFILD)|A_UNDERLINE);
        field_opts_off(MenuWinClassMWC->FORMPAGE.TMPField1[X], O_AUTOSKIP);
    }
    MenuWinClassMWC->FORMPAGE.TMPField1[Felder] = nullptr;
    /* Felder erzeugen ENDE */

    MenuWinClassMWC->FORMPAGE.TMPForm1 = new_form(MenuWinClassMWC->FORMPAGE.TMPField1);
    scale_form(MenuWinClassMWC->FORMPAGE.TMPForm1, &MenuWinClassMWC->START.PadMaxHRY, &MenuWinClassMWC->START.PadMaxWCX);

    if (MenuWinClassMWC->START.PadMaxHRY > MenuWinClassMWC->START.HRYw3()) {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.PadMaxHRY + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    } else {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.HRYw3() + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    };

    MenuWinClassMWC->START.TMPWin3 = newpad(MenuWinClassMWC->START.PadMaxHRY, MenuWinClassMWC->START.PadMaxWCX);
    wbkgd(MenuWinClassMWC->START.TMPWin3, COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.Form1));
    set_form_win(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin2);
    set_form_sub(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin3);
    post_form(MenuWinClassMWC->FORMPAGE.TMPForm1);

    wattrset(MenuWinClassMWC->START.TMPWin3, A_BOLD);
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 1, 1, MenuWinClassMWC->IDSet[0].Textfeld.c_str());
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 5, 1, "Feld 1: →");
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 7, 1, "Feld 2: →");

    refresh();
    touchwin(MenuWinClassMWC->START.TMPWin2);
    wrefresh(MenuWinClassMWC->START.TMPWin2);
    prefresh(MenuWinClassMWC->START.TMPWin3, 0, 0,
             6, MenuWinClassMWC->START.WCXw1() + 1,
             MenuWinClassMWC->START.HRY() - 2, MenuWinClassMWC->START.WCX() - 2);
}
void MenuWinClass::CreateForm2(){
    if (MenuWinClassMWC->FORMPAGE.TMPForm1 != nullptr) { MenuWinClassMWC->DeleteForm(MenuWinClassMWC->FORMPAGE.TMPForm1,MenuWinClassMWC->FORMPAGE.TMPField1); }
    if (MenuWinClassMWC->START.TMPWin3 != nullptr) { delwin(MenuWinClassMWC->START.TMPWin3); endwin(); };

    /* Felder erzeugen */
    int FieldWCX = 57, Felder = 2, StartFeld = 6;
    MenuWinClassMWC->FORMPAGE.TMPField1 = static_cast<FIELD **>(calloc(Felder, sizeof(FIELD *)));
    for (int X = 0,B = 0; X < Felder; X++, B++ ) {
        MenuWinClassMWC->FORMPAGE.TMPField1[X] = new_field(1, FieldWCX, StartFeld+X+B, 1, 0, 0);
        set_field_back(MenuWinClassMWC->FORMPAGE.TMPField1[X], COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.BK_CONFFILD)|A_UNDERLINE);
        field_opts_off(MenuWinClassMWC->FORMPAGE.TMPField1[X], O_AUTOSKIP);
    }
    MenuWinClassMWC->FORMPAGE.TMPField1[Felder] = nullptr;
    /* Felder erzeugen ENDE */

    MenuWinClassMWC->FORMPAGE.TMPForm1 = new_form(MenuWinClassMWC->FORMPAGE.TMPField1);
    scale_form(MenuWinClassMWC->FORMPAGE.TMPForm1, &MenuWinClassMWC->START.PadMaxHRY, &MenuWinClassMWC->START.PadMaxWCX);

    if (MenuWinClassMWC->START.PadMaxHRY > MenuWinClassMWC->START.HRYw3()) {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.PadMaxHRY + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    } else {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.HRYw3() + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    };

    MenuWinClassMWC->START.TMPWin3 = newpad(MenuWinClassMWC->START.PadMaxHRY, MenuWinClassMWC->START.PadMaxWCX);
    wbkgd(MenuWinClassMWC->START.TMPWin3, COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.Form2));
    set_form_win(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin2);
    set_form_sub(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin3);
    post_form(MenuWinClassMWC->FORMPAGE.TMPForm1);

    wattrset(MenuWinClassMWC->START.TMPWin3, A_BOLD);
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 1, 1, MenuWinClassMWC->IDSet[1].Textfeld.c_str());
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 5, 1, "Feld 1: →");
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 7, 1, "Feld 2: →");

    refresh();
    touchwin(MenuWinClassMWC->START.TMPWin2);
    wrefresh(MenuWinClassMWC->START.TMPWin2);
    prefresh(MenuWinClassMWC->START.TMPWin3, 0, 0,
             1, MenuWinClassMWC->START.WCXw1() + 1,
             MenuWinClassMWC->START.HRY() - 2, MenuWinClassMWC->START.WCX() - 2);
}
void MenuWinClass::CreateForm3(){
    if (MenuWinClassMWC->FORMPAGE.TMPForm1 != nullptr) { MenuWinClassMWC->DeleteForm(MenuWinClassMWC->FORMPAGE.TMPForm1,MenuWinClassMWC->FORMPAGE.TMPField1); }
    if (MenuWinClassMWC->START.TMPWin3 != nullptr) { delwin(MenuWinClassMWC->START.TMPWin3); endwin(); };

    /* Felder erzeugen */
    int FieldWCX = 57, Felder = 2, StartFeld = 6;
    MenuWinClassMWC->FORMPAGE.TMPField1 = static_cast<FIELD **>(calloc(Felder, sizeof(FIELD *)));
    for (int X = 0,B = 0; X < Felder; X++, B++ ) {
        MenuWinClassMWC->FORMPAGE.TMPField1[X] = new_field(1, FieldWCX, StartFeld+X+B, 1, 0, 0);
        set_field_back(MenuWinClassMWC->FORMPAGE.TMPField1[X], COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.BK_CONFFILD)|A_UNDERLINE);
        field_opts_off(MenuWinClassMWC->FORMPAGE.TMPField1[X], O_AUTOSKIP);
    }
    MenuWinClassMWC->FORMPAGE.TMPField1[Felder] = nullptr;
    /* Felder erzeugen ENDE */

    MenuWinClassMWC->FORMPAGE.TMPForm1 = new_form(MenuWinClassMWC->FORMPAGE.TMPField1);
    scale_form(MenuWinClassMWC->FORMPAGE.TMPForm1, &MenuWinClassMWC->START.PadMaxHRY, &MenuWinClassMWC->START.PadMaxWCX);

    if (MenuWinClassMWC->START.PadMaxHRY > MenuWinClassMWC->START.HRYw3()) {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.PadMaxHRY + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    } else {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.HRYw3() + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    };

    MenuWinClassMWC->START.TMPWin3 = newpad(MenuWinClassMWC->START.PadMaxHRY, MenuWinClassMWC->START.PadMaxWCX);
    wbkgd(MenuWinClassMWC->START.TMPWin3, COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.Form3));
    set_form_win(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin2);
    set_form_sub(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin3);
    post_form(MenuWinClassMWC->FORMPAGE.TMPForm1);

    wattrset(MenuWinClassMWC->START.TMPWin3, A_BOLD);
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 1, 1, MenuWinClassMWC->IDSet[2].Textfeld.c_str());
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 5, 1, "Feld 1: →");
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 7, 1, "Feld 2: →");

    refresh();
    touchwin(MenuWinClassMWC->START.TMPWin2);
    wrefresh(MenuWinClassMWC->START.TMPWin2);
    prefresh(MenuWinClassMWC->START.TMPWin3, 0, 0,
             1, MenuWinClassMWC->START.WCXw1() + 1,
             MenuWinClassMWC->START.HRY() - 2, MenuWinClassMWC->START.WCX() - 2);
}
void MenuWinClass::CreateForm4(){
    if (MenuWinClassMWC->FORMPAGE.TMPForm1 != nullptr) { MenuWinClassMWC->DeleteForm(MenuWinClassMWC->FORMPAGE.TMPForm1,MenuWinClassMWC->FORMPAGE.TMPField1); }
    if (MenuWinClassMWC->START.TMPWin3 != nullptr) { delwin(MenuWinClassMWC->START.TMPWin3); endwin(); };

    /* Felder erzeugen */
    int FieldWCX = 57, Felder = 5, StartFeld = 6;
    MenuWinClassMWC->FORMPAGE.TMPField1 = static_cast<FIELD **>(calloc(Felder, sizeof(FIELD *)));
    for (int X = 0,B = 0; X < Felder; X++, B++ ) {
        MenuWinClassMWC->FORMPAGE.TMPField1[X] = new_field(1, FieldWCX, StartFeld+X+B, 1, 0, 0);
        set_field_back(MenuWinClassMWC->FORMPAGE.TMPField1[X], COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.BK_CONFFILD)|A_UNDERLINE);
        field_opts_off(MenuWinClassMWC->FORMPAGE.TMPField1[X], O_AUTOSKIP);
    }
    MenuWinClassMWC->FORMPAGE.TMPField1[Felder] = nullptr;
    /* Felder erzeugen ENDE */

    MenuWinClassMWC->FORMPAGE.TMPForm1 = new_form(MenuWinClassMWC->FORMPAGE.TMPField1);
    scale_form(MenuWinClassMWC->FORMPAGE.TMPForm1, &MenuWinClassMWC->START.PadMaxHRY, &MenuWinClassMWC->START.PadMaxWCX);

    if (MenuWinClassMWC->START.PadMaxHRY > MenuWinClassMWC->START.HRYw3()) {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.PadMaxHRY + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    } else {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.HRYw3() + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    };

    MenuWinClassMWC->START.TMPWin3 = newpad(MenuWinClassMWC->START.PadMaxHRY, MenuWinClassMWC->START.PadMaxWCX);
    wbkgd(MenuWinClassMWC->START.TMPWin3, COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.Form4));
    set_form_win(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin2);
    set_form_sub(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin3);
    post_form(MenuWinClassMWC->FORMPAGE.TMPForm1);

    wattrset(MenuWinClassMWC->START.TMPWin3, A_BOLD);
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 1, 1, MenuWinClassMWC->IDSet[3].Textfeld.c_str());
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 5, 1, "Feld 1: ↓");
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 7, 1, "Feld 2: ↓");
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 9, 1, "Feld 3: ↓");
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 11, 1, "Feld 4: ↓");
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 13, 1, "Feld 5: ↓");

    refresh();
    touchwin(MenuWinClassMWC->START.TMPWin2);
    wrefresh(MenuWinClassMWC->START.TMPWin2);
    prefresh(MenuWinClassMWC->START.TMPWin3, 0, 0,
             1, MenuWinClassMWC->START.WCXw1() + 1,
             MenuWinClassMWC->START.HRY() - 2, MenuWinClassMWC->START.WCX() - 2);
}
void MenuWinClass::CreateForm5(){
    if (MenuWinClassMWC->FORMPAGE.TMPForm1 != nullptr) { MenuWinClassMWC->DeleteForm(MenuWinClassMWC->FORMPAGE.TMPForm1,MenuWinClassMWC->FORMPAGE.TMPField1); }
    if (MenuWinClassMWC->START.TMPWin3 != nullptr) { delwin(MenuWinClassMWC->START.TMPWin3); endwin(); };

    /* Felder erzeugen */
    int FieldWCX = 57, Felder = 2, StartFeld = 6;
    MenuWinClassMWC->FORMPAGE.TMPField1 = static_cast<FIELD **>(calloc(Felder, sizeof(FIELD *)));
    for (int X = 0,B = 0; X < Felder; X++, B++ ) {
        MenuWinClassMWC->FORMPAGE.TMPField1[X] = new_field(1, FieldWCX, StartFeld+X+B, 1, 0, 0);
        set_field_back(MenuWinClassMWC->FORMPAGE.TMPField1[X], COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.BK_CONFFILD)|A_UNDERLINE);
        field_opts_off(MenuWinClassMWC->FORMPAGE.TMPField1[X], O_AUTOSKIP);
    }
    MenuWinClassMWC->FORMPAGE.TMPField1[Felder] = nullptr;
    /* Felder erzeugen ENDE */

    MenuWinClassMWC->FORMPAGE.TMPForm1 = new_form(MenuWinClassMWC->FORMPAGE.TMPField1);
    scale_form(MenuWinClassMWC->FORMPAGE.TMPForm1, &MenuWinClassMWC->START.PadMaxHRY, &MenuWinClassMWC->START.PadMaxWCX);

    if (MenuWinClassMWC->START.PadMaxHRY > MenuWinClassMWC->START.HRYw3()) {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.PadMaxHRY + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    } else {
        MenuWinClassMWC->START.PadMaxHRY = MenuWinClassMWC->START.HRYw3() + 5;
        MenuWinClassMWC->START.PadMaxWCX = MenuWinClassMWC->START.WCXw3();
    };

    MenuWinClassMWC->START.TMPWin3 = newpad(MenuWinClassMWC->START.PadMaxHRY, MenuWinClassMWC->START.PadMaxWCX);
    wbkgd(MenuWinClassMWC->START.TMPWin3, COLOR_PAIR(MenuWinClassMWC->FORMPAGE.FormColor.Form5));
    set_form_win(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin2);
    set_form_sub(MenuWinClassMWC->FORMPAGE.TMPForm1, MenuWinClassMWC->START.TMPWin3);
    post_form(MenuWinClassMWC->FORMPAGE.TMPForm1);

    wattrset(MenuWinClassMWC->START.TMPWin3, A_BOLD);
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 1, 1, MenuWinClassMWC->IDSet[4].Textfeld.c_str());
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 5, 1, "Feld 1: ↓");
    mvwaddstr(MenuWinClassMWC->START.TMPWin3, 7, 1, "Feld 2: ↓");

    refresh();
    touchwin(MenuWinClassMWC->START.TMPWin2);
    wrefresh(MenuWinClassMWC->START.TMPWin2);
    prefresh(MenuWinClassMWC->START.TMPWin3, 0, 0,
             1, MenuWinClassMWC->START.WCXw1() + 1,
             MenuWinClassMWC->START.HRY() - 2, MenuWinClassMWC->START.WCX() - 2);
}

int MenuWinClass::ControlMainMenu(MENU* HauptMenu, int Key){
    //TOPMENU.HMMenu
    switch (Key) {
    case KEY_UP:{
        menu_driver(HauptMenu, REQ_UP_ITEM);
        break;}
    case KEY_DOWN:{
        menu_driver(HauptMenu, REQ_DOWN_ITEM);
        break;}
    case KEY_ENTER:
    case 10:{
        StartMenuAuswahl(string(item_name(current_item(HauptMenu))));
        break;}
    }
    refresh();
    wrefresh( (WINDOW *) START.TMPWin1);
    return Key;
}
int MenuWinClass::ControlAusWahlMenu(MENU* AusWahlMenu, int Key) {
    //INAPPMENU.InApMenu1
    switch (Key) {
    case KEY_UP:{
        menu_driver(AusWahlMenu, REQ_UP_ITEM);
        break;}
    case KEY_DOWN:{
        menu_driver(AusWahlMenu, REQ_DOWN_ITEM);
        break;}
    case KEY_LEFT:{
        menu_driver(AusWahlMenu, REQ_LEFT_ITEM);
        break;}
    case KEY_RIGHT:{
        menu_driver(AusWahlMenu, REQ_RIGHT_ITEM);
        break;}
    case KEY_ENTER:
    case 10:{
        START.ProID = item_index(current_item(AusWahlMenu));
        MenuWinClassMWC->TabWin.ActiveTab = MainTab3;
        break;}
    }
    START.ProID = item_index(current_item(AusWahlMenu));

    refresh();
    touchwin(START.TMPWin2);
    wrefresh(START.TMPWin2);
    prefresh(START.TMPWin3, 0, 0, 6, START.WCXw1() +1, START.HRY() -2, START.WCX() -2);
    prefresh(START.TMPWin4, 0, 0, 1, START.WCXw1() +1, 4, START.WCX() -2);
    return Key;
};
int MenuWinClass::ControlFormInput(WINDOW* SubWin, FORM* TmpFrom, int Key, int HRYvon, int WCXvon, int HRYbis, int WCXbis, int PadMaxHRY, int PadMaxWCX = MenuWinClassMWC->START.WCXw3()) {
    int rows = 0;
    int column = 0;
    keypad(SubWin, true);
    curs_set(1);

    refresh();
    touchwin(MenuWinClassMWC->START.TMPWin2);
    wrefresh(MenuWinClassMWC->START.TMPWin2);
    prefresh(SubWin, rows, column, HRYvon, WCXvon, HRYbis, WCXbis);

    while ((Key = getch()) != KEY_F(12)) {
        switch (Key) {
        case 127:
        case KEY_BACKSPACE: {
            form_driver(TmpFrom, REQ_DEL_PREV);
            break; }
        case KEY_DC: {
            form_driver(TmpFrom, REQ_DEL_CHAR);
            break; }
        case KEY_LEFT: {
            form_driver(TmpFrom, REQ_PREV_CHAR);
            if (getcurx(SubWin) >= (MenuWinClassMWC->START.WCX() - 2)) {
                if (column > 0) { column--; }
            }
            break; }
        case KEY_RIGHT: {
            form_driver(TmpFrom, REQ_NEXT_CHAR);
            if (getcurx(SubWin) >= (MenuWinClassMWC->START.WCX() - 2)) {
                if (column + WCXbis +1 <= PadMaxWCX) { column++; }
            }
            break; }
        case KEY_UP: {
            form_driver(TmpFrom, REQ_PREV_FIELD);
            form_driver(TmpFrom, REQ_END_LINE);
            if (getcury(SubWin) >= (MenuWinClassMWC->START.HRY() - 2)) {
                if (rows > 0) { rows--; }
            }
            break; }
        case KEY_DOWN: {
            form_driver(TmpFrom, REQ_NEXT_FIELD);
            form_driver(TmpFrom, REQ_END_LINE);
            if (getcury(SubWin) >= (MenuWinClassMWC->START.HRY() - 2)) {
                if (rows + HRYbis +1 <= PadMaxHRY) { rows++; }
            }
            break; }
        case KEY_PPAGE: { /* Page Up */
            form_driver(TmpFrom, REQ_PREV_PAGE);
            if (getcury(SubWin) >= (MenuWinClassMWC->START.HRY() - 2)) {
                if (rows > 0) { rows -= HRYbis; }
                if (rows < 0) { rows = 0; }
            }
            break; }
        case KEY_NPAGE: { /* Page Down */
            form_driver(TmpFrom, REQ_NEXT_PAGE);
            if (getcury(SubWin) >= (MenuWinClassMWC->START.HRY() - 2)) {
                if (rows + HRYbis +1 < PadMaxHRY) { rows += HRYbis; }
                if (rows + HRYbis + 1 > PadMaxHRY) { rows = PadMaxHRY - HRYbis - 1; }
            }
            break; }
        case KEY_HOME: {
            form_driver(TmpFrom, REQ_FIRST_FIELD);
            rows = 0;
            break; }
        case KEY_END: {
            form_driver(TmpFrom, REQ_LAST_FIELD);
            if (getcury(SubWin) >= (MenuWinClassMWC->START.HRY() - 2)) {
                rows = PadMaxHRY - HRYbis - 1;
            }
            break; }
        default: {
            if (((int)Key >= 40 ) || ((int)Key <= 177)) {
                form_driver(TmpFrom, Key);
//                if (form_driver(TmpFrom, REQ_VALIDATION) != E_OK) {
//                    // do something
//                }
            }
            break; }
        }
        refresh();
        touchwin(MenuWinClassMWC->START.TMPWin2);
        wrefresh(MenuWinClassMWC->START.TMPWin2);
        prefresh(SubWin, rows, column, HRYvon, WCXvon, HRYbis, WCXbis);

        if ((Key == 9) || (Key == 353) || (Key == KEY_F(12))) { break; }
    };
    keypad(stdscr, true);
    curs_set(false);
    return Key;
}
/*################################################################################*/
void MenuWinClass::DeleteForm(FORM* tmpF, FIELD** tmpFd){
    unpost_form(tmpF);
    for (int X = 0; X < tmpF->maxfield; X++) {
        free_field(tmpFd[X]);
    }
    free_form(tmpF);
    //delwin(tmpW);
}
void MenuWinClass::DeleteMenu(MENU* tmpMenu, ITEM** tmpItem){
    unpost_menu(tmpMenu);
    for (int X = 0; X < tmpMenu->nitems; X++) {
        free_item(tmpItem[X]);
    }
    free_menu(tmpMenu);
}
void MenuWinClass::ENDE(){
    if (START.TMPWin5 != nullptr) { delwin(START.TMPWin5); endwin();}
    if (START.TMPWin4 != nullptr) { delwin(START.TMPWin4); endwin();}
    if (FORMPAGE.TMPForm1 != nullptr) { DeleteForm(FORMPAGE.TMPForm1,FORMPAGE.TMPField1); }
    if (START.TMPWin3 != nullptr) { delwin(START.TMPWin3); endwin();}
    if (START.TMPWin2 != nullptr) { delwin(START.TMPWin2); endwin();}
    if (TOPMENU.HMMenu != nullptr) { DeleteMenu(TOPMENU.HMMenu, TOPMENU.HMItem); };
    if (START.TMPWin1 != nullptr) { delwin(START.TMPWin1); endwin();}
    werase(stdscr);
    clear();
    exit_curses(0);
}
/*################################################################################*/
int main() {
    werase(stdscr);
    MenuWinClassMWC->StartWin();
    signal(SIGWINCH, MenuWinClass::ResizeHandler);
    MenuWinClassMWC->SetWinSize();
    MenuWinClassMWC->FensterDraw();

    MenuWinClassMWC->TabWin.ActiveTab = MainTab1;
    MenuWinClassMWC->START.ProID = 0;

    refresh();
    wrefresh(MenuWinClassMWC->START.TMPWin1);
    wrefresh(MenuWinClassMWC->START.TMPWin2);

    int Key = 0;
     while ((Key = getch()) != KEY_F(12)) {
        switch (MenuWinClassMWC->TabWin.ActiveTab) {
        case MainTab1: {
            Key = MenuWinClassMWC->ControlMainMenu(MenuWinClassMWC->TOPMENU.HMMenu, Key);
            break; }
        case MainTab2: {
            if (MenuWinClassMWC->TabWin.ActiveTab < MenuWinClassMWC->TabWin.MaxTab) {
                Key = MenuWinClassMWC->ControlAusWahlMenu(MenuWinClassMWC->INAPPMENU.InApMenu1, Key);
            } else if (MenuWinClassMWC->TabWin.ActiveTab == MenuWinClassMWC->TabWin.MaxTab) {
                Key = MenuWinClassMWC->SetFormWin[MenuWinClassMWC->TabWin.MFID2].FormControl(MenuWinClassMWC->START.TMPWin3, MenuWinClassMWC->FORMPAGE.TMPForm1, Key,
                                                                                             1, MenuWinClassMWC->START.WCXw1() + 1,
                                                                                             MenuWinClassMWC->START.HRY() - 2, MenuWinClassMWC->START.WCX() - 2,
                                                                                             MenuWinClassMWC->START.PadMaxHRY, MenuWinClassMWC->START.PadMaxWCX);
            } else if (MenuWinClassMWC->TabWin.ActiveTab > MenuWinClassMWC->TabWin.MaxTab) {
                MenuWinClassMWC->TabWin.ActiveTab++;
            }
            break; }
        case MainTab3: {
            Key = MenuWinClassMWC->SetFormWin[MenuWinClassMWC->TabWin.MFID3].FormControl(MenuWinClassMWC->START.TMPWin3, MenuWinClassMWC->FORMPAGE.TMPForm1, Key,
                                                                                         6, MenuWinClassMWC->START.WCXw1() + 1,
                                                                                         MenuWinClassMWC->START.HRY() - 2, MenuWinClassMWC->START.WCX() - 2,
                                                                                         MenuWinClassMWC->START.PadMaxHRY, MenuWinClassMWC->START.PadMaxWCX);
            break; }
        }
        switch (Key) {
        case KEY_F(1): {

            break; }
        case 353: {
            MenuWinClassMWC->TabWin.ActiveTab--;
            while (MenuWinClassMWC->TabWin.ActiveTab > MenuWinClassMWC->TabWin.MaxTab) {
                MenuWinClassMWC->TabWin.ActiveTab--;
            }
            break; }
        case 9: {
            MenuWinClassMWC->TabWin.ActiveTab++;
            while (MenuWinClassMWC->TabWin.ActiveTab > MenuWinClassMWC->TabWin.MaxTab) {
                MenuWinClassMWC->TabWin.ActiveTab++;
            }
            break; }
        }
        if (Key == KEY_F(12)) { break; }
    };

    return 0;
}

void savewin(){
    MenuWinClass MWC;

    /* to save win to file */
    refresh();
    wrefresh(MWC.START.TMPWin3);
    world = fopen("world.win", "w");
    putwin(MWC.START.TMPWin3, world);
    fclose(world);

    /* to restore win from file */
    delwin(MWC.START.TMPWin3);
    world = fopen("world.win", "r");
    MWC.START.TMPWin3 = getwin(world);
    fclose(world);
    refresh();

}
