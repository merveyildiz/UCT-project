#include <iostream>
#include <QVector>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <stdio.h>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>
#include <qglobal.h>    /* qsrand, qrand */
#include <time.h>       /* time */
#include <math.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "draglabel.h"
#include "slottable.h"
#include "epsmoea.h"

#define POPSIZE 100
#define NEVALUATION 1500000
#define NOBJECTIVE 3
#define NCONSTRAINT 0
#define NREAL 0
#define PROBCROSS 0.75
#define DIMENSION 3

#define SLOT_SIZE 45

using namespace std;

QVector <QString> courses;
QVector <int> nsections;
QVector <QVector <QString> *> teachers;
QVector <int> nLecture;
QVector <int> nLab;
QVector <int> nLabHour;
QVector <int> parallel_lab;
QVector <int> parallel_lecture;
QVector <int> PS;
QVector <int> semester;
QVector <int> blok; // 1/0
QVector <int> elective;
int count_course;
QVector <QTableWidget *> wholeTables(0);
int scheduling[NSEMESTER][NDAY][NHOUR];
int lab_scheduling[NDAY][NHOUR];
QString best_pop_out_individual[POPSIZE];
int table[500][7];
int count_lecturer;
QVector <QString> lecturer_list;
QVector <QTableWidget *> lecturer(0);
/*  table[500][7]
 *  0 = ID
 * 1 = TYPE
 * 2 = DURATION
 * 3 = SUBID
4= MAX_SLOT
*   5= LAB_AMOUNT
*   6= ELECTIVE*/
int table_counter;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector <DragLabel *> labels;

