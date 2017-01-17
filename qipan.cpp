#include "qipan.h"
#include <memory.h>
#include <math.h>
QiPan::QiPan()
{
    Clear();
}

QiPan::~QiPan()
{

}

int QiPan::SetValue(int x, int y, STATUS_POINT status)
{
    if (x < 0 || x > 19 || y > 19 || y < 0)
        return 1;
    if(pt[x][y] != STATUS_POINT_FREE)
        return 2;
    pt[x][y] = status;

    if(status == STATUS_POINT_OWN)
        return 0;

    FindDanger();
    FindGood();

    return 0;
}


void QiPan::FindLevel1DefenseU()
{
    for(int iHorizontal = 0;iHorizontal<CHESS_BROAD_WIDTH;iHorizontal++)
    {
        for(int jVertical = 0;jVertical < CHESS_BROAD_WIDTH;jVertical ++)
        {
            int continuecount = 0;
            int findrange = jVertical+5 < CHESS_BROAD_WIDTH ? jVertical+5:CHESS_BROAD_WIDTH;

            int kcontinue = jVertical;
            for(;kcontinue<findrange;kcontinue++)
            {
                if(pt[iHorizontal][kcontinue] == -1)
                {
                    continuecount++;
                }
                else if(pt[iHorizontal][kcontinue] == 1)
                {
                    continuecount = 0;
                    break;
                }
            }

            switch(continuecount)
            {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            {
                for(int i = kcontinue - 5;i<kcontinue;i++)
                {
                    if(pt[iHorizontal][i] == STATUS_POINT_FREE)
                        LostMap[iHorizontal][i] += pow(continuecount,2);
                    else if(pt[i][jVertical] == STATUS_POINT_OTHER)
                        LostMap[i][jVertical] = STATUS_POINT_OTHER;
                }
            }

            }

        }
    }
}

void QiPan::FindLevel1DefenseV()
{
    for(int jVertical = 0;jVertical < CHESS_BROAD_WIDTH;jVertical ++)

    {
        for(int iHorizontal = 0;iHorizontal<CHESS_BROAD_WIDTH;iHorizontal++)
        {
            int continuecount = 0;
            int findrange = iHorizontal+5 < CHESS_BROAD_WIDTH ? iHorizontal+5:CHESS_BROAD_WIDTH;

            int kcontinue = iHorizontal;
            for(;kcontinue<findrange;kcontinue++)
            {
                if(pt[kcontinue][jVertical] == STATUS_POINT_OTHER)
                {
                    continuecount++;
                }
                else if(pt[kcontinue][jVertical] == STATUS_POINT_OWN)
                {
                    continuecount = 0;
                    break;
                }
            }

            switch(continuecount)
            {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            {
                //                LinkRange tmprange;
                //                tmprange.nlevel = continuecount;
                //                tmprange.uv = 2;
                //                tmprange.startPos = QPoint(jVertical,kcontinue - 5);
                //                tmprange.endPos = QPoint(jVertical,kcontinue);

                for(int i = kcontinue - 5;i<kcontinue;i++)
                {
                    if(pt[i][jVertical] == STATUS_POINT_FREE)
                        LostMap[i][jVertical] += pow(continuecount,2);
                    else if(pt[i][jVertical] == STATUS_POINT_OTHER)
                        LostMap[i][jVertical] = STATUS_POINT_OTHER;
                }

                //defenseRange.push_back(tmprange);
            }

            }

        }
    }
}


void QiPan::FindDefenseLeft()
{
    for(int v = 0;v<CHESS_BROAD_WIDTH;v++)
    {
        for(int u = 0;u<CHESS_BROAD_WIDTH;u++)
        {
            int chesscontinue = 0;
            for(int i = u,j = 0;i > u-5;i--,j++)
            {
                if(v + j >= CHESS_BROAD_WIDTH || i < 0)
                {
                    chesscontinue = 0;
                    break;
                }
                if(pt[i][v + j] == STATUS_POINT_OTHER)
                {
                    chesscontinue ++;
                }
                else if(pt[i][v + j] == STATUS_POINT_OWN)
                {
                    chesscontinue = 0;
                    break;
                }
            }
            if(chesscontinue > 0)
            {
                for(int i = u,j=0;i>u-5;i--,j++)
                {
                    if(pt[i][v+j] == STATUS_POINT_FREE)
                        LostMap[i][v+j] += pow(chesscontinue,2);
                }
            }
        }

    }
}

