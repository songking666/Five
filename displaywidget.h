#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

#include "aiwuziqi.h"
#include <qpushbutton.h>
class DisplayWidget:public QWidget
{
    Q_OBJECT
public:
    DisplayWidget();
    ~DisplayWidget();
private:
    int segment;
    int half_segment;
    int qipan[20][20];

    AIWuZiQi    ai;
    QPushButton *pButtonReset;
    QPushButton *pButtonShowMatrix;
    QPoint      AILastPt;
    bool        bshowlog;
private slots:
    void SetClear();
    void ShowMatrix();
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // DISPLAYWIDGET_H
