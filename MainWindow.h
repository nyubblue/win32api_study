#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include"BaseWindow.h"

struct VIEWINFO
{
    TCHAR szAddr[20];
    TCHAR szCity[20];
    TCHAR szPrice[20];
    TCHAR szBed[20];
    TCHAR szBaths[20];
};

class MainWindow : public BaseWindow<MainWindow>
{
public:
    MainWindow();
    PCWSTR  ClassName() const;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    BOOL InitListViewColumns(HWND hWndListView);
    HWND CreateListView(HWND hwndParent);
    void HandleWM_NOTIFY(LPARAM lParam);
    BOOL InsertListViewItems(HWND hWndListView, int cItems);
private:
    VIEWINFO rgPetInfo[20];
};

#endif