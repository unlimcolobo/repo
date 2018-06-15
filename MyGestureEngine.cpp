#include "MyGestureEngine.h"
CMyGestureEngine::CMyGestureEngine(CDrawingObject* pcRect):CGestureEngine(),_pcRect(pcRect)
{}
void CMyGestureEngine::ProcessPressAndTap()
{
    if(_pcRect)_pcRect->ShiftColor();
}
void CMyGestureEngine::ProcessTwoFingerTap()
{
    if(_pcRect) _pcRect->ToggleDrawDiagonals();
}
void CMyGestureEngine::ProcessZoom(const double dZoomFactor, const LONG lZx, const LONG lZy)
{
    if(_pcRect) _pcRect->Zoom(dZoomFactor,lZx,lZy);
}
void CMyGestureEngine::ProcessMove(const LONG ldx, const LONG ldy)
{
    if(_pcRect) _pcRect->Move(ldx, ldy);
}
void CMyGestureEngine::ProcessRotate(const double dAngle, const LONG lOx, const LONG lOy)
{
    if(_pcRect) _pcRect->Rotate(dAngle,lOx,lOy);
}