//    QVector <QCheckBox *> checkBoxes1;
//    QVector <QCheckBox *> checkBoxes2;

    wholeTables.append(ui->tableWidget_1);
    wholeTables.append(ui->tableWidget_2);
    wholeTables.append(ui->tableWidget_3);
    wholeTables.append(ui->tableWidget_4);
    wholeTables.append(ui->tableWidget_5);
    wholeTables.append(ui->tableWidget_6);
    wholeTables.append(ui->tableWidget_7);
    wholeTables.append(ui->tableWidget_8);
    wholeTables.append(ui->tableWidget_9);
    wholeTables.append(ui->tableWidget_10);
    wholeTables.append(ui->tableWidget_11);
    wholeTables.append(ui->tableWidget_12);
    wholeTables.append(ui->tableWidget_13);
    wholeTables.append(ui->tableWidget_14);
    wholeTables.append(ui->tableWidget_15);
    wholeTables.append(ui->tableWidget_16);
    wholeTables.append(ui->tableWidget_17);
    wholeTables.append(ui->tableWidget_18);
    wholeTables.append(ui->tableWidget_19);
    wholeTables.append(ui->tableWidget_20);
    wholeTables.append(ui->tableWidget_21);
    wholeTables.append(ui->tableWidget_22);
    wholeTables.append(ui->tableWidget_23);
    wholeTables.append(ui->tableWidget_24);
    wholeTables.append(ui->tableWidget_25);
    wholeTables.append(ui->tableWidget_26);
    wholeTables.append(ui->tableWidget_27);
    wholeTables.append(ui->tableWidget_28);

    /*wholeTables.at(0)->setItem(0,0,new QTableWidgetItem("Merve\nYILDIZ"));  //deneme

    QColor color( Qt::red );
    wholeTables.at(0)->item(0,0)->setBackground(color);
    //wholeTables.at(0)->item(0,0)->setBackground(Qt::white);*/


    SlotTable * control1 = new SlotTable();
    SlotTable * control2 = new SlotTable();
    SlotTable * control3 = new SlotTable();
    SlotTable * control4 = new SlotTable();
    SlotTable * control5 = new SlotTable();
    SlotTable * control6 = new SlotTable();
    SlotTable * control7 = new SlotTable();
    SlotTable * control8 = new SlotTable();
    SlotTable * control9 = new SlotTable();
    SlotTable * control10 = new SlotTable();
    SlotTable * control11 = new SlotTable();
    SlotTable * control12 = new SlotTable();
    SlotTable * control13 = new SlotTable();
    SlotTable * control14 = new SlotTable();
    SlotTable * control15 = new SlotTable();
    SlotTable * control16 = new SlotTable();
    SlotTable * control17 = new SlotTable();
    SlotTable * control18 = new SlotTable();
    SlotTable * control19 = new SlotTable();
    SlotTable * control20 = new SlotTable();

    control1->source = wholeTables.at(0);
    control1->destination = wholeTables.at(8);

    control2->source = wholeTables.at(1);
    control2->destination = wholeTables.at(9);

    control3->source = wholeTables.at(2);
    control3->destination = wholeTables.at(10);

    control4->source = wholeTables.at(2);
    control4->destination = wholeTables.at(12);

    control5->source = wholeTables.at(3);
    control5->destination = wholeTables.at(11);

    control6->source = wholeTables.at(3);
    control6->destination = wholeTables.at(13);

    control7->source = wholeTables.at(4);
    control7->destination = wholeTables.at(14);

    control8->source = wholeTables.at(4);
    control8->destination = wholeTables.at(16);

    control9->source = wholeTables.at(5);
    control9->destination = wholeTables.at(15);

    control10->source = wholeTables.at(5);
    control10->destination = wholeTables.at(17);

    control11->source = wholeTables.at(6);
    control11->destination = wholeTables.at(18);

    control12->source = wholeTables.at(7);
    control12->destination = wholeTables.at(19);

    control13->source = wholeTables.at(0);
    control13->destination = wholeTables.at(20);
    control14->source = wholeTables.at(1);
    control14->destination = wholeTables.at(21);
    control15->source = wholeTables.at(2);
    control15->destination = wholeTables.at(22);
    control16->source = wholeTables.at(3);
    control16->destination = wholeTables.at(23);
    control17->source = wholeTables.at(4);
    control17->destination = wholeTables.at(24);
    control18->source = wholeTables.at(5);
    control18->destination = wholeTables.at(25);
    control19->source = wholeTables.at(6);
    control19->destination = wholeTables.at(26);
    control20->source = wholeTables.at(7);
    control20->destination = wholeTables.at(27);


    connect(wholeTables.at(0),SIGNAL(cellChanged(int,int)),control1, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(1),SIGNAL(cellChanged(int,int)),control2, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(2),SIGNAL(cellChanged(int,int)),control3, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(2),SIGNAL(cellChanged(int,int)),control4, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(3),SIGNAL(cellChanged(int,int)),control5, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(3),SIGNAL(cellChanged(int,int)),control6, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(4),SIGNAL(cellChanged(int,int)),control7, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(4),SIGNAL(cellChanged(int,int)),control8, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(5),SIGNAL(cellChanged(int,int)),control9, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(5),SIGNAL(cellChanged(int,int)),control10, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(6),SIGNAL(cellChanged(int,int)),control11, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(7),SIGNAL(cellChanged(int,int)),control12, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(0),SIGNAL(cellChanged(int,int)),control13, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(1),SIGNAL(cellChanged(int,int)),control14, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(2),SIGNAL(cellChanged(int,int)),control15, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(3),SIGNAL(cellChanged(int,int)),control16, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(4),SIGNAL(cellChanged(int,int)),control17, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(5),SIGNAL(cellChanged(int,int)),control18, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(6),SIGNAL(cellChanged(int,int)),control19, SLOT(UpdateTable(int,int)));
    connect(wholeTables.at(7),SIGNAL(cellChanged(int,int)),control20, SLOT(UpdateTable(int,int)));

    count_lecturer = 0;
    count_course = 0;
    int tmp;
    QFile file(":/MyFiles/input_file.csv");
    if (!file.open(QIODevice::ReadOnly)) {  //File could not be opened
         qDebug() << file.errorString() << "input_file.csv";
    }
    else{
        file.readLine();
        while (!file.atEnd()) {
            //QCheckBox * checkBox1;
            //QCheckBox * checkBox2;
            QString line = file.readLine();

            //qDebug() << line.split(';').at(2).toInt();
            courses.append(line.split(';').at(0));
            nsections.append(line.split(';').at(1).toInt());
            tmp = line.split(';').at(1).toInt();
            teachers.append(new QVector <QString>());
            int i, j;
            for(i=0; i<tmp; i++){
                ((QVector <QString>*)(teachers.at(count_course)))->append(line.split(';').at(i+2));
                for(j=0; j<lecturer_list.size(); j++){
                    if(line.split(';').at(i+2) == lecturer_list.at(j)){
                        break;
                    }
                }
                if(j == lecturer_list.size()){
                    lecturer_list.append(line.split(';').at(i+2));
                    count_lecturer++;
                }
            }
            i--;
            nLecture.append(line.split(';').at(3+i).toInt());
            nLab.append(line.split(';').at(4+i).toInt());
            nLabHour.append(line.split(';').at(5+i).toInt());
            parallel_lab.append(line.split(';').at(6+i).toInt());
            parallel_lecture.append(line.split(';').at(7+i).toInt());
            PS.append(line.split(';').at(8+i).toInt());
            semester.append(line.split(';').at(9+i).toInt());
            blok.append(line.split(';').at(10+i).toInt());
            elective.append(line.split(';').at(11+i).toInt());
            labels.append( new DragLabel(courses.at(count_course), this));

            //qDebug()<< line.split(';').at(0).split(' ').at(0) << line.split(';').at(0).split(' ').at(1) << line.split(';').at(2) <<line.split(';').at(3) <<line.split(';').at(4) <<line.split(';').at(5) ;
            //list_of_course_teacher.append(line.split(';', QString::SkipEmptyParts).at(1));
            //lbl->setText(line.split(';').first());

            /*lbl->move(5, 5);
            lbl->show();
            lbl->setAttribute(Qt::WA_DeleteOnClose);*/
 /*         checkBox1 = new QCheckBox;
            checkBox2 = new QCheckBox;
            checkBox1->setText("1");
            checkBox2->setText("2");
            checkBoxes1.append(checkBox1);
            checkBoxes2.append(checkBox2);*/

//            QVBoxLayout *vlayout = new QVBoxLayout();
//            vlayout->addWidget(checkBoxes1.at(count_course));
//            vlayout->addWidget(checkBoxes2.at(count_course));

            QHBoxLayout *hlayout = new QHBoxLayout();
            hlayout->addWidget(labels.at(count_course));
            //hlayout->addLayout(vlayout);

            ui->verticalLayout->addLayout(hlayout);

            count_course++;
        }
    }
    file.close();

    for(int i=0; i<count_lecturer; i++){

        QString x = "new tab";
        x = lecturer_list.at(i);
        lecturer.append(new QTableWidget);
        lecturer.at(i)->setRowCount(NHOUR);
        lecturer.at(i)->setColumnCount(NDAY);
        ui->tabWidget->insertTab(13+i, lecturer.at(i), x);
    }
    /*for(int i=0; i<count_lecturer; i++){
        qDebug() << lecturer_list[i];
    }*/
    /*for (int i=0; i<8; i++){
        for (int j=0; j<5; j++){
            for (int k=0; k<10; k++){
                scheduling[i][j][k] = -1;
            }
        }
    }
    qsrand(time(NULL));                                         //initialize random seed
    for(int i=0; i<count_course; i++){
        for(int j=0; j<(nLecture[i] + (nLabHour[i])); j++){
            int High=count_course-1, Low=0;                                //initialization high and low boundaries
            int random = qrand() % ((High + 1) - Low) + Low;   // generate random number between low<= and high<=
            High=7;
            int random1 = qrand() % ((High + 1) - Low) + Low;   //semester
            High=4;
            int random2 = qrand() % ((High + 1) - Low) + Low;   //day
            High=9;
            int random3 = qrand() % ((High + 1) - Low) + Low;   //hour

            if(scheduling[random1][random2][random3] != -1){
                //i--;
                wholeTables.at(random1)->item(random3,random2)->setText(wholeTables.at(random1)->item(random3, random2)->text() + "\r\n" + courses.at( random ) );
                wholeTables.at(random1)->item(random3,random2)->setBackground(Qt::red);
                qDebug() << "cakismali ders var, tekrar deneniyor" << random1 << random2 <<random3 <<random;
            }
            else{
                scheduling[random1][random2][random3] = random;
                wholeTables.at(random1)->setItem(random3, random2, new QTableWidgetItem( courses.at( random ) ));
            }
        }
    }*/



    /**
     * QVBoxLayout* layout = new QVBoxLayout(ui->verticalLayout_2);

    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    QPushButton *button3 = new QPushButton("Three");
    QPushButton *button4 = new QPushButton("Four");
    QPushButton *button5 = new QPushButton("Five");
    //QLabel *lbl = new QLabel;
    //lbl->setText("Dynamic label");

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(button1);
    layout->addWidget(button2);
    //layout->addWidget(lbl);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(button5);

    ui->verticalLayout_2->addLayout(layout);*/

    ui->label->setText("UCT with NSGA-II");
    //ui->verticalLayout_2->addItem(new QLabel(this->ui->verticalLayout,0));
    ui->tabWidget->setTabText(0,"S 1");
    ui->tabWidget->setTabText(1,"S 2");
    ui->tabWidget->setTabText(2,"S 3");
    ui->tabWidget->setTabText(3,"S 4");
    ui->tabWidget->setTabText(4,"S 5");
    ui->tabWidget->setTabText(5,"S 6");
    ui->tabWidget->setTabText(6,"S 7");
    ui->tabWidget->setTabText(7,"S 8");
    ui->tabWidget->setTabText(8,"S 1-2-3-4");
    ui->tabWidget->setTabText(9,"S 3-4-5-6");
    ui->tabWidget->setTabText(10,"S 5-6-7-8");
    ui->tabWidget->setTabText(11,"S 1-2-3-4-5-6-7-8");
    ui->tabWidget->setTabText(12,"Meeting Hours");
    //ui->tabWidget->setTabEnabled(1, false);
    for(int i=0; i<NSEMESTER; i++){
        ui->tabWidget->tabBar()->setTabTextColor(i,Qt::blue);
    }
    //ui->tabWidget->setTabsClosable(true);
    //ui->tabWidget->widget(1)->setEnabled(false);
    //ui->tabWidget->addTab("newTab");

    ui->label->setAutoFillBackground(true);
    ui->label->setFrameShape(QFrame::Panel);
    ui->label->setFrameShadow(QFrame::Raised);

    /**
    setAcceptDrops(true);
    setMinimumSize(400, qMax(200, y));
    setWindowTitle(tr("Draggable Text"));*/

    //setAcceptDrops(true);                 //Enable Drag and Drop

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*MainWindow::DragWidget(QWidget *parent)
    : QWidget(parent)
{
    QFile dictionaryFile(":/dictionary/words.txt");
    dictionaryFile.open(QIODevice::ReadOnly);
    QTextStream inputStream(&dictionaryFile);

    int x = 5;
    int y = 5;

    while (!inputStream.atEnd()) {
        QString word;
        inputStream >> word;
        if (!word.isEmpty()) {
            DragLabel *wordLabel = new DragLabel(word, this);
            wordLabel->move(x, y);
            wordLabel->show();
            wordLabel->setAttribute(Qt::WA_DeleteOnClose);
            x += wordLabel->width() + 2;
            if (x >= 245) {
                x = 5;
                y += wordLabel->height() + 2;
            }
        }
    }
*/
    /*
    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);
    */

/*    setAcceptDrops(true);
    setMinimumSize(400, qMax(200, y));
    setWindowTitle(tr("Draggable Text"));
}**/

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText()) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasText()) {
        const QMimeData *mime = event->mimeData();
        QStringList pieces = mime->text().split(QRegExp("\\s+"),
                             QString::SkipEmptyParts);
        QPoint position = event->pos();
        QPoint hotSpot;

        QList<QByteArray> hotSpotPos = mime->data("application/x-hotspot").split(' ');
        if (hotSpotPos.size() == 2) {
            hotSpot.setX(hotSpotPos.first().toInt());
            hotSpot.setY(hotSpotPos.last().toInt());
        }

        foreach (QString piece, pieces) {
            DragLabel *newLabel = new DragLabel(piece, this);
            newLabel->move(position - hotSpot);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            position += QPoint(newLabel->width(), 0);
        }

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
    foreach (QObject *child, children()) {
        if (child->inherits("QWidget")) {
            QWidget *widget = static_cast<QWidget *>(child);
            if (!widget->isVisible())
                widget->deleteLater();
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPoint hotSpot = event->pos() - child->pos();

    QMimeData *mimeData = new QMimeData;
    mimeData->setText(child->text());
    mimeData->setData("application/x-hotspot",
                      QByteArray::number(hotSpot.x()) + " " + QByteArray::number(hotSpot.y()));

    QPixmap pixmap(child->size());
    child->render(&pixmap);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(hotSpot);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

    if (dropAction == Qt::MoveAction)
        child->close();
}


void MainWindow::on_pushButton_clicked()
{
    QString input_filename = "merve3.in";
    QString input_filename1 = "course_list.csv";
    QString input_filename2 = "scheduling.in";
    QFile inputFile_NSGA(input_filename);
    QFile inputFile_NSGA1(input_filename1);
    QFile inputFile_NSGA2(input_filename2);
    if(!inputFile_NSGA.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << input_filename << "for output";
        exit(1);
    }
    if(!inputFile_NSGA1.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << input_filename1 << "for output";
        exit(1);
    }
    if(!inputFile_NSGA2.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << input_filename2 << "for output";
        exit(1);
    }
    QTextStream outStream(&inputFile_NSGA);
    QTextStream outStream1(&inputFile_NSGA1);
    QTextStream outStream2(&inputFile_NSGA2);
    ////////////////////////////////////////////////////////
    int i, j, k;
    for(i=0; i<NSEMESTER; i++){
        for(j=0; j<NDAY; j++){
            for(k=0; k<NHOUR; k++){
                scheduling[i][j][k] = 0;
            }
        }
    }
    reset_table();
    for(i=0; i<NSEMESTER; i++){
        for(j=0; j<NHOUR - 1; j++){
            for(k=0; k<NDAY; k++){
                outStream2 << scheduling[i][k][j] << " ";
            }
            outStream2 << "\n";
        }
        outStream2 << "\n";
    }
    ///////////////////////////////////////////////

    outStream << POPSIZE << endl;
    outStream << NEVALUATION << endl;
    outStream << NOBJECTIVE << endl;
    outStream << NCONSTRAINT << endl;
    outStream << NREAL << endl;

    table_counter = 0;
    for(int i=0; i<count_course; i++){
        for(int j=0; j<nsections[i]; j++){      //each sections divide (1+2) lecture or not divide (3)
            if(nLecture[i] == 3 && blok[i] == 0){
                table[table_counter][0] = i;
                table[table_counter][1] = 0;
                table[table_counter][2] = 1;
                table[table_counter][3] = j;
                table[table_counter][5] = nLab[i];
                table[table_counter][6] = elective[i];
                table_counter++;
                table[table_counter][0] = i;
                table[table_counter][1] = 0;
                table[table_counter][2] = 2;
                table[table_counter][3] = j;
                table[table_counter][5] = nLab[i];
                table[table_counter][6] = elective[i];
                table_counter++;
            }
            else{
                table[table_counter][0] = i;
                table[table_counter][1] = 0;
                table[table_counter][2] = nLecture[i];
                table[table_counter][3] = j;
                table[table_counter][5] = nLab[i];
                table[table_counter][6] = elective[i];
                table_counter++;
            }
        }
        int num_lab;
        if(parallel_lab[i] == 1){
            table[table_counter][0] = i;
            table[table_counter][1] = 1;
            table[table_counter][2] = nLabHour[i] + PS[i];
            table[table_counter][5] = nLab[i];
            table[table_counter][6] = elective[i];
            table_counter++;
        }
        else{
            for(num_lab = nLab[i]; num_lab>0; num_lab--){
                table[table_counter][0] = i;
                table[table_counter][1] = 1;
                table[table_counter][2] = nLabHour[i] + PS[i];
                table[table_counter][5] = nLab[i];
                table[table_counter][6] = elective[i];
                table_counter++;
            }
        }
        if(PS[i] > 0 && nLab[i] == 0){
            table[table_counter][0] = i;
            table[table_counter][1] = 2;
            table[table_counter][2] = PS[i];
            table[table_counter][5] = nLab[i];
            table[table_counter][6] = elective[i];
            table_counter++;
        }
    }
    outStream << table_counter << endl;
    outStream1 << table_counter << endl;
    for(int i=0; i<table_counter;i++){
        int num_slots;
        if(table[i][2] == 1){
            num_slots = 25;
        }
        else if(table[i][2] == 2){
            num_slots = 25;
        }
        else if(table[i][2] == 3){
            num_slots = 20;
        }
        outStream << ceil(log2(num_slots)) << " 0 " << num_slots-1 << endl;
        table[i][4] = num_slots;
        outStream1 << courses[table[i][0]] << ";" ;
        if(table[i][1] == 0){
            //qDebug() << "MERV EEEEEEEEEEEEEEEEEEEEEEEEEEEEEE "<<table[i][0]<<" "<< table[i][3];
            outStream1 << teachers.at(table[i][0])->at(table[i][3])<< ";";
        }
        else{
             outStream1 << "ASSISTANT;";
        }
        outStream1 << table[i][1] << ";";
        outStream1 << semester[table[i][0]] << ";";
        outStream1 << table[i][2] << ";";
        outStream1 << table[i][5] << ";";
        outStream1 << table[i][6] << endl;
            //table[i][1] << " " << table[i][2] << " " << table[i][3] << endl;
    }
    outStream << PROBCROSS << endl;
    outStream << 1/(float)table_counter << endl;
    outStream << 1 << endl;
    if (DIMENSION == 2){
        outStream << 2 <<endl;//2D
        outStream << 1 <<endl;
        outStream << 2 << endl;
    }
    if (DIMENSION == 3){
        outStream << 3 << endl; //3D
        outStream << 1 << endl; //Enter the objective for X axis display
        outStream << 2 << endl; //Enter the objective for Y axis display
        outStream << 3 << endl; //Enter the objective for Z axis display
        outStream << 60 << endl;//Enter the first angle (an integer in the range 0-180) (if not known, enter 60)
        outStream << 30 << endl;//Enter the second angle (an integer in the range 0-360) (if not known, enter 30)
    }

    inputFile_NSGA.close();     /* Close the file */
    inputFile_NSGA1.close();     /* Close the file */
    inputFile_NSGA2.close();     /* Close the file */

    system("cp /home/merve/Desktop/nsga2-gnuplot-v1.1.6/nsga2-gnuplot-v1.1.6/nsga2r /home/merve/Project/myFirstWidget");
    system("/home/merve/Project/myFirstWidget/nsga2r 0.7 < /home/merve/Project/build-project-Desktop_Qt_5_5_0_GCC_64bit-Debug/merve3.in");
    //system("cp /home/merve/Project/build-project-Desktop_Qt_5_5_0_GCC_64bit-Debug/best_pop.out /home/merve/Project/myFirstWidget");
    reading_best_pop_out();
    QMessageBox::information(this, "NSGA-ii", "NSGA-ii finished");
}

void MainWindow::reading_best_pop_out(){
    /*Reading best.out*/
    QFile file("/home/merve/Project/build-project-Desktop_Qt_5_5_0_GCC_64bit-Debug/best_pop.out");
    if (!file.open(QIODevice::ReadOnly)) {  //File could not be opened
         qDebug() << file.errorString();
    }
    else{
        int i=0;
        QString fit1, fit2, fit3;
        file.readLine();
        file.readLine();
        ui->comboBox->addItem("");
        while (!file.atEnd()) {
            best_pop_out_individual[i] = file.readLine();
            fit1 = best_pop_out_individual[i].split("\t").at(0);
            fit2 = best_pop_out_individual[i].split("\t").at(1);
            fit3 = best_pop_out_individual[i].split("\t").at(2);
            ui->comboBox->addItem(QString::number(i+1) + " " + fit1 + " " + fit2 + " " + fit3);
            i++;
        }
        file.close();       /* Close the file */
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    int row = 0;
    int col = 0;
    int slot;
    int index_lec;
    QString constantString = QString::number(1);

    if( ui->comboBox->currentText() == ""){
        reset_table();
        qDebug() << "MERVE";
    }
    else{
        QString line = best_pop_out_individual[ui->comboBox->currentText().split(" ").at(0).toInt() -1];
        int index = 0;
        for (int i=0; i<NOBJECTIVE; i++){
            index++;
            //qDebug() << line.split('\t').at(i);
        }
        for (int i=0; i<NCONSTRAINT; i++){
            index++;
        }
        for(int i=0; i<NREAL; i++){
            index++;
        }
        for(int i=0; i<table_counter; i++){
            int sum = 0, binary_var = 0;
            for(int j=0; j<ceil(log2(table[i][4])); j++){
                //calculating binary
                if(line.split('\t').at(index) == constantString){
                    sum += pow(2,ceil(log2(table[i][4]))-1-j);
                }
                index++;
            }
            binary_var = 0 + (double)sum*(table[i][4]-1 - 0)/(double)(pow(2,ceil(log2(table[i][4])))-1);
            slot = binary_var ;
            if(table[i][2] == 1){
                col = (slot/5) ;
                if(slot%5<3){
                        row = (slot%5)+2;
                }else{
                        row = (slot%5)+4;
                }
            }
            else if(table[i][2] == 2){
                col = (binary_var/5) ;
                if(slot%5 == 0){
                        row = 0;
                }else if(slot%5 == 1){
                        row = 2;
                }if(slot%5 == 2){
                        row = 3;
                }if(slot%5 == 3){
                        row = 5;
                }if(slot%5 == 4){
                        row = 7;
                }
                if(table[i][1] == 0){   //if Lecture
//
                    if(table[i][6] == 1){   //if Elective
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                        if(wholeTables.at(7)->item(row+1,col)){
                            wholeTables.at(7)->item(row+1,col)->setText(wholeTables.at(7)->item(row+1,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(7)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(7)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                    }
                    else{
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                    }
                    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    index_lec= lecturer_list.indexOf(teachers.at(table[i][0])->at(table[i][3]));
                    //qDebug() << index_lec;
                    if( lecturer.at(index_lec)->item(row+1,col) ){
                        lecturer.at(index_lec)->item(row+1,col)->setText(lecturer.at(index_lec)->item(row+1,col)->text() + " + " + courses[table[i][0]]);
                        lecturer.at(index_lec)->item(row+1,col)->setBackground(Qt::magenta);
                    }
                    else{
                        lecturer.at(index_lec)->setItem(row+1, col, new QTableWidgetItem(courses[table[i][0]]));
                    }
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                }
                else if(table[i][1] == 1){
//
                    if(table[i][6] == 1){
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                        if(wholeTables.at(7)->item(row+1,col)){
                            wholeTables.at(7)->item(row+1,col)->setText(wholeTables.at(7)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(7)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(7)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                    }
                    else{
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                    }
                }
                else if(table[i][1] == 2){
//
                    if(table[i][6] == 1){
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() +  " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                        if(wholeTables.at(7)->item(row+1,col)){
                            wholeTables.at(7)->item(row+1,col)->setText(wholeTables.at(7)->item(row+1,col)->text() +  " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(7)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(7)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                    }
                    else{
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() +  " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                    }
                }
            }
            else if(table[i][2] == 3){
                col = (binary_var/4) ;
                if(slot%4 == 0){
                    row = 0;
                }if(slot%4 == 1){
                    row = 2;
                }if(slot%4 == 2){
                    row = 4;
                }if(slot%4 == 3){
                    row = 5;
                }
                if(table[i][1] == 0){   //if Lecture

                    if(table[i][6] == 1){   //if Elective
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                        if(wholeTables.at(7)->item(row+1,col)){
                            wholeTables.at(7)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(7)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(7)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                    }
                    else{
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                    }
                    ///////////
                    index_lec= lecturer_list.indexOf(teachers.at(table[i][0])->at(table[i][3]));
                    if( lecturer.at(index_lec)->item(row+1,col) ){
                        lecturer.at(index_lec)->item(row+1,col)->setText(lecturer.at(index_lec)->item(row+1,col)->text() + " + " + courses[table[i][0]]);
                        lecturer.at(index_lec)->item(row+1,col)->setBackground(Qt::magenta);
                    }
                    else{
                        lecturer.at(index_lec)->setItem(row+1, col, new QTableWidgetItem(courses[table[i][0]]));
                    }
                    ///////////

                    if(table[i][6] == 1){   //if Elective
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                        if(wholeTables.at(7)->item(row+2,col)){
                            wholeTables.at(7)->item(row+2,col)->setText(wholeTables.at(7)->item(row+2,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(7)->item(row+2,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                    }
                    else{
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->text() + " + " + courses[table[i][0]]);
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]]));
                        }
                    }
                    ///////////
                    ///////////
                    index_lec= lecturer_list.indexOf(teachers.at(table[i][0])->at(table[i][3]));
                    //qDebug() << index_lec;
                    if( lecturer.at(index_lec)->item(row+2,col) ){
                        lecturer.at(index_lec)->item(row+2,col)->setText(lecturer.at(index_lec)->item(row+2,col)->text() + " + " + courses[table[i][0]]);
                        lecturer.at(index_lec)->item(row+2,col)->setBackground(Qt::magenta);
                    }
                    else{
                        lecturer.at(index_lec)->setItem(row+2, col, new QTableWidgetItem(courses[table[i][0]]));
                    }
                    ///////////
                    ///////////
                }
                else if(table[i][1] == 1){  //if Lab
                    if(table[i][6] == 1){   //if Elective
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                        //
                        if(wholeTables.at(7)->item(row+1,col)){
                            wholeTables.at(7)->item(row+1,col)->setText(wholeTables.at(7)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(7)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(7)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                        if(wholeTables.at(7)->item(row+2,col)){
                            wholeTables.at(7)->item(row+2,col)->setText(wholeTables.at(7)->item(row+2,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(7)->item(row+2,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                    }
                    else{
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->text() + " + " + courses[table[i][0]] + ".L");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                        }
                    }
                }else if(table[i][1] == 2){ //if PS
                    if(table[i][6] == 1){   //if Elective
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->text() + " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                        //
                        if(wholeTables.at(7)->item(row+1,col)){
                            wholeTables.at(7)->item(row+1,col)->setText(wholeTables.at(7)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(7)->item(row+1,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(7)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                        if(wholeTables.at(7)->item(row+2,col)){
                            wholeTables.at(7)->item(row+2,col)->setText(wholeTables.at(7)->item(row+2,col)->text() + " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(7)->item(row+2,col)->setBackground(Qt::yellow);
                        }
                        else{
                            wholeTables.at(7)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                    }
                    else{
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->text() + " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+1,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+1,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                        if(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)){
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->text() + " + " + courses[table[i][0]] + ".PS");
                            wholeTables.at(semester[table[i][0]]-1)->item(row+2,col)->setBackground(Qt::red);
                        }
                        else{
                            wholeTables.at(semester[table[i][0]]-1)->setItem(row+2,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                        }
                    }
                }
            }
            if(table[i][1] == 0){
                if(table[i][6] == 1){   //if Elective
                    if(wholeTables.at(semester[table[i][0]]-1)->item(row,col)){
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row,col)->text() + " + " + courses[table[i][0]]);
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setBackground(Qt::yellow);
                    }
                    else{
                        wholeTables.at(semester[table[i][0]]-1)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]]));
                    }
                    //
                    if(wholeTables.at(7)->item(row,col)){
                        wholeTables.at(7)->item(row,col)->setText(wholeTables.at(7)->item(row,col)->text() + " + " + courses[table[i][0]]);
                        wholeTables.at(7)->item(row,col)->setBackground(Qt::yellow);
                    }
                    else{
                        wholeTables.at(7)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]]));
                    }
                }
                else{
                    if(wholeTables.at(semester[table[i][0]]-1)->item(row,col)){
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row,col)->text() + " + " + courses[table[i][0]]);
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setBackground(Qt::red);
                    }
                    else{
                        wholeTables.at(semester[table[i][0]]-1)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]]));
                    }
                }
                ///////////
                index_lec= lecturer_list.indexOf(teachers.at(table[i][0])->at(table[i][3]));
                //qDebug() << index_lec;
                if( lecturer.at(index_lec)->item(row,col) ){
                    lecturer.at(index_lec)->item(row,col)->setText(lecturer.at(index_lec)->item(row,col)->text() + " + " + courses[table[i][0]]);
                    lecturer.at(index_lec)->item(row,col)->setBackground(Qt::magenta);
                }
                else{
                    lecturer.at(index_lec)->setItem(row, col, new QTableWidgetItem(courses[table[i][0]]));
                }
                ///////////
            }else if(table[i][1] == 1){
                if(table[i][6] == 1){   //if Elective
                    if(wholeTables.at(semester[table[i][0]]-1)->item(row,col)){
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row,col)->text() + " + " + courses[table[i][0]] + ".L");
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setBackground(Qt::yellow);
                    }
                    else{
                        wholeTables.at(semester[table[i][0]]-1)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                    }
                    //
                    if(wholeTables.at(7)->item(row,col)){
                        wholeTables.at(7)->item(row,col)->setText(wholeTables.at(7)->item(row,col)->text() + " + " + courses[table[i][0]] + ".L");
                        wholeTables.at(7)->item(row,col)->setBackground(Qt::yellow);
                    }
                    else{
                        wholeTables.at(7)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                    }
                }
                else{
                    if(wholeTables.at(semester[table[i][0]]-1)->item(row,col)){
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row,col)->text() + " + " + courses[table[i][0]] + ".L");
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setBackground(Qt::red);
                    }
                    else{
                        wholeTables.at(semester[table[i][0]]-1)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]] + ".L"));
                    }
                }
            }else if(table[i][1] == 1){
                if(table[i][6] == 1){   //if Elective
                    if(wholeTables.at(semester[table[i][0]]-1)->item(row,col)){
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row,col)->text() + " + " + courses[table[i][0]] + ".PS");
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setBackground(Qt::yellow);
                    }
                    else{
                        wholeTables.at(semester[table[i][0]]-1)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                    }
                    //
                    if(wholeTables.at(7)->item(row,col)){
                        wholeTables.at(7)->item(row,col)->setText(wholeTables.at(7)->item(row,col)->text() + " + " + courses[table[i][0]] + ".PS");
                        wholeTables.at(7)->item(row,col)->setBackground(Qt::yellow);
                    }
                    else{
                        wholeTables.at(7)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                    }
                }
                else{
                    if(wholeTables.at(semester[table[i][0]]-1)->item(row,col)){
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setText(wholeTables.at(semester[table[i][0]]-1)->item(row,col)->text() + " + " + courses[table[i][0]] + ".PS");
                        wholeTables.at(semester[table[i][0]]-1)->item(row,col)->setBackground(Qt::red);
                    }
                    else{
                        wholeTables.at(semester[table[i][0]]-1)->setItem(row,col,new QTableWidgetItem(courses[table[i][0]] + ".PS"));
                    }
                }
            }
            //qDebug() << sum << "\t" << binary_var << "\t" << index;
        }
    }
}
void MainWindow::reset_table(){
    int i,j,k=0;
    QString constantString = "4561";
    constantString ="";
    for(int i=0; i<28; i++){
        wholeTables.at(i)->clearContents();
    }
    QFile file1(":/MyFiles/collective-engineering-lessons.csv");
    if (!file1.open(QIODevice::ReadOnly)) {  //File could not be opened
         qDebug() << file1.errorString() << "collective-engineering-lessons.csv";
    }
    else{
        while (!file1.atEnd()) {
            file1.readLine();
            for(j=0; j<9;j++){
                QString line1 = file1.readLine();
                QString line2 = file1.readLine();
                for(i=2; i<7; i++){
                    if(line1.split(';').at(i) != constantString && line1.split(';').at(i) != "\r\n" && line1.split(';').at(i) != "\n"){
                        if((wholeTables.at(k+0)->item(j, i-2)))
                            wholeTables.at(k+0)->item(j, i-2)->setText(wholeTables.at(k+0)->item(j, i-2)->text() + " + " + line1.split(';').at(i));
                        else
                            wholeTables.at(k+0)->setItem(j, i-2, new QTableWidgetItem(line1.split(';').at(i)));
                        scheduling[k+0][i-2][j] = 1;
                    }
                    if( line2.split(';').at(i) != constantString && line2.split(";").at(i) != "\r\n" && line2.split(';').at(i) != "\n"){
                        if((wholeTables.at(k+0)->item(j, i-2)))
                            wholeTables.at(k+0)->item(j, i-2)->setText(wholeTables.at(k+0)->item(j, i-2)->text() + " + " + line2.split(';').at(i));
                        else
                            wholeTables.at(k+0)->setItem(j, i-2, new QTableWidgetItem(line2.split(';').at(i)));
                        scheduling[k+0][i-2][j] = 1;
                    }
                }
                for(int i=9; i<14; i++){
                    //qDebug() << line1.split(';').at(i);
                    if(line1.split(';').at(i) != constantString && line1.split(";").at(i) != "\r\n" && line1.split(';').at(i) != "\n"){
                        if(wholeTables.at(k+1)->item(j, i-9))
                            wholeTables.at(k+1)->item(j, i-9)->setText(wholeTables.at(k+1)->item(j, i-9)->text() + " + " + line1.split(';').at(i));
                        else
                            wholeTables.at(k+1)->setItem(j, i-9, new QTableWidgetItem(line1.split(';').at(i)));
                        scheduling[k+1][i-9][j] = 1;
                    }
                    if(line2.split(';').at(i) != constantString && line2.split(";").at(i) != "\r\n" && line2.split(';').at(i) != "\n"){
                        if(wholeTables.at(k+1)->item(j, i-9))
                            wholeTables.at(k+1)->item(j, i-9)->setText(wholeTables.at(k+1)->item(j, i-9)->text() + " + " + line2.split(';').at(i));
                        else
                            wholeTables.at(k+1)->setItem(j, i-9, new QTableWidgetItem(line2.split(';').at(i)));
                        scheduling[k+1][i-9][j] = 1;
                    }
                }
            }
            k+=2;
        }
    }
    file1.close();
}

