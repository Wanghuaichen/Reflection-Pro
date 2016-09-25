#include "ReflectionView.h"
#include "RootViewController.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RootViewController rootView;
    rootView.Initialize();
    int exeResult = 1;
    exeResult = a.exec();


    return exeResult;
}
