#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    high_c = med_c = low_c = 0;
    currentCohLevel = 0;
    hrvTimer = new QTimer(this);
    connect(hrvTimer, &QTimer::timeout, this, &MainWindow::addNextInteger);
    powerOn = false;
    newSession = false;
    showSummery = false;
    challengeLevel = 1;
    breathPacer = 10;
    ithRecord = 0;
    inview - false;
    ui->setupUi(this);
    ui->screen->setStyleSheet("background-color: black");
    ui->batterySpinBox->setRange(0, 100);
    ui->batterySpinBox->setValue(50);
    ui->batteryLevelBar->setValue(50);
    ui->batteryLevelBar->setVisible(false);
    ui->sBox->setVisible(false);
    ui->sessionSummery->setStyleSheet("QGroupBox { background-color: white; }");
    ui->sessionSummery->setVisible(false);

    //Menu Lebel Setting
    ui->menuLabel->setAlignment(Qt::AlignCenter);
    ui->menuLabel->setStyleSheet("background-color: rgb(135, 206, 250)");
    ui->menuLabel->setVisible(false);

    // Create menu tree
    masterMenu = new Menu("MAIN MENU", {"START NEW SESSION","SETTINGS","LOG/HISTORY"}, nullptr);
    mainMenuOG = masterMenu;
    initializeMainMenu(masterMenu);

    // Initialize the main menu view
    activeQListWidget = ui->mainMenuListView;
    activeQListWidget->addItems(masterMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);
    ui->menuLabel->setText(masterMenu->getName());

    //Menu List Setting
    ui->mainMenuListView->setVisible(false);

    // device interface button connections
    connect(ui->upButton, &QPushButton::pressed, this, &MainWindow::navigateUpMenu);
    connect(ui->downButton, &QPushButton::pressed, this, &MainWindow::navigateDownMenu);
    connect(ui->selectButton, &QPushButton::pressed, this, &MainWindow::navigateSubMenu);
    connect(ui->backButton, &QPushButton::pressed, this, &MainWindow::navigateBack);
    connect(ui->menuButton, &QPushButton::pressed, this, &MainWindow::navigateMainMenu);

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->HRVgraph->setScene(scene);
    QGraphicsScene* summeryScene = new QGraphicsScene(this);
    ui->summery_hrvGraph->setScene(scene);
    hrvFrequency = 12; // 64/5 -> 12
    ui->breathPacer->setValue(0);
    ui->breathPacer->setFormat("Breath In ...");

    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->radioButton);
    buttonGroup->addButton(ui->radioButton_2);
    ui->radioButton->setChecked(true);
    ui->session_length->setText("Length: ");
    ui->session_achievement->setText("Achievement: ");
    ui->session_coherence->setText("Coherence: ");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNextInteger(){
    if(dataTable >0){
        on_HRVaddButton_clicked(hrvTable.cohGetAt(currentIndex%10));
        if(currentIndex%5 == 0 && currentIndex>4){
            coherenceScore = hrvTable.cohScoreGetAt(((int)currentIndex/5 -1)%10);
            achievement += coherenceScore;
            ui->session_achievement->setText("Achievement: "+QString::number(achievement));
            sessionData_coherence.append(coherenceScore);
            ui->session_coherence->setText("Coherence: "+QString::number(coherenceScore));
            if(challengeLevel == 1){
                if(coherenceScore<0.5){
                    low_c++;
                    redLED_on();
                    blueLED_off();
                    greenLED_off();
                }else if(coherenceScore<0.9){
                    med_c++;
                    redLED_off();
                    blueLED_on();
                    greenLED_off();
                }else{
                    high_c++;
                    redLED_off();
                    blueLED_off();
                    greenLED_on();
                }
            }else if(challengeLevel == 2){
                if(coherenceScore<0.6){
                    low_c++;
                    redLED_on();
                    blueLED_off();
                    greenLED_off();
                }else if(coherenceScore<2.1){
                    med_c++;
                    redLED_off();
                    blueLED_on();
                    greenLED_off();
                }else{
                    high_c++;
                    redLED_off();
                    blueLED_off();
                    greenLED_on();
                }
            }else if(challengeLevel == 3){
                if(coherenceScore<1.8){
                    low_c++;
                    redLED_on();
                    blueLED_off();
                    greenLED_off();
                }else if(coherenceScore<4.0){
                    med_c++;
                    redLED_off();
                    blueLED_on();
                    greenLED_off();
                }else{
                    high_c++;
                    redLED_off();
                    blueLED_off();
                    greenLED_on();
                }
            }else if(challengeLevel == 4){
                if(coherenceScore<4.0){
                    low_c++;
                    redLED_on();
                    blueLED_off();
                    greenLED_off();
                }else if(coherenceScore<6.0){
                    med_c++;
                    redLED_off();
                    blueLED_on();
                    greenLED_off();
                }else{
                    high_c++;
                    redLED_off();
                    blueLED_off();
                    greenLED_on();
                }
            }
        }
    }else{
        on_HRVaddButton_clicked(hrvTable.incGetAt(currentIndex%10));
        if(currentIndex%5 == 0 && currentIndex>4){
            coherenceScore = hrvTable.incScoreGetAt(((int)currentIndex/5 -1)%10);
            sessionData_coherence.append(coherenceScore);
            achievement += coherenceScore;
            ui->session_achievement->setText("Achievement: "+QString::number(achievement));
            ui->session_coherence->setText("Coherence: "+QString::number(coherenceScore));
            if(challengeLevel == 1){
                if(coherenceScore<0.5){
                    low_c++;
                    redLED_on();
                    blueLED_off();
                    greenLED_off();
                }else if(coherenceScore<0.9){
                    med_c++;
                    redLED_off();
                    blueLED_on();
                    greenLED_off();
                }else{
                    high_c++;
                    redLED_off();
                    blueLED_off();
                    greenLED_on();
                }
            }else if(challengeLevel == 2){
                if(coherenceScore<0.6){
                    low_c++;
                    redLED_on();
                    blueLED_off();
                    greenLED_off();
                }else if(coherenceScore<2.1){
                    med_c++;
                    redLED_off();
                    blueLED_on();
                    greenLED_off();
                }else{
                    high_c++;
                    redLED_off();
                    blueLED_off();
                    greenLED_on();
                }
            }else if(challengeLevel == 3){
                if(coherenceScore<1.8){
                    low_c++;
                    redLED_on();
                    blueLED_off();
                    greenLED_off();
                }else if(coherenceScore<4.0){
                    med_c++;
                    redLED_off();
                    blueLED_on();
                    greenLED_off();
                }else{
                    high_c++;
                    redLED_off();
                    blueLED_off();
                    greenLED_on();
                }
            }else if(challengeLevel == 4){
                if(coherenceScore<4.0){
                    low_c++;
                    redLED_on();
                    blueLED_off();
                    greenLED_off();
                }else if(coherenceScore<6.0){
                    med_c++;
                    redLED_off();
                    blueLED_on();
                    greenLED_off();
                }else{
                    high_c++;
                    redLED_off();
                    blueLED_off();
                    greenLED_on();
                }
            }
        }
    }
    currentIndex++;
}


