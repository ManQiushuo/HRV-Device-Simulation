#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <QSpinBox>
#include <QListWidget>
#include <QList>
#include <QGraphicsView>
#include <QTimer>
#include <QStatusBar>
#include <QVector>
#include <QtGlobal>
#include <iostream>
#include <string>
#include <QButtonGroup>
#include <QDate>

#include "menu.h"
#include "waveitem.h"
#include "hrvtable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_backButton_clicked();
    void on_menuButton_clicked();
    void on_upButton_clicked();
    void on_selectButton_clicked();
    void on_downButton_clicked();
    void on_leftButton_clicked();
    void on_rightButton_clicked();
    void on_powerButton_clicked();
    void on_batterySpinBox_valueChanged(int arg1);
    void on_chargingCheckBox_stateChanged(int arg1);
    void navigateDownMenu();
    void navigateUpMenu();
    void navigateSubMenu();
    void navigateBack();
    void navigateMainMenu();
    void on_HRVaddButton_clicked(int val);
    void sessionUI(bool ns, bool ss);

private:
    void redLED_on();
    void redLED_off();
    void blueLED_on();
    void blueLED_off();
    void greenLED_on();
    void greenLED_off();
    void updateMenu(const QString, const QStringList);
    void initializeMainMenu(Menu*);
    void updateBreathPacer(int time);
    void addNextInteger();

    Ui::MainWindow *ui;
    bool powerOn;
    QTimer* hrvTimer;
    HRVtable hrvTable;
    QListWidget *activeQListWidget;
    Menu* masterMenu;
    Menu* mainMenuOG;
    QList<int> hrvList;
    QList<int> sessionData_HRV;
    QVector<QList<int>> allData;
    bool inview;
    QStringList recordAndDate;
    int ithRecord;
    QList<float> sessionData_coherence;
    int hrvFrequency;
    bool newSession;
    bool showSummery;
    int breathPacer;
    int challengeLevel;
    QButtonGroup* buttonGroup;
    int dataTable;
    float coherenceScore;
    int currentIndex;
    float achievement;
    int high_c;
    int med_c;
    int low_c;
    int currentCohLevel;
};
#endif // MAINWINDOW_H
