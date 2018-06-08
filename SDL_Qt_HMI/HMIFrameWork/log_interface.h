#ifndef LOG_INTERFACE_H
#define LOG_INTERFACE_H

#include <QDebug>
#include <iostream>
using namespace std;

#define INFO qDebug

//#define __DEBUG__

//#ifdef __DEBUG__
//#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"/n", __LINE__, ##__VA_ARGS__)
//#define INFO(format,...) printf("File: "__FILE__", Line: %05d: "format"/n", __LINE__, ##__VA_ARGS__)
//#else
//#define DEBUG(format,...)
//#define INFO(format,...)
//#endif

#endif // LOG_INTERFACE_H