//illume the red LED
void MainWindow::redLED_on(){
    if(currentCohLevel != 1){
        qInfo()<<"--- BEEEEEEP ---";
    }
    currentCohLevel = 1;
    ui->redLed->setStyleSheet("background-color: red"); }
//extinguish the red LED
void MainWindow::redLED_off(){ ui->redLed->setStyleSheet(""); }
//illume the blue LED
void MainWindow::blueLED_on(){
    if(currentCohLevel != 2){
        qInfo()<<"--- BEEEEEEP ---";
    }
    currentCohLevel = 2;
    ui->blueLed->setStyleSheet("background-color: blue"); }
//extinguish the blue LED
void MainWindow::blueLED_off(){ ui->blueLed->setStyleSheet(""); }
//illume the green LED
void MainWindow::greenLED_on(){
    if(currentCohLevel != 3){
        qInfo()<<"--- BEEEEEEP ---";
    }
    currentCohLevel = 3;
    ui->greenLed->setStyleSheet("background-color: green"); }
//extinguish the green LED
void MainWindow::greenLED_off(){ ui->greenLed->setStyleSheet(""); }
//back button
void MainWindow::on_backButton_clicked(){
    //qInfo("BACK button clicked");
}
//menu button
void MainWindow::on_menuButton_clicked(){
    //qInfo("MENU button clicked");
}



