#ifndef TextViewXWPluginExample_H
#define TextViewXWPluginExample_H

#include <QWidget>

// cumbia-tango
#include <qulogimpl.h>
#include <cutcontrolsreader.h>
#include <cutcontrolswriter.h>
#include <cumbiatango.h>
// cumbia-tango

namespace Ui {
class TextViewXWPluginExample;
}

class RTPlotXWPluginExample : public QWidget
{
    Q_OBJECT

public:
    explicit RTPlotXWPluginExample(CumbiaTango *cut, QWidget *parent = 0);
    ~RTPlotXWPluginExample();

private:
    Ui::TextViewXWPluginExample *ui;

// cumbia-tango
    CumbiaTango *cu_t;
    CuTReaderFactory cu_tango_r_fac;
    QuLogImpl m_log_impl;
    CuLog *m_log;
// cumbia-tango
};

#endif // TextViewXWPluginExample_H
