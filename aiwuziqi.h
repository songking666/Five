#ifndef AIWUZIQI_H
#define AIWUZIQI_H

#include "qipan.h"
enum STATUS_AI
{
    STATUS_AI_FREE,
    STATUS_AI_ATTACK,
    STATUS_AI_DEFENSE
};


class AIWuZiQi
{
public:
    AIWuZiQi();
    ~AIWuZiQi();
private:

public:
    STATUS_AI m_status;
    QiPan   m_qipan;
    int SetPiecePos(int x,int y,STATUS_POINT pt = STATUS_POINT_OTHER);
    int* GetQiPan();
    int CheckWiner();
    //VTRange& GetDefenseRange();

    QPoint GetAIPress();

    void Clear();
    int GetWinMap(int x, int y);
    int GetLostMap(int x,int y);
};

#endif // AIWUZIQI_H
