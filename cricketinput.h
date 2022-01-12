#ifndef CRICKETINPUT_H
#define CRICKETINPUT_H

#include <QDialog>
#include <QGraphicsView>
#include "dartboardsegment.h"
#include <QLCDNumber>
#include "undobutton.h"
#include "submitbutton.h"
#include <QLabel>
#include <QGraphicsSvgItem>
#include <QSoundEffect>

class CricketMainWindow;
class cricketclass;

namespace Ui {
class cricketinput;
}


class cricketinput : public QDialog
{
    Q_OBJECT
public:
    void setScore(int value, QChar type);
    void computeScore();
    bool areSlotsFull();
public slots:
    void signalSegmentPressed(int &value, QChar &type);
signals:
    void signalSubmitButtonPressed2(int &numberofdarts, QVector<QString> darts);
    void signalSetLabelSlot(int hits, int slot);
public:
    cricketinput(QWidget *parent = nullptr, int sets = 1, int legs = 1, cricketclass* player = nullptr, CricketMainWindow* gamewindow = nullptr, bool cutthroat = false);
    ~cricketinput();
private slots:
    void on_submitButton_clicked();
    void on_undoButton_clicked();

private:
    Ui::cricketinput *ui;
    QGraphicsView* view;
    QGraphicsScene *mscene;
    QGraphicsSvgItem *labels;
    int Sets, Legs, Counter;
    bool Stop;
    QLCDNumber *scoreDart1;
    QLCDNumber *scoreDart2;
    QLCDNumber *scoreDart3;
    UndoButton *undoButton;
    SubmitButton *submitButton;
    QVector<QString> Dart{"","",""};
    cricketclass* Player;
    CricketMainWindow* mGameWindow;
    int mSlot15, mSlot16, mSlot17, mSlot18, mSlot19, mSlot20, mSlot25;
    int mExtra15, mExtra16, mExtra17, mExtra18, mExtra19, mExtra20, mExtra25;
    int mScore;
    bool mCutThroat;
    QVector<int> mExtra15s, mExtra16s, mExtra17s, mExtra18s, mExtra19s, mExtra20s, mExtra25s;
    QVector<int> mSlot15Array, mSlot16Array, mSlot17Array, mSlot18Array, mSlot19Array, mSlot20Array, mSlot25Array;
    QVector<int> mExtra15Array, mExtra16Array, mExtra17Array, mExtra18Array, mExtra19Array, mExtra20Array, mExtra25Array;
    QVector<QVector<int>> mExtra15sArray, mExtra16sArray, mExtra17sArray, mExtra18sArray, mExtra19sArray, mExtra20sArray, mExtra25sArray;
    QSoundEffect gameshotsound;
};

#endif // CRICKETINPUT_H
