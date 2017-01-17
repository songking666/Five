#ifndef QTHINKWINTHREAD_H
#define QTHINKWINTHREAD_H
#include <QThread>

class QThinkWinThread : public QThread
{
    Q_OBJECT
public:
    QThinkWinThread();
    ~QThinkWinThread();

    void run() Q_DECL_OVERRIDE {

    }
    int** ppmap;
    int m,n;

    //int p[i][j]
    //*((int*)array + n*i + j);
    void Func(int **array, int m, int n);

};

#endif // QTHINKWINTHREAD_H