//select buttons set
void MainWindow::on_upButton_clicked(){
    //qInfo("UP button clicked");
}
void MainWindow::on_selectButton_clicked(){
    //qInfo("SELECT button clicked");
}
void MainWindow::on_downButton_clicked(){
    //qInfo("DOWN button clicked");
}
void MainWindow::on_leftButton_clicked(){
    //qInfo("LEFT button clicked");
}
void MainWindow::on_rightButton_clicked(){
    //qInfo("RIGHT button clicked");
}



//power button
void MainWindow::on_powerButton_clicked(){
    //turn off the device
    if(powerOn){
        powerOn = false;
        ui->batteryLevelBar->setVisible(false);
        ui->menuLabel->setVisible(false);
        ui->mainMenuListView->setVisible(false);
        ui->screen->setStyleSheet("background-color: black");
        ui->sBox->setVisible(false);
        ui->sessionSummery->setVisible(false);
        newSession = false;
        showSummery = false;
        redLED_off();
        blueLED_off();
        greenLED_off();
        hrvTimer->stop();
    }
    //turn on the device
    else{
        if(ui->batterySpinBox->value()!=0){
            powerOn = true;
            ui->batteryLevelBar->setVisible(true);
            ui->menuLabel->setVisible(true);
            ui->mainMenuListView->setVisible(true);
            ui->screen->setStyleSheet("");
        }
    }
}

//battery spin box changed
void MainWindow::on_batterySpinBox_valueChanged(int arg1)
{
    qInfo()<< QString::number(arg1);
    ui->batteryLevelBar->setValue(arg1);
}

//the device is charging
void MainWindow::on_chargingCheckBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        qInfo()<< "charging ...";
        ui->screen->setStyleSheet("background-color: lightgreen");
        while(ui->batterySpinBox->value() < 100){
            QThread::sleep(1);
            ui->batterySpinBox->setValue(ui->batterySpinBox->value() +10);
        }
        ui->chargingCheckBox->setChecked(false);
        if(powerOn){
            ui->screen->setStyleSheet("");
        }else{
            ui->screen->setStyleSheet("background-color: black");
        }
    }else{
        qInfo()<<"battery is full";
        ui->chargingCheckBox->setChecked(false);
    }
}

//initialize the main menu
void MainWindow::initializeMainMenu(Menu* m) {

    QStringList breathPacerList;
    QStringList challengeLevelList;



    for(int i = 1; i < 31; i++) {
        QString pacer = QString::number(i);
        breathPacerList.append(pacer);
    }

    for(int j = 1; j < 5; j++) {
        QString level = QString::number(j);
        challengeLevelList.append(level);
    }





    Menu* newSession = new Menu("START NEW SESSION", {}, m);
    Menu* settings = new Menu("SETTINGS", {"BREATH PACER SETTING","CHALLENGE LEVEL SETTING"}, m);
    Menu* logOrHistory = new Menu("LOG/HISTORY", {"RESET"}, m);


    m->addChildMenu(newSession);
    m->addChildMenu(settings);
    m->addChildMenu(logOrHistory);

    Menu* breathPacerSetting = new Menu("BREATH PACER SETTING",breathPacerList, settings);
    Menu* challengeLevelSetting = new Menu("CHALLENGE LEVEL SETTING",challengeLevelList, settings);

    settings->addChildMenu(breathPacerSetting);
    settings->addChildMenu(challengeLevelSetting);


    Menu* recordResetMenu = new Menu("RESET",{}, logOrHistory);
    logOrHistory->addChildMenu(recordResetMenu);


    std::vector<Menu*> breathPacer(30);

    for(int i = 0; i < 30; i++) {
        breathPacer[i] = new Menu(breathPacerList[i],{}, breathPacerSetting);
        breathPacerSetting->addChildMenu(breathPacer[i]);
    }

    std::vector<Menu*> chanllengeLevel(4);
    for(int j = 0; j < 4; j++) {
        chanllengeLevel[j] = new Menu(challengeLevelList[j],{}, challengeLevelSetting);
        challengeLevelSetting->addChildMenu(chanllengeLevel[j]);
    }
}