/*void MainWindow::readingSemester(QString fileName, int semester)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {  //File could not be opened
         qDebug() << file.errorString();
    }
    else{
        file.readLine();
        while (!file.atEnd()) {
            QString line = file.readLine();
            //qDebug() << line.split(';').at(0);
            //qDebug() << line.split(';').at(1);
        }
    }
    file.close();
}*/

void MainWindow::on_pushButton_5_clicked()
{
    QString semester1_filename = "semester1.csv";
    QString semester2_filename = "semester2.csv";
    QString semester3_filename = "semester3.csv";
    QString semester4_filename = "semester4.csv";
    QString semester5_filename = "semester5.csv";
    QString semester6_filename = "semester6.csv";
    QString semester7_filename = "semester7.csv";
    QString semester8_filename = "semester8.csv";
    QFile semester1(semester1_filename);
    QFile semester2(semester2_filename);
    QFile semester3(semester3_filename);
    QFile semester4(semester4_filename);
    QFile semester5(semester5_filename);
    QFile semester6(semester6_filename);
    QFile semester7(semester7_filename);
    QFile semester8(semester8_filename);
    if(!semester1.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << semester1_filename << "for output";
        exit(1);
    }
    if(!semester2.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << semester2_filename << "for output";
        exit(1);
    }
    if(!semester3.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << semester3_filename << "for output";
        exit(1);
    }
    if(!semester4.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << semester4_filename << "for output";
        exit(1);
    }
    if(!semester5.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << semester5_filename << "for output";
        exit(1);
    }
    if(!semester6.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << semester6_filename << "for output";
        exit(1);
    }
    if(!semester7.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << semester7_filename << "for output";
        exit(1);
    }
    if(!semester8.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << semester8_filename << "for output";
        exit(1);
    }
    QTextStream sem1(&semester1);
    QTextStream sem2(&semester2);
    QTextStream sem3(&semester3);
    QTextStream sem4(&semester4);
    QTextStream sem5(&semester5);
    QTextStream sem6(&semester6);
    QTextStream sem7(&semester7);
    QTextStream sem8(&semester8);
    sem1 << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
    sem2 << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
    sem3 << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
    sem4 << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
    sem5 << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
    sem6 << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
    sem7 << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
    sem8 << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
    QString str = "09:00-10:00,10:00-11:00,11:00-12:00,12:00-13:00,13:00-14:00,14:00-15:00,15:00-16:00,16:00-17:00,17:00-18:00,18:00-19:00,19:00-20:00";
    QStringList list;
    list = str.split(",");
    for(int j=0;j<NHOUR;j++){
        for(int k=0; k<NDAY; k++){
            if (k == 0){
                sem1 << list.at(j) << ";";
                sem2 << list.at(j) << ";";
                sem3 << list.at(j) << ";";
                sem4 << list.at(j) << ";";
                sem5 << list.at(j) << ";";
                sem6 << list.at(j) << ";";
                sem7 << list.at(j) << ";";
                sem8 << list.at(j) << ";";
            }
            if(wholeTables.at(0)->item(j, k)){
                sem1 << wholeTables.at(0)->item(j, k)->text() << ";";
            }else {sem1 << ";";}
            if(wholeTables.at(1)->item(j, k)){
                sem2 << wholeTables.at(1)->item(j, k)->text() << ";";
            }else {sem2 << ";";}
            if(wholeTables.at(2)->item(j, k)){
                sem3 << wholeTables.at(2)->item(j, k)->text() << ";";
            }else {sem3 << ";";}
            if(wholeTables.at(3)->item(j, k)){
                sem4 << wholeTables.at(3)->item(j, k)->text() << ";";
            }else {sem4 << ";";}
            if(wholeTables.at(4)->item(j, k)){
                sem5 << wholeTables.at(4)->item(j, k)->text() << ";";
            }else {sem5 << ";";}
            if(wholeTables.at(5)->item(j, k)){
                sem6 << wholeTables.at(5)->item(j, k)->text() << ";";
            }else {sem6 << ";";}
            if(wholeTables.at(6)->item(j, k)){
                sem7 << wholeTables.at(6)->item(j, k)->text() << ";";
            }else {sem7 << ";";}
            if(wholeTables.at(7)->item(j, k)){
                sem8 << wholeTables.at(7)->item(j, k)->text() << ";";
            }else {sem8 << ";";}
        }
        sem1 << endl;
        sem2 << endl;
        sem3 << endl;
        sem4 << endl;
        sem5 << endl;
        sem6 << endl;
        sem7 << endl;
        sem8 << endl;
    }
    semester1.close();
    semester2.close();
    semester3.close();
    semester4.close();
    semester5.close();
    semester6.close();
    semester7.close();
    semester8.close();
    QMessageBox::information(this, "File creation finished", "semester files created");
}

