#ifndef QIPAN_H
#define QIPAN_H
#include <stdint.h>
#include <QVector>
#include <QPoint>
#define CHESS_BROAD_WIDTH 20

enum STATUS_POINT
{
    STATUS_POINT_OTHER = -1,
    STATUS_POINT_FREE = 0,
    STATUS_POINT_OWN = 1
};

typedef struct tag_KeyPoint
{
    int x,y;
    STATUS_POINT keystatus;
}KeyPoint;

typedef QVector<KeyPoint> VTPT;

typedef struct tag_LinkRange
{
    int nlevel;
    int uv;
    QPoint startPos;
    QPoint endPos;
}LinkRange;

typedef QVector<LinkRange> VTRange;


class QiPan
{
public:
    QiPan();
    ~QiPan();


    int FindVertical(int i,int j);
    int FindHorizontal(int j, int i);
    int FindRight(int j, int i);
    int FindLeft(int i, int j);

    int FindV4(int i, int j, QPoint& pos);
    int FindH4(int i, int j,QPoint& pos);
    int FindR4(int i, int j,QPoint& pos);
    int FindL4(int i, int j,QPoint& pos);

    int FindWin();
    int SetValue(int x,int y,STATUS_POINT status);

    void Clear();

    int FindDanger();
    int FindGood();

    QPoint CompareStatus();
    void FindLevel1DefenseU();
    void FindLevel1DefenseV();

    void FindDefenseLeft();
    void FindDefenseRight();

    void FindLevel1AttackU();
    void FindLevel1AttackV();
    void FindAttackLeft();
    void FindAttackRight();

    int FindFourWin(QPoint &pos);

    int GetWinMap(int x, int y);
    int GetLostMap(int x,int y);

private:
    VTPT vtstep;
    int pt[CHESS_BROAD_WIDTH][CHESS_BROAD_WIDTH];
    int WinMap[CHESS_BROAD_WIDTH][CHESS_BROAD_WIDTH];
    int LostMap[CHESS_BROAD_WIDTH][CHESS_BROAD_WIDTH];
    STATUS_POINT GetValue(int x,int y);
    //VTRange fightRange;


};

#endif // QIPAN_H
