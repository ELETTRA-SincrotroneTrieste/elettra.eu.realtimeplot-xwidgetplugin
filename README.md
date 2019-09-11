### Elettra *real time plot*: a spectrum plot with configuration options to change the period and the number of samples

cumbia-qtcontrols QuSpectrumPlot combined with a box grouping controls to change the read period and the number of
samples read by the plot. It is compatible with the *Elettra* tango devices exposing commands of the type

```
bc01/diagnostics/rtcm_bc01.01->GetCharge(0,1000)
```

They have two input arguments, the *mode* and the dimension of the array.
The class made available by the plugin is called *QuRTPlot* and allows to change

\li the period and
\li the length of the array



To install the plugin, execute

- qmake
- make
- make install

after checking that the line

```
include(/usr/local/cumbia-libs/include/cumbia-qtcontrols/cumbia-qtcontrols.pri)
```

in the file elettra.eu.realtimeplot-xwidgetplugin.pro is correct (in the default case,
cumbia-qtcontrols is installed under /usr/local/cumbia-libs)

#### Example usage

##### Header file

```
class RTPlotXWPluginExample : public QWidget
{
    Q_OBJECT

public:
    RTPlotXWPluginExample(CumbiaTango *cut, QWidget *parent = 0);

private:

// cumbia-tango
    CumbiaTango *cu_t;
    CuTReaderFactory cu_tango_r_fac;
}
```

##### cpp file

```
#include <QGridLayout>
#include <QVariant>
#include <QCoreApplication>
#include <quxtrawidgetpluginloader.h>

RTPlotXWPluginExample::RTPlotXWPluginExample(CumbiaTango *cumbia_tango, QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *lo = new QGridLayout(this);
    QuXtraWidgetPluginLoader xwpl;
    QuXtraWidgetPluginI *pi = xwpl.getPlugin("QuRTPlot");
    if(pi) {
        QWidget *rtPlot = pi->create("QuRTPlot", parent, cumbia_tango, cu_tango_reader_factory);
        lo->addWidget(rtPlot);
        rtPlot->setObjectName("rtPlot");
        // either use the "source" property
        rtPlot->setProperty("source", qApp->arguments()[1]);
        // or
        // rtPlot->setProperty("sources", QStringList() << "s/t/u->get(0,1000)" << "v/w/x->get(0,1000)" );
}
```

Have fun.