void MainWindow::navigateMainMenu() {
    for(int i=0;i<recordAndDate.size();i++){
        if(masterMenu->getName().mid(2) == recordAndDate[i].section(":",0,0) && inview == true){
            ui->sessionSummery->setVisible(false);
            inview = false;
            break;
        }
    }
    if(!newSession && !showSummery){
        while (masterMenu->getName() != "MAIN MENU"){
            masterMenu = masterMenu->getParent();
        }
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
}

void MainWindow::navigateUpMenu() {
    if(powerOn && !newSession && !showSummery){
        int nextIndex = activeQListWidget->currentRow() - 1;

        if (nextIndex < 0) {
            nextIndex = activeQListWidget->count() - 1;
        }

        activeQListWidget->setCurrentRow(nextIndex);
    }
}

void MainWindow::sessionUI(bool ns, bool ss){
    ui->sBox->setVisible(ns);
    ui->sessionSummery->setVisible(ss);
    if(ns && !ss){
        QGraphicsScene* scene = ui->HRVgraph->scene();
        scene->clear();
        hrvList.clear();
        sessionData_HRV.clear();
        ui->breathPacer->setValue(0);
    }else if(!ns && ss){
        QGraphicsScene* scene = ui->HRVgraph->scene();
        scene->clear();
        QGraphicsScene* summeryScene = ui->summery_hrvGraph->scene();
        WaveItem* waveItem = new WaveItem(sessionData_HRV, ui->summery_hrvGraph->width(), ui->summery_hrvGraph->height());
        summeryScene->addItem(waveItem);
        int minutes = sessionData_HRV.size()/60;
        int seconds = sessionData_HRV.size() - minutes*60;
        float avgC = 0;
        //qInfo()<<sessionData_coherence;
        for(int i=0; i<sessionData_coherence.size(); i++){
            avgC += sessionData_coherence[i];
        }
        if(sessionData_coherence.size()>0){
            avgC = avgC/(float)sessionData_coherence.size();
            //qInfo()<<QString::number((int) high_c/(high_c+med_c+low_c));
            ui->summeryText->setText("Challenge Level: "+QString::number(challengeLevel)+
                                     "\nHigh Coherence: "+QString::number((int) 100*high_c/(high_c+med_c+low_c))+"%"+
                                     "\nMedium Coherence: "+QString::number((int) 100*med_c/(high_c+med_c+low_c))+"%"+
                                     "\nLow Coherence: "+QString::number((int) 100*low_c/(high_c+med_c+low_c))+"%"+
                                     "\nAverage Coherence: "+QString::number(avgC)+
                                     "\nLength of Session: "+QString::number(minutes)+"min"+QString::number(seconds)+"s"+
                                     "\nAchievement Schor: "+QString::number(achievement));
        }else{
            ui->summeryText->setText("Challenge Level: "+QString::number(challengeLevel)+
                                     "\nHigh Coherence: "+QString::number(0)+"%"+
                                     "\nMedium Coherence: "+QString::number(0)+"%"+
                                     "\nLow Coherence: "+QString::number(0)+"%"+
                                     "\nAverage Coherence: "+QString::number(0)+
                                     "\nLength of Session: "+QString::number(minutes)+"min"+QString::number(seconds)+"s"+
                                     "\nAchievement Schor: "+QString::number(0));
        }
    }else if(!ns && !ss){
        ui->session_coherence->setText("Coherence: ");
        ui->session_achievement->setText("Achievement: ");
        ui->batterySpinBox->setValue(ui->batterySpinBox->value()-10);
        if(ui->batterySpinBox->value()==0){
            on_powerButton_clicked();
        }
    }
}

void MainWindow::navigateDownMenu() {
    if(powerOn && !newSession && !showSummery){
        int nextIndex = activeQListWidget->currentRow() + 1;

        if (nextIndex > activeQListWidget->count() - 1) {
            nextIndex = 0;
        }

        activeQListWidget->setCurrentRow(nextIndex);
    }
}

void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems) {

    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);

    ui->menuLabel->setText(selectedMenuItem);
}

