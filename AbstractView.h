#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QObject>

class AbstractView : public QObject
{
    Q_OBJECT
public:
    explicit AbstractView(QObject *parent = 0);
    virtual ~AbstractView();
    virtual QWidget *GetViewsFrame() = 0;
    virtual void OnSwitchIn() {}
signals:

public slots:
    virtual void ReportErrors(const QString &errors);

};

#endif // ABSTRACTVIEW_H