void QiPan::FindDefenseRight()
{
    for(int v = 0;v<CHESS_BROAD_WIDTH;v++)
    {
        for(int u = 0;u<CHESS_BROAD_WIDTH;u++)
        {
            int chesscontinue = 0;
            for(int i = u,j = 0;i < u+5;i++,j++)
            {
                if(v + j >= CHESS_BROAD_WIDTH || i >= CHESS_BROAD_WIDTH)
                {
                    chesscontinue = 0;
                    break;
                }
                if(pt[i][v + j] == STATUS_POINT_OTHER)
                {
                    chesscontinue ++;
                }
                else if(pt[i][v + j] == STATUS_POINT_OWN)
                {
                    chesscontinue = 0;
                    break;
                }
            }
            if(chesscontinue > 0)
            {
                for(int i = u,j=0;i<u+5;i++,j++)
                {
                    if(pt[i][v+j] == STATUS_POINT_FREE)
                        LostMap[i][v+j] += pow(chesscontinue,2);
                }
            }
        }
    }
}


void QiPan::FindLevel1AttackU()
{
    for(int iHorizontal = 0;iHorizontal<CHESS_BROAD_WIDTH;iHorizontal++)
    {
        for(int jVertical = 0;jVertical < CHESS_BROAD_WIDTH;jVertical ++)
        {
            int continuecount = 0;
            int findrange = jVertical+5 < CHESS_BROAD_WIDTH ? jVertical+5:CHESS_BROAD_WIDTH;

            int kcontinue = jVertical;
            for(;kcontinue<findrange;kcontinue++)
            {
                if(pt[iHorizontal][kcontinue] == STATUS_POINT_OWN)
                {
                    continuecount++;
                }
                else if(pt[iHorizontal][kcontinue] == STATUS_POINT_OTHER)
                {
                    continuecount = 0;
                    break;
                }
            }

            switch(continuecount)
            {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            {
                for(int i = kcontinue - 5;i<kcontinue;i++)
                {
                    if(pt[iHorizontal][i] == STATUS_POINT_FREE)
                        WinMap[iHorizontal][i] += pow(continuecount,2);
                    else if(pt[i][jVertical] == STATUS_POINT_OWN)
                        WinMap[i][jVertical] = STATUS_POINT_OTHER;
                }
            }

            }

        }
    }
}

void QiPan::FindLevel1AttackV()
{
    for(int jVertical = 0;jVertical < CHESS_BROAD_WIDTH;jVertical ++)

    {
        for(int iHorizontal = 0;iHorizontal<CHESS_BROAD_WIDTH;iHorizontal++)
        {
            int continuecount = 0;
            int findrange = iHorizontal+5 < CHESS_BROAD_WIDTH ? iHorizontal+5:CHESS_BROAD_WIDTH;

            int kcontinue = iHorizontal;
            for(;kcontinue<findrange;kcontinue++)
            {
                if(pt[kcontinue][jVertical] == STATUS_POINT_OWN)
                {
                    continuecount++;
                }
                else if(pt[kcontinue][jVertical] == STATUS_POINT_OTHER)
                {
                    continuecount = 0;
                    break;
                }
            }

            switch(continuecount)
            {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            {

                for(int i = kcontinue - 5;i<kcontinue;i++)
                {
                    if(pt[i][jVertical] == STATUS_POINT_FREE)
                        WinMap[i][jVertical] += pow(continuecount,2);
                    else if(pt[i][jVertical] == STATUS_POINT_OWN)
                        WinMap[i][jVertical] = STATUS_POINT_OTHER;
                }


            }

            }

        }
    }
}

void QiPan::FindAttackLeft()
{
    for(int v = 0;v<CHESS_BROAD_WIDTH;v++)
    {
        for(int u = 0;u<CHESS_BROAD_WIDTH;u++)
        {
            int chesscontinue = 0;
            for(int i = u,j = 0;i > u-5;i--,j++)
            {
                if(v + j >= CHESS_BROAD_WIDTH || i < 0)
                {
                    chesscontinue = 0;
                    break;
                }
                if(pt[i][v + j] == STATUS_POINT_OWN)
                {
                    chesscontinue ++;
                }
                else if(pt[i][v + j] == STATUS_POINT_OTHER)
                {
                    chesscontinue = 0;
                    break;
                }
            }
            if(chesscontinue > 0)
            {
                for(int i = u,j=0;i>u-5;i--,j++)
                {
                    if(pt[i][v+j] == STATUS_POINT_FREE)
                        WinMap[i][v+j] += pow(chesscontinue,2);
                }
            }
        }

    }
}

