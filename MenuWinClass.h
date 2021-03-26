#ifndef MENUWINCLASS_H
#define MENUWINCLASS_H

#include <ncursesw/cursesapp.h>
#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <ncursesw/form.h>
#include <ncursesw/panel.h>
#include <ncursesw/unctrl.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <csignal>
#include <thread>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <vector>
#include <locale.h>
#include <term.h>
#include <algorithm>
#include <cassert>
#include <set>
#include <filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include <functional>

#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif
//#define CTRLD 4
#define BUFSIZE 8192
#define CLEARSCR system ( "clear" )
#define UNUSED(x) (void) (x)
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define SIZEOF(table) (sizeof(table) / sizeof(table[0]))
#define VARNAME(name) #name

using namespace std;

namespace WinFormMenu {

    enum WinID      { MENU_Win_1 = 0,
                      MAIN_Win_2 = 1,
                      FORM_Win_3 = 2,
                      MENU_Win_4 = 3,
                      MENU_Win_5 = 4,
                      ALLWIN = 5,
                      ENDWIN = 6 };
    enum MenuFormID { FORMWIN1 = 0,
                      FORMWIN2 = 1,
                      FORMWIN3 = 2,
                      FORMWIN4 = 3,
                      FORMWIN5 = 4,
                      FORMWIN6 = 5,
                      FORMWIN7 = 6,
                      FORMWIN8 = 7,
                      INLINEMENU1 = 8,
                      INLINEMENU2 = 9,
                      MENU_MAIN = 10,
                      ENDMENUFORM = 11};
    enum TabID      { MainTab1 = 1,
                      MainTab2 = 2,
                      MainTab3 = 3 };
    struct ID_Setup_ {
        int ID;
        MenuFormID MFID;
        string MFIDtoStr;
        WinID WID;
        string Textfeld;
    };
    struct FENSTER {
        static const WinID TMPWin1ID = MENU_Win_1;
        static const WinID TMPWin2ID = MAIN_Win_2;
        static const WinID TMPWin3ID = FORM_Win_3;
        static const WinID TMPWin4ID = MENU_Win_4;
        static const WinID TMPWin5ID = MENU_Win_5;
        int     ProID = 0;
        int     BorderWeight { 1 };
        int     BorderHeight { 1 };
        int     WCX()        { return static_cast<int>(roundf(getmaxx(stdscr))); };  /* W=weight C=column X=x achse */
        int     HRY()        { return static_cast<int>(roundf(getmaxy(stdscr))); };  /* H=height R=row    Y=y achse */
        int     HRYw1()      { return static_cast<int>(roundf(HRY())); };                                   /*w1 24 */
        int     WCXw1()      { return static_cast<int>(roundf(20)); };                                      /*w1 20 */
        int     HRYw2()      { return static_cast<int>(roundf(HRY())); };                                   /*w2 24 */
        int     WCXw2()      { return static_cast<int>(roundf(WCX() - WCXw1())); };                         /*w2 60 */
        int     HRYw3()      { return static_cast<int>(roundf(HRY() - (BorderHeight * 2))); };              /*w2 22 */
        int     WCXw3()      { return static_cast<int>(roundf(WCX() - (WCXw1() + (BorderWeight * 2)))); };  /*w3 58 */
        int     HRYw4()      { return static_cast<int>(roundf(HRY() - 2)); };                               /*w4 24 */
        int     WCXw4()      { return static_cast<int>(roundf(WCXw2() - (BorderWeight * 2))); };            /*w4 58 */
        int     HRYw5()      { return static_cast<int>(roundf(0)); };                                       /*w5 0  */
        int     WCXw5()      { return static_cast<int>(roundf(0)); };                                       /*w5 0  */
        int     PadMaxHRY    = HRYw3();
        int     PadMaxWCX    = WCXw3();
        WINDOW  *TMPWIN      { nullptr };
        WINDOW  *TMPWin1;//     = newwin(HRYw1(), WCXw1(), 0, 0);
        WINDOW  *TMPWin2;//     = newwin(HRYw2(), WCXw2(), 0, WCXw1());
        WINDOW  *TMPWin3;//     = newpad(HRYw3(), WCXw3());
        WINDOW  *TMPWin4;//     = newwin(HRYw4(), WCXw4(), 1, WCXw1() +1);
        WINDOW  *TMPWin5;//     = newpad(HRYw5(), WCXw5());
        union Size {
            int WCX()        { return static_cast<int>(roundf(getmaxx(stdscr))); };  /* W=weight C=column X=x achse */
            int HRY()        { return static_cast<int>(roundf(getmaxy(stdscr))); };
            int WCX_Real()   { return static_cast<int>(roundf(WCX() - (2 * 1))); };
            int HRY_Real()   { return static_cast<int>(roundf(HRY() - (2 * 1))); };
            int WCX_Center() { return static_cast<int>(roundf(WCX() / 2)); };
            int HRY_Center() { return static_cast<int>(roundf(HRY() / 2)); };
            int WCX_TmpWin(WINDOW *tmpwin)       { return static_cast<int>(roundf(getmaxx(tmpwin))); };
            int HRY_TmpWin(WINDOW *tmpwin)       { return static_cast<int>(roundf(getmaxy(tmpwin))); };
            int WCX_TmpWinReal(WINDOW *tmpwin)   { return static_cast<int>(roundf(getmaxx(tmpwin) - (1 * 2))); };
            int HRY_TmpWinReal(WINDOW *tmpwin)   { return static_cast<int>(roundf(getmaxy(tmpwin) - (1 * 2))); };
            int WCX_TmpWinCenter(WINDOW *tmpwin) { return static_cast<int>(roundf(getmaxx(tmpwin) / 2)); };
            int HRY_TmpWinCenter(WINDOW *tmpwin) { return static_cast<int>(roundf(getmaxy(tmpwin) / 2)); };
            unsigned long WinHalfDurch(WINDOW *tmpwin, int TeilDurch) { return static_cast<int>(roundf(WCX_TmpWinCenter(tmpwin) / TeilDurch)); };
        } WinSize;
        struct WinColor {
            int BK_MENUWIN = 70; // 78 Text=MY_LIGHT_WHITE, Bk=MY_MARIN_BLUE
            int BK_MAINWIN = 70; // 87 Text=MY_MARIN_BLUE, Bk=MY_LIGHT_WHITE
            int BK_INFOWIN = 20;
            int BK_LISTPAD = 70;
            int BK_DESCWIN = 70;
            int BK_TIMEWIN = 70;
            int BK_HELPWIN = 40;
        } WinColor;
        void delwinow(WINDOW *tmpwin){
            if(tmpwin){
                int mx,my,bx,by;
                getbegyx(tmpwin,by,bx);
                getmaxyx(tmpwin,my,mx);
                touchwin(tmpwin);
                wborder(tmpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                touchline(tmpwin,bx,mx);
                delwin(tmpwin);
                endwin();
                tmpwin=nullptr;
            }
        }
    };
    struct INPUTFORM: public FENSTER {
        int     WCXform = static_cast<int>(roundf(FENSTER::WCXw3() - 2));
        int     HRYform = static_cast<int>(roundf(FENSTER::HRYw3() - 2));
        int     FOID        {0};
        string  FONAME      {"SourceHistory"};
        int     TMPWinHigh;
        FORM    *TMPForm1   { nullptr };
        FIELD   **TMPField1 { nullptr };
        struct FormColor {
            int BK_PROJFILD = 20;
            int FO_PROJFILD = 20;
            int BK_CONFFILD = 20;
            int FO_CONFFILD = 20;
            int Form1 = 78;
            int Form2 = 7;
            int Form3 = 3;
            int Form4 = 72;
            int Form5 = 71;
        } FormColor;
    };
    struct HMENU {
        MENU    *HMMenu {nullptr};
        ITEM    **HMItem {nullptr};
        MENU    *TMPMENU; /* Temporärer Menu zwischen speicher */
        int     MeInAl {0};
        string  AktivName = "";
        struct  MenuColor {
            int BK_MAINMENU  = 70; // 78 Text=MY_LIGHT_WHITE, Bk=MY_MARIN_BLUE
            int BK_UNTERMENU = 70; // 87 Text=MY_MARIN_BLUE, Bk=MY_LIGHT_WHITE
            int BK_AKTIVHAME = 10;
            int BK_AKTIVUNME = 10;
            int BK_UNUSEDHM  = 70;
            int BK_UNUSEDUM  = 70;
        } MenuColor;
    };
    struct APPMENU {
        MENU*  InApMenu1  { nullptr };
        ITEM** InApItem1  { nullptr };
        MENU*  InApMenu2  { nullptr };
        ITEM** InApItem2  { nullptr };
        struct InAppColor {
            int BK_InAppMENU   = 20; // 78 Text=MY_LIGHT_WHITE, Bk=MY_MARIN_BLUE
            int BK_AKTIVInApp  = 10;
            int BK_UNUSEDInApp = 40;
        } InAppColor;
    };
    struct TabKey {
        TabID ActiveTab = MainTab1;
        TabID MaxTab;
        MenuFormID MFID1 = MENU_MAIN;
        MenuFormID MFID2;
        MenuFormID MFID3;
    };
    struct FormSwitch {
        MenuFormID MFID;
        void (*FormStart)();
        int (*FormControl)(WINDOW* SubWin, FORM* TmpFrom, int Key, int HRYvon, int WCXvon, int HRYbis, int WCXbis, int PadMaxHRY, int PadMaxWCX);
        void (*FormEnde)(FORM* tmpF, FIELD** tmpFd);
    };

