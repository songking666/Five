#include "displaywidget.h"
#include <QtWidgets>

#include <math.h>
DisplayWidget::DisplayWidget()
{
     segment = 40;
     half_segment = segment / 2;
     int screenheight = segment * 21;
     int screenwidth = screenheight + 100;
     this->resize(screenwidth,screenheight);

     bshowlog = true;

    memset(qipan,0,sizeof(int[20][20]));

    pButtonReset = new QPushButton( "Reset", this);
    connect(pButtonReset, &QPushButton::clicked, this, &DisplayWidget::SetClear);
    pButtonReset->move(screenwidth - 120,50);


    pButtonShowMatrix = new QPushButton("ShowLog",this);
    connect(pButtonShowMatrix, &QPushButton::clicked, this, &DisplayWidget::ShowMatrix);
    pButtonShowMatrix->move(screenwidth - 120,80);
}

DisplayWidget::~DisplayWidget()
{

}

void DisplayWidget::SetClear()
{
    memset(qipan,0,sizeof(int[20][20]));
    ai.Clear();
    update();
}

void DisplayWidget::ShowMatrix()
{
    bshowlog = !bshowlog;
    update();
}

void DisplayWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for(int i = 1;i<21;i++)
    {
        painter.drawLine(QPoint(segment,segment * i),QPoint(segment * 20,segment * i));
        painter.drawText(QPoint(segment - 20,segment * i),QString::number(i));
    }
    for(int i = 1;i<21;i++)
    {
        painter.drawLine(QPoint(segment * i,segment),QPoint(segment * i,segment * 20));
        painter.drawText(QPoint(segment * i,segment - 20),QString::number(i));
    }

    for(int i = 0;i<20;i++)
    {
        for(int j = 0;j<20;j++)
        {
            if(qipan[i][j] == 0)
                continue;
            if(qipan[i][j] == -1)
                painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
            if(qipan[i][j] == 1)
                painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));

            painter.drawEllipse(segment * (i + 1) - half_segment,
                                segment * (j + 1)- half_segment,
                                segment - 1,
                                segment - 1);

        }
    }

    QPen tmpPen;
    tmpPen.setStyle(Qt::DotLine);
    tmpPen.setWidth(3);
    tmpPen.setColor(Qt::red);

    QBrush tmpBrush;
    tmpBrush.setColor(Qt::yellow);

    painter.setPen(tmpPen);
    painter.setBrush(tmpBrush);
    painter.drawEllipse(segment * (AILastPt.x() + 1) - (half_segment-3),
                        segment * (AILastPt.y() + 1)- (half_segment - 3),
                        segment - 6,
                        segment - 6);

    if(bshowlog)
    {
        for(int i = 0;i<20;i++)
        {
            for(int j = 0;j<20;j++)
            {
                QString tmpstr = QString::number(ai.GetWinMap(i,j));
                tmpstr += "/";
                tmpstr += QString::number(ai.GetLostMap(i,j));

                painter.drawText(segment * (i + 1),
                                 segment * (j + 1),tmpstr);

            }
        }
    }


//    QPen tmpPen;
//    for(int i = 0;i<ai.GetDefenseRange().size();i++)
//    {
//        tmpPen.setStyle(Qt::DotLine);
//        tmpPen.setWidth(3);
//        tmpPen.setColor(Qt::red);
//        painter.setPen(tmpPen);
//        //painter.setPen(Qt::red);
//        painter.drawLine(segment * (ai.GetDefenseRange()[i].startPos.y() + 1),
//                         segment * (ai.GetDefenseRange()[i].startPos.x() + 1),
//                         segment * (ai.GetDefenseRange()[i].endPos.y() + 1),
//                         segment * (ai.GetDefenseRange()[i].endPos.x() + 1)
//                         );
//    }

}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint curpt = event->pos();
    int half = segment / 2;
    for(int i = 0;i<20;i++)
    {
        for(int j = 0;j<20;j++)
        {
            QRect rc(segment * (i + 1) - half
                  ,segment * (j + 1)- half
                  ,segment - 1
                  ,segment - 1);

            if(curpt.x() > rc.left() && curpt.x() < rc.right() &&
               curpt.y() > rc.top() && curpt.y() < rc.bottom())
            {
                if(ai.SetPiecePos(i,j,STATUS_POINT_OTHER) == 0)
                {
                    qipan[i][j] = 1;
                    int checkreturn = ai.CheckWiner();
                    if(checkreturn != 0)
                    {
                        QMessageBox::about(NULL, "Win", "You Win!");
                        return;
                    }
                    QPoint aipt = ai.GetAIPress();
                    qipan[aipt.x()][aipt.y()] = -1;

                    checkreturn = ai.CheckWiner();
                    if(checkreturn != 0)
                    {
                        QMessageBox::about(NULL, "Lost", "You Lost!");
                        return;
                    }

                    AILastPt = aipt;
                    update();
                    return;
                }
            }
        }
    }
}