void QiPan::FindAttackRight()
{
    for(int v = 0;v<CHESS_BROAD_WIDTH;v++)
    {
        for(int u = 0;u<CHESS_BROAD_WIDTH;u++)
        {
            int chesscontinue = 0;
            for(int i = u,j = 0;i < u+5;i++,j++)
            {
                if(v + j >= CHESS_BROAD_WIDTH || i >= CHESS_BROAD_WIDTH)
                {
                    chesscontinue = 0;
                    break;
                }
                if(pt[i][v + j] == STATUS_POINT_OWN)
                {
                    chesscontinue ++;
                }
                else if(pt[i][v + j] == STATUS_POINT_OTHER)
                {
                    chesscontinue = 0;
                    break;
                }
            }
            if(chesscontinue > 0)
            {
                for(int i = u,j=0;i<u+5;i++,j++)
                {
                    if(pt[i][v+j] == STATUS_POINT_FREE)
                        WinMap[i][v+j] += pow(chesscontinue,2);
                }
            }
        }
    }
}

int QiPan::FindFourWin(QPoint& pos)
{
    for(int i = 0;i<CHESS_BROAD_WIDTH;i++)
    {
        for(int j = 0;j<CHESS_BROAD_WIDTH;j++)
        {

            if(FindV4(i,j,pos) == 1)
                return 1;
            else if(FindH4(i,j,pos) == 1)
                return 1;
            else if(FindR4(i,j,pos) == 1)
                return 1;
            else if(FindL4(i,j,pos) == 1)
                return 1;
        }
    }
    return 0;
}


int QiPan::GetWinMap(int x,int y)
{
    return WinMap[x][y];
}

int QiPan::GetLostMap(int x, int y)
{
    return LostMap[x][y];
}

//VTRange &QiPan::GetDefenseRange()
//{
//    return defenseRange;

//}

int QiPan::FindDanger()
{
    //defenseRange.clear();
    memset(LostMap,0,sizeof(int[20][20]));

    FindLevel1DefenseU();
    FindLevel1DefenseV();

    FindDefenseRight();
    FindDefenseLeft();

    return 0;
}

int QiPan::FindGood()
{
    memset(WinMap,0,sizeof(int[20][20]));
    FindLevel1AttackU();
    FindLevel1AttackV();

    FindAttackLeft();
    FindAttackRight();

    return 1;
}

QPoint QiPan::CompareStatus()
{
    QPoint maxDangerPos;
    int maxDangerValue = 0;
    for(int i = 0;i<CHESS_BROAD_WIDTH;i++)
    {
        for(int j = 0;j<CHESS_BROAD_WIDTH;j++)
        {
            if(LostMap[i][j] > maxDangerValue)
            {
                maxDangerValue = LostMap[i][j];
                maxDangerPos = QPoint(i,j);
            }
        }
    }
    if(maxDangerValue > 31)
        return maxDangerPos;

    QPoint maxWinPos;
    int maxWinValue = 0;
    for(int i = 0;i<CHESS_BROAD_WIDTH;i++)
    {
        for(int j = 0;j<CHESS_BROAD_WIDTH;j++)
        {
            if(WinMap[i][j] > maxWinValue)
            {
                maxWinValue = WinMap[i][j];
                maxWinPos = QPoint(i,j);
            }
        }
    }

    if(maxDangerValue > maxWinValue)
        return maxDangerPos;
    else
        return maxWinPos;

}

STATUS_POINT QiPan::GetValue(int x, int y)
{
    return (STATUS_POINT)pt[x][y];
}

int QiPan::FindVertical(int i,int j)
{
    int sum_owen = 0;
    int sum_other = 0;
    for(int k = j;k<j+5 && k < CHESS_BROAD_WIDTH;k++)
    {
        if(pt[i][k] > 0)
            sum_owen += pt[i][k];
        else if(pt[i][k] < 0)
            sum_other += pt[i][k];
    }
    if(sum_owen > 4)
        return 1;
    else if(sum_other < -4)
        return -1;
    return 0;
}