void MainWindow::on_pushButton_2_clicked()
{
    read_labs();
    QMessageBox::information(this, "Reading lab lessons", "Reading Finished");
    write_labs();
    QMessageBox::information(this, "writing lab lessons", "Writing Finished");
}

void MainWindow::read_labs(){
    int i, j;
    for(i=0; i<NDAY; i++){
        for(j=0; j<NHOUR; j++){
            lab_scheduling[i][j] = 0;
        }
    }
/*    for(j=0;j<count_lecturer; j++){
        lecturer.at(j)->clearContents();
        ui->tabWidget->widget(13+i)->repaint();
    }
*/
    QString constantString = "4561";
    constantString ="";
    QFile file(":/MyFiles/lab_list.csv");
    if (!file.open(QIODevice::ReadOnly)) {  //File could not be opened
         qDebug() << file.errorString() << ":/MyFiles/lab_list.csv";
    }
    else{
        while (!file.atEnd()) {
            file.readLine();
            for(j=0; j<10;j++){
                QString line1 = file.readLine();
                QString line2 = file.readLine();
                //qDebug() << line1;
                //qDebug() << line2;
                for(i=2; i<7; i++){
                    if(line1.split(';').at(i) != constantString && line1.split(';').at(i) != "\n"){
                        //qDebug()<< line1.split(';').at(i);
                        lab_scheduling[i-2][j]++;
                    }
                    if( line2.split(';').at(i) != constantString && line2.split(";").at(i) != "\n"){
                        //qDebug()<< line2.split(';').at(i);
                        lab_scheduling[i-2][j]++;
                    }
                }
                for(i=9; i<14; i++){
                    if(line1.split(';').at(i) != constantString && line1.split(';').at(i) != "\n"){
                        //qDebug()<< line1.split(';').at(i);
                        lab_scheduling[i-9][j]++;
                    }
                    if( line2.split(';').at(i) != constantString && line2.split(";").at(i) != "\n"){
                        //qDebug()<< line2.split(';').at(i);
                        lab_scheduling[i-9][j]++;
                    }
                }
            }
        }
    }
    file.close();
}
void MainWindow::write_labs(){
    //Faculty Lab hours are printed simply into lab_list.in which will be read by NSGA-II
    int i, j;
    QString labs_filename = "lab_list.in";
    QFile labs_file(labs_filename);
    if(!labs_file.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << labs_filename << "for output";
        exit(1);
    }
    QTextStream lout(&labs_file);
    for(i=0; i<NHOUR; i++){
        for(j=0; j<NDAY; j++){
            lout << lab_scheduling[j][i] << " ";
        }
        lout << "\n";
    }
    labs_file.close();
}



