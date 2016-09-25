#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T17:29:38
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += xml
QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reflection
TEMPLATE = app


SOURCES += main.cpp\
        RootViewController.cpp \
    AbstractView.cpp \
    ReflectionView.cpp \
    ReflectionWidget.cpp \
    QueryCondition.cpp \
    TouchTableGrid.cpp \
    TableCell.cpp \
    freezetablewidget.cpp \
    DBManager.cpp \
    DBAccess.cpp \
    PatientSystem.cpp \
    FieldDefine.cpp \
    ReflectionAccess.cpp \
    ReflectionInfo.cpp \
    ReflectionInfoSaver.cpp \
    ReflectionItem.cpp \
    Filepathmanager.cpp \
    InfoSaver.cpp \
    IDataAccess.cpp \
    ParameterSystem.cpp \
    ChemistryType.cpp \
    RecordWithReflectionDataAccess.cpp \
    RecordInfo.cpp \
    RecordInfoSaver.cpp \
    RecordAccess.cpp \
    UIWidthManager.cpp \
    IniAccess.cpp \
    UWinEventFilter.cpp \
    ChemistryAnalyser.cpp \
    SysTopMenuView.cpp \
    topmenuwidget.cpp \
    MenuButton.cpp \
    MainBottomCtrlWidget.cpp \
    ReViewQueryDlg.cpp \
    CustomLineEdit.cpp \
    CustomNumEdit.cpp \
    CustomDateEdit.cpp \
    DryRange.cpp \
    ReflectedChecker.cpp \
    StripItemProvider.cpp \
    WaitDialog.cpp

HEADERS  += RootViewController.h \
    AbstractView.h \
    EnumViewType.h \
    ReflectionView.h \
    ReflectionWidget.h \
    QueryCondition.h \
    TouchTableGrid.h \
    TableCell.h \
    freezetablewidget.h \
    DBManager.h \
    DBAccess.h \
    PatientSystem.h \
    FieldDefine.h \
    ReflectionAccess.h \
    ReflectionInfo.h \
    ReflectionInfoSaver.h \
    ReflectionItem.h \
    Filepathmanager.h \
    EnumChemistryType.h \
    InfoSaver.h \
    IDataAccess.h \
    ParameterSystem.h \
    DryColorInfo.h \
    CommonInfomation.h \
    ChemistryType.h \
    EnumReflectType.h \
    RecordWithReflectionDataAccess.h \
    RecordInfo.h \
    EnumPrintItem.h \
    EnumPatientGenderItem.h \
    RecordInfoSaver.h \
    RecordAccess.h \
    UIWidthManager.h \
    IniAccess.h \
    UWinEventFilter.h \
    ChemistryAnalyser.h \
    SysTopMenuView.h \
    topmenuwidget.h \
    MenuButton.h \
    MainBottomCtrlWidget.h \
    EnumMainBottomCtrlType.h \
    ReViewQueryDlg.h \
    CustomDateEdit.h \
    CustomLineEdit.h \
    CustomNumEdit.h \
    DryRange.h \
    ReflectedChecker.h \
    StripItemProvider.h \
    WaitDialog.h

FORMS += \
    ReflectionWidget.ui \
    touchtablegrid.ui \
    topmenuwidget.ui \
    MainBottomCtrlWidget.ui \
    ReViewQueryDlg.ui \
    CustomDateEdit.ui \
    CustomNumEdit.ui \
    WaitDialog.ui