int QiPan::FindHorizontal(int j, int i)
{
    int sum_owen = 0;
    int sum_other = 0;
    for(int k = i;k<i+5 && k < CHESS_BROAD_WIDTH;k++)
    {
        if(pt[k][j] > 0)
            sum_owen += pt[i][j];
        else if(pt[k][j] < 0)
            sum_other += pt[i][j];
    }
    if(sum_owen > 4)
        return 1;
    else if(sum_other < -4)
        return -1;
    return 0;
}

int QiPan::FindRight(int j, int i)
{
    int sum_owen = 0;
    int sum_other = 0;
    for(int k = i,l = j;k<i+5 && k < CHESS_BROAD_WIDTH && l < j + 5 && l < CHESS_BROAD_WIDTH;k++,l++)
    {
        if(pt[l][k] > 0)
            sum_owen += pt[l][k];
        else if(pt[l][k] < 0)
            sum_other += pt[l][k];
    }
    if(sum_owen > 4)
        return 1;
    else if(sum_other < -4)
        return -1;
    return 0;
}

int QiPan::FindLeft(int i,int  j)
{
    int sum_owen = 0;
    int sum_other = 0;
    for(int k = i,l = j;k>i-5 && k >= 0 && l < j + 5 && l < CHESS_BROAD_WIDTH;k--,l++)
    {
        if(pt[k][l] > 0)
            sum_owen += pt[k][l];
        else if(pt[k][l] < 0)
            sum_other += pt[k][l];
    }
    if(sum_owen > 4)
        return 1;
    else if(sum_other < -4)
        return -1;
    return 0;
}

int QiPan::FindV4(int i, int j, QPoint &pos)
{
    int sum_owen = 0;
    bool have_empty = false;
    for(int k = j;k<j+5 && k < CHESS_BROAD_WIDTH;k++)
    {
        sum_owen += pt[i][k];
        if(pt[i][k] == 0)
        {
            have_empty = true;
            pos = QPoint(i,k);
        }
    }
    if(sum_owen == 4 && have_empty)
        return 1;
    return 0;
}

int QiPan::FindH4(int i, int j, QPoint& pos)
{
    int sum_owen = 0;
    bool have_empty = false;
    for(int k = i;k<i+5 && k < CHESS_BROAD_WIDTH;k++)
    {
        sum_owen += pt[i][j];
        if(pt[k][j] == 0)
        {
            have_empty = true;
            pos = QPoint(k,j);
        }
    }
    if(sum_owen == 4 && have_empty)
        return 1;
    return 0;
}

int QiPan::FindR4(int i, int j, QPoint& pos)
{
    int sum_owen = 0;
    bool have_empty = false;
    for(int k = i,l = j;k<i+5 && k < CHESS_BROAD_WIDTH && l < j + 5 && l < CHESS_BROAD_WIDTH;k++,l++)
    {

        sum_owen += pt[l][k];
        if(pt[l][k] == 0)
            pos = QPoint(l,k);
    }
    if(sum_owen == 4 && have_empty)
    {
        have_empty = true;
        return 1;
    }
    return 0;
}

int QiPan::FindL4(int i, int j, QPoint &pos)
{
    int sum_owen = 0;
    bool have_empty = false;
    for(int k = i,l = j;k>i-5 && k >= 0 && l < j + 5 && l < CHESS_BROAD_WIDTH;k--,l++)
    {
        sum_owen += pt[k][l];
        if(pt[k][l] == 0)
        {
            have_empty = true;
            pos = QPoint(k,l);
        }
    }
    if(sum_owen == 4 && have_empty)
        return 1;
    return 0;
}

int QiPan::FindWin()
{
    for(int i = 0;i<CHESS_BROAD_WIDTH;i++)
    {
        for(int j = 0;j<CHESS_BROAD_WIDTH;j++)
        {
            int retfind = FindVertical(i, j);
            if(retfind != 0)
                return retfind;

            retfind = FindHorizontal(j, i);
            if(retfind != 0)
                return retfind;

            retfind = FindRight(j, i);
            if(retfind != 0)
                return retfind;

            retfind = FindLeft(i,j);
            if(retfind != 0)
                return retfind;
        }
    }
    return 0;
}

void QiPan::Clear()
{
    memset(pt,0,sizeof(int[20][20]));
    memset(WinMap,0,sizeof(int[20][20]));
    memset(LostMap,0,sizeof(int[20][20]));
}

