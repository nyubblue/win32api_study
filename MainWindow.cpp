#include "MainWindow.h"

MainWindow::MainWindow() {

    VIEWINFO ref[] = {
    {TEXT("There 15 pines  "), TEXT("There 15 pines"), TEXT("price 1"), TEXT("bed 1"), TEXT("baths 1")},
    {TEXT("addr 2"), TEXT("city 2"), TEXT("price 2"), TEXT("bed 2"), TEXT("baths 2")},
    {TEXT("addr 3"), TEXT("city 3"), TEXT("price 3"), TEXT("bed 3"), TEXT("baths 3")},
    {TEXT("addr 4"), TEXT("city 4"), TEXT("price 4"), TEXT("bed 4"), TEXT("baths 4")}
    };
    
    for (int i = 0; i < 4; i++) {
        rgPetInfo[i]= ref[i];
    }

}
BOOL MainWindow::InitListViewColumns(HWND hwndListView) {
    WCHAR szText[256];     // Temporary buffer.
    LVCOLUMN lvc;
    int iCol;

    // Initialize the LVCOLUMN structure.
    // The mask specifies that the format, width, text,
    // and subitem members of the structure are valid.
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    // Add the columns.
    for (iCol = 0; iCol < C_COLUMNS; iCol++)
    {
        lvc.iSubItem = iCol;
        lvc.pszText = szText;
        lvc.cx = 100;               // Width of column in pixels.

        if (iCol < 2)
            lvc.fmt = LVCFMT_LEFT;  // Left-aligned column.
        else
            lvc.fmt = LVCFMT_RIGHT; // Right-aligned column.

        // Load the names of the column headings from the string resources.
        LoadString(g_hInst,
            IDS_ADDRESS + iCol,
            szText,
            sizeof(szText) / sizeof(szText[0]));

        // Insert the columns into the list view.
        if (ListView_InsertColumn(hwndListView, iCol, &lvc) == -1)
            return FALSE;
    }

    return TRUE;
};

PCWSTR  MainWindow::ClassName() const { return L"Sample Window Class"; }

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hWndListView;
    //DWORD dwStyle;

    switch (uMsg)
    {
    case WM_CREATE:
        hWndListView = CreateListView(m_hwnd);
        if (hWndListView == NULL)
            MessageBox(NULL, L"Listview not created!", NULL, MB_OK);
        InitListViewColumns(hWndListView);
        InsertListViewItems(hWndListView, 4);
        break;

 
    case WM_NOTIFY:
        HandleWM_NOTIFY(lParam);
        break;


    case WM_COMMAND:

        // Test for the identifier of a command item. 

        switch (LOWORD(wParam))
        {
        case IDM_ABOUT:
            //DoFileOpen();   // application-defined 
            break;

        case IDM_EXIT:
            DestroyWindow(m_hwnd);  // application-defined 
            break;
            // Process other menu commands. 

        default:
            break;

        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

HWND MainWindow::CreateListView(HWND hwndParent) {
    INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    RECT rcClient;                       // The parent window's client area.

    GetClientRect(hwndParent, &rcClient);

    // Create the list-view window in report view with label editing enabled.
    HWND hWndListView = CreateWindow(WC_LISTVIEW,
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT |
        LVS_EDITLABELS | WS_EX_CLIENTEDGE,
        0, 0,
        rcClient.right - rcClient.left,
        rcClient.bottom - rcClient.top,
        hwndParent,
        NULL,
        g_hInst,
        NULL);

    return (hWndListView);
}

BOOL MainWindow::InsertListViewItems(HWND hWndListView, int cItems)
{
    LVITEM lvI;

    // Initialize LVITEM members that are common to all items.
    lvI.pszText = LPSTR_TEXTCALLBACK; // Sends an LVN_GETDISPINFO message.
    lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM;;
    lvI.stateMask = 0;
    lvI.iSubItem = 0;
    lvI.state = 0;

    // Initialize LVITEM members that are different for each item.
    for (int index = 0; index < cItems; index++)
    {
        lvI.iItem = index;
        lvI.iImage = index;

        // Insert items into the list.
        if (ListView_InsertItem(hWndListView, &lvI) == -1)
            return FALSE;
    }

    return TRUE;
}

void MainWindow::HandleWM_NOTIFY(LPARAM lParam)
{
    NMLVDISPINFO* plvdi;

    switch (((LPNMHDR)lParam)->code)
    {
    case LVN_GETDISPINFO:

        plvdi = (NMLVDISPINFO*)lParam;

        switch (plvdi->item.iSubItem)
        {
        case 0:
            plvdi->item.pszText = rgPetInfo[plvdi->item.iItem].szAddr;
            break;

        case 1:
            plvdi->item.pszText = rgPetInfo[plvdi->item.iItem].szCity;
            break;

        case 2:
            plvdi->item.pszText = rgPetInfo[plvdi->item.iItem].szPrice;
            break;
        case 3:
            plvdi->item.pszText = rgPetInfo[plvdi->item.iItem].szBed;
            break;
        case 4:
            plvdi->item.pszText = rgPetInfo[plvdi->item.iItem].szBaths;
            break;

        default:
            break;
        }

        break;

    }
}
