#include "aiwuziqi.h"

AIWuZiQi::AIWuZiQi()
{

}

AIWuZiQi::~AIWuZiQi()
{

}

int AIWuZiQi::SetPiecePos(int x, int y, STATUS_POINT pt)
{
    return m_qipan.SetValue(x,y,pt);
}



int AIWuZiQi::CheckWiner()
{
    return m_qipan.FindWin();
}

QPoint AIWuZiQi::GetAIPress()
{
    QPoint pt;
//    if(m_qipan.FindFourWin(pt) == 1)
//    {
//        m_qipan.SetValue(pt.x(),pt.y(),STATUS_POINT_OWN);
//    }
//    else
    {
        pt = m_qipan.CompareStatus();
        m_qipan.SetValue(pt.x(),pt.y(),STATUS_POINT_OWN);
    }
    return pt;
}

//VTRange& AIWuZiQi::GetDefenseRange()
//{
//    return m_qipan.GetDefenseRange();
//}

void AIWuZiQi::Clear()
{
    m_qipan.Clear();
}

int AIWuZiQi::GetWinMap(int x,int y)
{
    return m_qipan.GetWinMap(x,y);
}

int AIWuZiQi::GetLostMap(int x, int y)
{
    return m_qipan.GetLostMap( x, y);
}