void MainWindow::navigateSubMenu() {
    if(powerOn){
        int index = activeQListWidget->currentRow();
        if (index < 0) return;

        //qInfo()<<masterMenu->get(index)->getName();
        if(masterMenu->get(index)->getName() == "LOG/HISTORY"
                && masterMenu->get(index)->getMenuItemsDynamic().size() - 1 < recordAndDate.size()){
               masterMenu = masterMenu->get(index);
               int recordAlready = masterMenu->getMenuItemsDynamic().size() - 1;
               int recordTotal = recordAndDate.size();
               for(int i=recordAlready; i<recordTotal; i++){
                   ithRecord++;
                   QString title = recordAndDate[i].section(":",0,0);
                   title = QString::number(ithRecord) +" " + title;
                   masterMenu->getMenuItemsDynamic().append(title);
                   qInfo()<< title;
                   Menu* addingMenu = new Menu(title,{"View","Delete"},masterMenu);
                   Menu* viewMenu = new Menu("VIEW", {}, addingMenu);
                   Menu* deleteMenu = new Menu("DELETE", {}, addingMenu);
                   addingMenu->addChildMenu(viewMenu);
                   addingMenu->addChildMenu(deleteMenu);
                   masterMenu->addChildMenu(addingMenu);
               }
               MainWindow::updateMenu(masterMenu->getName(),masterMenu->getMenuItemsDynamic());
               return;
        }
        //If the menu is a parent and clicking on it should display more menus.
        if (masterMenu->get(index)->getMenuItems().length() > 0) {
            masterMenu = masterMenu->get(index);
            MainWindow::updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
        }

        else if (masterMenu->getName() == "BREATH PACER SETTING") {
            masterMenu = masterMenu->get(index);
            MainWindow::updateMenu({}, {});
            breathPacer = index+1;
            qInfo()<<breathPacer;
            navigateBack();
            navigateBack();
        }


        else if(masterMenu->get(index)->getName() == "RESET"){
            recordAndDate.clear();
            allData.clear();
            masterMenu->getMenuItemsDynamic().clear();
            masterMenu->getMenuItemsDynamic().append("RESET");
            qInfo()<<"Device Reset to initial status";
            navigateBack();
        }

        else if(masterMenu->get(index)->getName() == "DELETE"){
            QString targetNum = masterMenu->getName().section(" ", 0, 0);
            int target = targetNum.toInt();
            recordAndDate.removeAt(target - 1);
            allData.removeAt(target - 1);
            masterMenu->getParent()->getMenuItemsDynamic().removeAt(target);
            navigateBack();
        }

        else if(masterMenu->get(index)->getName() == "VIEW"){
            inview = true;
            qInfo()<<masterMenu->getName();
             QString targetNum = masterMenu->getName().section(" ", 0, 0);
             int target = targetNum.toInt();
             ui->sessionSummery->setVisible(true);
             ui->summeryText->setText(recordAndDate[target - 1]);
             QGraphicsScene* summeryScene = ui->summery_hrvGraph->scene();
             WaveItem* aWaveItem = new WaveItem(allData[target -1], ui->summery_hrvGraph->width(), ui->summery_hrvGraph->height());
             summeryScene->clear();
             summeryScene->addItem(aWaveItem);
        }

        else if (masterMenu->getName() == "CHALLENGE LEVEL SETTING") {
            masterMenu = masterMenu->get(index);
            MainWindow::updateMenu({}, {});
            challengeLevel = index+1;
            qInfo()<<challengeLevel;
            navigateBack();
            navigateBack();
        }

        else if (masterMenu->get(index)->getName() == "START NEW SESSION") {
            if(!newSession && !showSummery){
                newSession = true;
                currentIndex = 0;
                achievement = 0;
                if(buttonGroup->checkedId() == -2){
                    dataTable = 1;
                    //qInfo()<<"Coh";
                }else{
                    dataTable = -1;
                    //qInfo()<<"Inc";
                }
                hrvTimer->start(1000);
                sessionUI(newSession, showSummery);
            }else if(newSession && !showSummery){
                newSession = false;
                showSummery = true;
                hrvTimer->stop();
                sessionUI(newSession, showSummery);
            }else if(!newSession && showSummery){
                //qInfo()<<sessionData_HRV;
                allData.append(sessionData_HRV);
                QString date = QDate::currentDate().toString();
                QString record =date + ": " + ui->summeryText->toPlainText();
                recordAndDate.append(record);
                showSummery = false;
                currentIndex = 0;
                coherenceScore = 0;
                ui->summeryText->setText("");
                redLED_off();
                blueLED_off();
                greenLED_off();
                sessionUI(newSession, showSummery);

            }
        }

    }
}

