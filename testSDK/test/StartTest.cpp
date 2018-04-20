#include "StartTest.h"
#include "gtest/gtest.h"
#include "Common/AppBase.h"

#include <QDebug>


TestWorkThread::TestWorkThread(QObject * parent)
:QThread(parent){

}

void TestWorkThread::run()
{
    int ret = RUN_ALL_TESTS();
    qDebug()<<"RUN_ALL_TESTS  =  " << ret;
}

StartTest* StartTest::m_Inst = NULL;

StartTest::StartTest(QObject* parent)
    :QObject(parent)

{
    m_mThread = new TestWorkThread();
}
void StartTest::Start()
{
   m_mThread->start();
}
StartTest *StartTest::Inst()
{
    if(m_Inst == NULL)
    {
        m_Inst = new StartTest;
    }
    return m_Inst;
}