void MainWindow::on_pushButton_4_clicked()
{
    reset_table();
    for(int i=0; i<lecturer.size(); i++){
        lecturer.at(i)->clearContents();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    //Meeting file is shown on the QTableWidget
    QFile file("/home/merve/Project/build-project-Desktop_Qt_5_5_0_GCC_64bit-Debug/Meeting.txt");
    if (!file.open(QIODevice::ReadOnly)) {  //File could not be opened
        QMessageBox::information(this, "File Error", "There is no file named Meeting.txt");
        qDebug() << file.errorString() << ":/MyFiles/lab_list.csv";
    }
    else{
        for(int i=0; i<NHOUR; i++){
            QString line = file.readLine();
            for(int j=0; j<NDAY; j++){
                //qDebug() <<line.split(' ').at(j).split('\n').at(0);
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(line.split(' ').at(j).split('\n').at(0)));
            }
        }
        QMessageBox::information(this, "Reading Finished", "Reading finished");
        file.close();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    //Meeting file is updated
    QString meeting_file_name = "Meeting.txt";
    QFile meeting_file(meeting_file_name);
    if(!meeting_file.open(QIODevice::WriteOnly)){
        qDebug() << "- Error, unable to open" << meeting_file_name << "for output";
        exit(1);
    }
    QTextStream mout(&meeting_file);
    for(int i=0; i<NHOUR; i++){
        for(int j=0; j<NDAY; j++){
            mout << ui->tableWidget->item(i, j)->text() << " ";
        }
        mout << "\n";
    }
    meeting_file.close();
    QMessageBox::information(this, "Writing Finished", "Writing finished");
}

void MainWindow::on_pushButton_8_clicked()
{
    //Lecturer Timetables will be printed
    for(int k=0; k<lecturer.size(); k++){
        qDebug() << k;
        //////
        QString file_name = lecturer_list.at(k) + ".csv";
        qDebug() << file_name;
        QFile file(file_name);
        if(!file.open(QIODevice::WriteOnly)){
            qDebug() << "- Error, unable to open" << file_name << "for output";
            exit(1);
        }
        QTextStream tout(&file);
        tout << "Time;Monday;Tuesday;Wednesday;Tuesday;Friday" << endl;
        QString str = "09:00-10:00,10:00-11:00,11:00-12:00,12:00-13:00,13:00-14:00,14:00-15:00,15:00-16:00,16:00-17:00,17:00-18:00,18:00-19:00";
        QStringList list;
        list = str.split(",");
        for(int i=0; i<NHOUR; i++){
            for(int j=0; j<NDAY; j++){
                if (j == 0){
                    tout << list.at(i) << ";";
                }
                if(lecturer.at(k)->item(i,j)){
                    tout << lecturer.at(k)->item(i,j)->text() << ";";
                }
                else{
                    tout << ";";
                }
            }
            tout << endl;
        }
        file.close();
        //////////7
    }
    QMessageBox::information(this, "Writing Finished", "All lecturer tables are printed");

}