void MainWindow::navigateBack() {
    for(int i=0;i<recordAndDate.size();i++){
        if(masterMenu->getName().mid(2) == recordAndDate[i].section(":",0,0) && inview == true){
            ui->sessionSummery->setVisible(false);
            inview = false;
            break;
        }
    }
    if (masterMenu->getName() == "MAIN MENU") {
        activeQListWidget->setCurrentRow(0);
    }
    else {
        masterMenu = masterMenu->getParent();
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
}

//add hrv data
void MainWindow::on_HRVaddButton_clicked(int val)
{
    QGraphicsScene* scene = ui->HRVgraph->scene();
    if(hrvList.size() == 12){
        hrvList.removeAt(0);
        scene->clear();
    }
    hrvList.append(val);
    sessionData_HRV.append(val);
    updateBreathPacer(sessionData_HRV.size());
    int minutes = sessionData_HRV.size()/60;
    int seconds = sessionData_HRV.size() - minutes*60;
    ui->session_length->setText("Length: "+QString::number(minutes)+"min"+QString::number(seconds)+"s");
    //qInfo()<<sessionData_HRV;
    WaveItem* waveItem = new WaveItem(hrvList, ui->HRVgraph->width(), ui->HRVgraph->height());
    scene->addItem(waveItem);

    // Add the y-axis to the scene
    QGraphicsLineItem* yAxis = new QGraphicsLineItem(0, 0, 0, ui->HRVgraph->height());
    QPen pen;
    pen.setWidth(2);
    yAxis->setPen(pen);
    scene->addItem(yAxis);
    // Add labels to the y-axis
    int numLabels = 5;  // Number of labels to add
    int labelSpacing = ui->HRVgraph->height() / (numLabels - 1);  // Spacing between labels
    for (int i = 0; i <= numLabels; i++) {
        int value = (100/numLabels)*i + 20;  // Compute the label value
        QString labelText = QString::number(value);  // Convert value to string
        QGraphicsSimpleTextItem* label = new QGraphicsSimpleTextItem(labelText);
        label->setPos(-label->boundingRect().width() +25, -10+((numLabels-i)* ui->HRVgraph->height()/(numLabels+1)));
        scene->addItem(label);
    }
}

void MainWindow::updateBreathPacer(int time){
    int this_session = time % breathPacer;
    if(this_session < breathPacer/2){
        ui->breathPacer->setValue(100*this_session / (breathPacer/2));
        ui->breathPacer->setFormat("Breath In ...");
    }else{
        ui->breathPacer->setValue(100*((breathPacer/2) - (this_session - (breathPacer/2)))/(breathPacer/2));
        ui->breathPacer->setFormat("Breath Out ...");
    }
}
