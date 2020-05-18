#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QRect>
#include <vector>
#include <QPixmap>
#include <list>

#include "Ship.h"

using namespace std;

class GameManager;
class Ship;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void _hideSelectPane();

    void _initSelectPane();
    

    ~MainWindow();

public:
    GameManager* _gm = nullptr;

protected:
    void paintEvent(QPaintEvent *event);

    void _displayNotStart();
    void _displayP1Choice();
    void _displayP2Choice();
    void _displayWaitP1Play();
    void _displayWaitP2Play();
    void _displayP1Play();
    void _displayP2Play();
    void _displayGameOver();

    void _displayMap();
    void _displayP1Ships();
    void _displayP2Ships();

    void _displayHistoryAttacks();
    void _displayCurP1Attack();
    void _displayCurP2Attach();


    void _initP1P2Rects();

    void _p1Attack(int row, int col);
    void _p2Attack(int row, int col);

    bool _canP1Attack(int row, int col);
    bool _canP2Attack(int row, int col);

    bool _isGameOver();

    bool _isP1Win();
    bool _isP2Win();

    bool _isP1ShipDestroy(Ship* ship);
    bool _isP2ShipDestroy(Ship* ship);

private slots:
    void on_btnAction_clicked();

    void fireEffectTimer();

private:
    Ui::MainWindow *ui;

    QVector<QRectF> _p1Rects;
    QVector<QRectF> _p2Rects;

    list<QPoint> _p1Attacks;
    list<QPoint> _p2Attacks;

    vector<QPixmap*> _p1ShipImages;
    vector<QPixmap*> _p2ShiImages;

    QPixmap* _historyDestoryImage;
    QPixmap* _curDestoryImage;
    QPixmap* _waveImage;

    int _xCells = 10;
    int _yCells = 10;
    int _topPane = 100;
    int _leftPane = 50;
    int _bottomPane = 50;
    int cellW;// = (w - _leftPane) / (2 * _xCells);
    int cellH;


    ShipType _curaddShipType = Ship1;
};
#endif // MAINWINDOW_H
