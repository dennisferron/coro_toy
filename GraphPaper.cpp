#include "GraphPaper.hpp"

GraphPaper::GraphPaper(RECT const& rect) :
    rect(rect)
{
}

void GraphPaper::draw(HDC hdc)
{
    PAINTSTRUCT ps;
    LOGBRUSH lb;
    HGDIOBJ hPen = NULL;
    HGDIOBJ hPenOld;

    // Initialize the pen's brush.
    lb.lbStyle = BS_SOLID;
    lb.lbColor = RGB(100,100,100);
    lb.lbHatch = 0;

    hPen = ExtCreatePen(PS_COSMETIC | PS_DOT,
                        1, &lb, 0, NULL);
    hPenOld = SelectObject(hdc, hPen);

    for (int x = rect.left; x < rect.right; x+=square_size)
    {
        MoveToEx(hdc, x, rect.top, NULL);
        LineTo(hdc, x, rect.bottom);
    }

    for (int y = rect.top; y < rect.bottom; y+=square_size)
    {
        MoveToEx(hdc, rect.left, y, NULL);
        LineTo(hdc, rect.right, y);
    }

    SelectObject(hdc, hPenOld);
    DeleteObject(hPen);
}