    struct MenuSetup_ {
        int ID;
        string Property;
        string Value;
    };

    class MenuWinClass {
    public:
        int Key;
        MenuWinClass();
        FENSTER START;
        HMENU TOPMENU;
        APPMENU INAPPMENU;
        INPUTFORM FORMPAGE;
        static vector<ID_Setup_> IDSet;
        MenuFormID GetIDtoStr(string ID_Name);
        TabKey TabWin;
        static vector<MenuSetup_> MenuSetup;
        /*#__Win create and Resize!__#*/
        void StartWin();
        void StopWin();
        void SetWinSize();
        void AppColor();
        void FensterDraw();
        void CreateWin(WINDOW* win, WinID WID, int TempHRY, int TempWCX);
        static void ResizeHandler(int signal);
        /*#__Menu and Form create!__#*/
        void StartMenuAuswahl(string MenuPoint);
        void Hauptmenu();
        void AusWahlMenu();
        static void CreateForm1();
        static void CreateForm2();
        static void CreateForm3();
        static void CreateForm4();
        static void CreateForm5();
        /*#__Menu and Form Controll!__#*/
        static FormSwitch SetFormWin[];
        int ControlMainMenu(MENU* HauptMenu, int Key);
        int ControlAusWahlMenu(MENU* AusWahlMenu, int Key);
        static int ControlFormInput(WINDOW* SubWin, FORM* TmpFrom, int Key, int HRYvon, int WCXvon, int HRYbis, int WCXbis, int PadMaxHRY, int PadMaxWCX);
        /*#__Delete Form or Menu!__#*/
        static void DeleteForm(FORM* tmpF, FIELD** tmpFd);
        void DeleteMenu(MENU* tmpMenu, ITEM** tmpItem);
        void ENDE();
    };

};
#endif // MENUWINCLASS_H
