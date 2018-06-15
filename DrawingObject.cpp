#include "DrawingObject.h"
#define ROUND_DOUBLE_TO_LONG(x) ((LONG)floor(0.5 + (x)))
const COLORREF CDrawingObject::s_colors[] = 
{
    RGB(0, 0, 0),     // black
    RGB(255, 255, 0), // yellow
    RGB(255, 0, 0),   // red
    RGB(0, 255, 0),   // green
    RGB(0, 0, 255)    // blue
};
void CDrawingObject::ShiftColor()
{
    _iColorIndex++;
    if (MAX_COLORS == _iColorIndex) _iColorIndex = 0;
}
void CDrawingObject::ResetObject(const int cxClient, const int cyClient)
{
    _iCx = cxClient/2;
    _iCy = cyClient/2;
    _iWidth = cxClient/2;
    _iHeight = cyClient/2;
    _dScalingFactor = 1.0;
    _dRotationAngle = 0.0; 
    _bDrawDiagonals = false;
    _iColorIndex = 0;
}
void CDrawingObject::Paint(HDC hdc)
{
    HPEN hPen = CreatePen(PS_SOLID,1,s_colors[_iColorIndex]);HGDIOBJ hPenOld = SelectObject(hdc,hPen);POINT ptRect[5];ptRect[0].x = -(LONG)(_dScalingFactor * _iWidth/2);ptRect[0].y = -(LONG)(_dScalingFactor * _iHeight/2);ptRect[1].x = (LONG)(_dScalingFactor * _iWidth/2);
    ptRect[1].y = ptRect[0].y;ptRect[2].x = ptRect[1].x;ptRect[2].y = (LONG)(_dScalingFactor * _iHeight/2);ptRect[3].x = ptRect[0].x;ptRect[3].y = ptRect[2].y;ptRect[4] = ptRect[0];
    double dCos = cos(_dRotationAngle);double dSin = sin(_dRotationAngle);
    for (int i = 0; i < 5; i++){LONG lDX = ptRect[i].x;LONG lDY = ptRect[i].y;ptRect[i].x = (LONG)(lDX*dCos + lDY*dSin);ptRect[i].y = (LONG)(lDY*dCos - lDX*dSin);}
    for (int i = 0; i < 5; i++){ptRect[i].x += _iCx;ptRect[i].y += _iCy;}
    Polyline(hdc, ptRect, 5);if(_bDrawDiagonals)
    {
        MoveToEx(hdc, ptRect[0].x, ptRect[0].y, NULL);
        LineTo(hdc, ptRect[2].x, ptRect[2].y);
        MoveToEx(hdc, ptRect[1].x, ptRect[1].y, NULL);
        LineTo(hdc, ptRect[3].x, ptRect[3].y);
    }SelectObject(hdc, hPenOld);DeleteObject(hPen);
}
void CDrawingObject::Move(LONG ldx, LONG ldy){_iCx += ldx;_iCy += ldy;}
void CDrawingObject::Zoom(const double dZoomFactor, const LONG iZx, const LONG iZy)
{
    _iCx = ROUND_DOUBLE_TO_LONG(iZx * (1.0-dZoomFactor) + _iCx * dZoomFactor);
    _iCy = ROUND_DOUBLE_TO_LONG(iZy * (1.0-dZoomFactor) + _iCy * dZoomFactor);
    _dScalingFactor *= dZoomFactor;
}
void CDrawingObject::Rotate(const double dAngle, const LONG iOx, const LONG iOy)
{
    double dCos = cos(dAngle);double dSin = sin(dAngle);
    LONG lDX = _iCx - iOx;LONG lDY = _iCy - iOy;
    _iCx = iOx + ROUND_DOUBLE_TO_LONG(lDX*dCos + lDY*dSin);
    _iCy = iOy + ROUND_DOUBLE_TO_LONG(lDY*dCos - lDX*dSin);
    _dRotationAngle += dAngle;
}
