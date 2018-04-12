#ifndef STARTTEST_H
#define STARTTEST_H
#include "Common/AppBase.h"
#include "Gen3UIManager.h"
#include "app_list_interface.h"
#include "message_interface.h"
#include <QThread>
#include <QObject>
#include "sdl_connector.h"

class TestWorkThread: public QThread
{

    Q_OBJECT

public:
    explicit TestWorkThread(QObject * parent = 0);
    ~TestWorkThread(){}
    void run();
};

class StartTest:public QObject
{
    Q_OBJECT
public:
    explicit StartTest(QObject* parent = 0);
    ~StartTest(){}
    void Start();

public:
    TestWorkThread *m_mThread;
    static StartTest *Inst();
    static StartTest *m_Inst;
};

#endif // STARTTEST_H
