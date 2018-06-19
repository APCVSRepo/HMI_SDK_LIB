#ifndef LOG_INTERFACE_H
#define LOG_INTERFACE_H

#include <QDebug>
#include <iostream>
using namespace std;



#define __DEBUG__

#ifndef __DEBUG__
#define INFO(format,...) printf("[INFO]-File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#define WARN(format,...) printf("[WARN]-File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#define ERROR(format,...) printf("[ERROR]-File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#else
#define INFO(format,...) qDebug("[INFO]-File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#define ERROR(format,...) qDebug("[INFO]-File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#define WARN(format,...) qDebug("[INFO]-File: "__FILE__", Line: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
#endif

#endif // LOG_INTERFACE_H
