#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QPixmap>
#include <QVector>
#include <QLineF>
#include <QString>
#include <QTimer>

#include <algorithm>

#include "gamemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _gm = new GameManager();

    for (int i = 1; i <= 5; ++i)
    {
        QPixmap* p = new QPixmap();
        p->load(":/res/chuan" + QString::number(i) +  ".png");
        _p1ShipImages.push_back(p);
    }

    for (int i = 1; i <= 5; ++i)
    {
        QPixmap* p = new QPixmap();
        p->load(":/res/chuanshu" + QString::number(i) + ".png");
        _p2ShiImages.push_back(p);
    }

   

    _curDestoryImage = new QPixmap();
    _curDestoryImage->load(":/res/fire.png");

    _historyDestoryImage = new QPixmap();
    _historyDestoryImage->load(":/res/fire2.png");

    _waveImage = new QPixmap();
    _waveImage->load(":/res/wave.png");

    ui->setupUi(this);

    for (int t = 0; t < 10; ++t)
    {
        ui->comboBoxRow->addItem(QString::number(t));
        ui->comboBoxCol->addItem(QString::number(t));
    }

    ui->comboBoxDirect->addItem(QString("Horizontal"));
    ui->comboBoxDirect->addItem(QString("Vertical"));

    _hideSelectPane();

}

void MainWindow::_hideSelectPane()
{
    ui->labelRow->setVisible(false);
    ui->labelCol->setVisible(false);

    ui->comboBoxRow->setVisible(false);
    ui->comboBoxCol->setVisible(false);
    ui->comboBoxDirect->setVisible(false);
}

void MainWindow::_initSelectPane()
{
    /*ui->comboBoxRow->clear();
    ui->comboBoxCol->clear();*/

    ui->labelRow->setText("row");
    ui->labelCol->setText("col");

    ui->labelRow->setVisible(true);
    ui->labelCol->setVisible(true);

    ui->comboBoxRow->setVisible(true);
    ui->comboBoxCol->setVisible(true);
    ui->comboBoxDirect->setVisible(true);
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    int w = width();
    int h = height();
    cellW = (w - _leftPane) / (2 * _xCells);
    cellH = (h - _topPane - _bottomPane) / _yCells;

//    qDebug() << "hello.world";
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::blue);

    switch (_gm->_status)
    {
    case NotStarted:
    {
        _displayNotStart();
    }break;
    case P1Place:
    {
        _displayP1Choice();
    }break;
    case P2Place:
    {
        _displayP2Choice();
    }break;
    case WaitP1Attack:
    {
        _displayWaitP1Play();
    }break;
    case P1Attack:
    {
        _displayP1Play();
        QTimer::singleShot(2000, this, &MainWindow::fireEffectTimer);
    }break;
    case P1AttackFinish:
    {
        _displayWaitP2Play();
        _gm->_status = WaitP2Attack;
    }break;
    case WaitP2Attack:
    {
        _displayWaitP2Play();
        QTimer::singleShot(2000, this, &MainWindow::fireEffectTimer);
    }break;
    case P2AttachFinish:
    {
        _displayWaitP1Play();
        _gm->_status = WaitP1Attack;
    }break;
    case P2Attack:
    {
        _displayP2Play();
        QTimer::singleShot(2000, this, &MainWindow::fireEffectTimer);
    }break;
    case Overed:
    {
        _displayGameOver();
    }break;
    default:
        break;
    }
}

void MainWindow::_displayNotStart()
{
    ui->labelStatus->setText("not started");
    _displayMap();
}

void MainWindow::_displayP1Choice()
{
    ui->labelStatus->setText("red choice ship pos");
    ui->btnAction->setText("choice");
    _displayMap();
    _displayP1Ships();
}

void MainWindow::_displayP2Choice()
{
    ui->labelStatus->setText("blue choice ship pos");
    ui->btnAction->setText("choice");
    _displayMap();
    _displayP2Ships();
}

void MainWindow::_displayWaitP1Play()
{
    ui->labelStatus->setText("wait red attack");
    _displayMap();
    _displayP1Ships();
    _displayHistoryAttacks();
}

void MainWindow::_displayWaitP2Play()
{
    ui->labelStatus->setText("wait blue attack");
    _displayMap();
    _displayP2Ships();
    _displayHistoryAttacks();
}

void MainWindow::_displayP1Play()
{
    _displayMap();
    _displayP1Ships();
    _displayHistoryAttacks();
    _displayCurP1Attack();
}

void MainWindow::_displayP2Play()
{
    _displayMap();
    _displayP2Ships();
    _displayHistoryAttacks();
    _displayCurP2Attach();
}

void MainWindow::_displayGameOver()
{
    _displayMap();
    _displayP1Ships();
    _displayP2Ships();

    _displayHistoryAttacks();
    if (_isP1Win())
    {
        ui->labelStatus->setText(QString::fromStdString("p1 win,score:" + to_string(_p1Attacks.size())));
    }
    else
    {
        ui->labelStatus->setText(QString::fromStdString("p2 win,score:" + to_string(_p2Attacks.size())));
    }
    ui->btnAction->setText("again");
}

void MainWindow::_displayMap()
{

    _initP1P2Rects();
    QPainter painter(this);

    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine));
    painter.drawRects(_p1Rects);

    for (int i = 0; i < 10; ++i)
    {
        painter.drawText(15, i*_p1Rects.begin()->height() + _topPane + 25, QString::number(i));
        painter.drawText(i*_p1Rects.begin()->width() + _leftPane + 25, height() - 30, QString::number(i));
        painter.drawText((i+10)*_p1Rects.begin()->width() + _leftPane + 25, height() - 30, QString::number(i));
    }

    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine));
    painter.drawRects(_p2Rects);

    
}

void MainWindow::_displayP1Ships()
{
    QPainter painter(this);

    int imgIndex = 0;
    for (auto it = _gm->_p1._ships.begin(); it != _gm->_p1._ships.end(); ++it)
    {
        int index = (*it)->_position.x() + 10 * ((*it)->_position.y());

        auto FirstPos = _p1Rects.at(index);
        int multipy = (int)((*it)->_type);
        switch ((*it)->_direct)
        {
        case Horizontal:
        {
            FirstPos.setWidth(FirstPos.width()*multipy);
            painter.drawPixmap(FirstPos, *_p1ShipImages[imgIndex], _p1ShipImages[imgIndex]->rect());

        }break;
        case Vertical:
        {
            FirstPos.setHeight(FirstPos.height()*multipy);
            painter.drawPixmap(FirstPos, *_p2ShiImages[imgIndex], _p2ShiImages[imgIndex]->rect());
        }break;
        default:
            break;
        }

        //painter.drawPixmap(FirstPos, *_p1ShipImages[imgIndex], _p1ShipImages[imgIndex]->rect());
        ++imgIndex;
    }
   
}

void MainWindow::_displayP2Ships()
{
    QPainter painter(this);
    int imgIndex = 0;
    for (auto it = _gm->_p2._ships.begin(); it != _gm->_p2._ships.end(); ++it)
    {
        int index = (*it)->_position.x() + 10 * ((*it)->_position.y());

        auto FirstPos = _p2Rects.at(index);
        int multipy = (int)((*it)->_type);
        switch ((*it)->_direct)
        {
        case Horizontal:
        {
            FirstPos.setWidth(FirstPos.width()*multipy);
            painter.drawPixmap(FirstPos, *_p1ShipImages[imgIndex], _p1ShipImages[imgIndex]->rect());

        }break;
        case Vertical:
        {
            FirstPos.setHeight(FirstPos.height()*multipy);
            painter.drawPixmap(FirstPos, *_p2ShiImages[imgIndex], _p2ShiImages[imgIndex]->rect());
        }break;
        default:
            break;
        }

       // painter.drawPixmap(FirstPos, *_p1ShipImages[imgIndex], _p1ShipImages[imgIndex]->rect());
        /*int index = (*it)->_position.x() + 10 * ((*it)->_position.y());
        painter.drawPixmap(_p2Rects.at(index), *_p2ShiImages[imgIndex], _p2ShiImages[imgIndex]->rect());*/
        ++imgIndex;
    }
}

void MainWindow::_displayHistoryAttacks()
{
    auto p1s = _gm->_p1._getShipPositons();
    auto p2s = _gm->_p2._getShipPositons();
    QPainter painter(this);
    for (auto it = _p1Attacks.begin(); it != _p1Attacks.end(); ++it)
    {
        int index = it->y() * 10 + it->x();

        auto p2d = std::find(p2s.begin(), p2s.end(), *it);
        if (p2d!=p2s.end())
        {
            painter.drawPixmap(_p2Rects.at(index), *_historyDestoryImage, _historyDestoryImage->rect());
        }
        else
        {
            painter.drawPixmap(_p2Rects.at(index), *_waveImage, _waveImage->rect());
        }
    }
    for (auto it = _p2Attacks.begin(); it != _p2Attacks.end(); ++it)
    {
        int index = it->y() * 10 + it->x();
        auto p1d = std::find(p1s.begin(), p1s.end(), *it);
        if (p1d != p1s.end())
        {
            painter.drawPixmap(_p1Rects.at(index), *_historyDestoryImage, _historyDestoryImage->rect());
        }
        else
        {
            painter.drawPixmap(_p1Rects.at(index), *_waveImage, _waveImage->rect());
        }
    }
}

void MainWindow::_displayCurP1Attack()
{
    QPainter painter(this);
    if (_p1Attacks.empty()) { return; }
    int index = _p1Attacks.rbegin()->y() + _p1Attacks.rbegin()->x();
    painter.drawPixmap(_p2Rects.at(index), *_curDestoryImage, _curDestoryImage->rect());
}

void MainWindow::_displayCurP2Attach()
{
    QPainter painter(this);
    if (_p2Attacks.empty()) { return; }
    int index = _p2Attacks.rbegin()->y() * 10 + _p2Attacks.rbegin()->x();
    painter.drawPixmap(_p1Rects.at(index), *_curDestoryImage, _curDestoryImage->rect());
}

void MainWindow::_initP1P2Rects()
{
    _p1Rects.clear();
    _p2Rects.clear();
 
    //align left map
    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 10; ++col)
        {
            _p1Rects.append(QRectF(col*cellW+_leftPane, row*cellH + _topPane, cellW, cellH));
        }
    }
    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 10; ++col)
        {
            _p2Rects.append(QRectF((col+10)*cellW+_leftPane, row*cellH + _topPane, cellW, cellH));
        }
    }
}

void MainWindow::_p1Attack(int row, int col)
{
    _p1Attacks.push_back(QPoint(col, row));
}

void MainWindow::_p2Attack(int row, int col)
{
    _p2Attacks.push_back(QPoint(col, row));
}

bool MainWindow::_canP1Attack(int row, int col)
{
    for (auto it = _p1Attacks.begin(); it != _p1Attacks.end(); ++it)
    {
        if (it->x() == col && it->y() == row) { return false; }
    }
    return true;
}

bool MainWindow::_canP2Attack(int row, int col)
{
    for (auto it = _p2Attacks.begin(); it != _p2Attacks.end(); ++it)
    {
        if (it->x() == col && it->y() == row) { return false; }
    }
    return true;
}

bool MainWindow::_isGameOver()
{
    if (_isP1Win() || _isP2Win())
    {
        return true;
    }
    return false;
}

bool MainWindow::_isP1Win()
{
    bool bret = true;
    for (auto it = _gm->_p2._ships.begin(); it != _gm->_p2._ships.end(); ++it)
    {
        bret = _isP2ShipDestroy(*it);
        if (!bret) { return bret; }
    }
    return bret;
}

bool MainWindow::_isP2Win()
{
    bool bret = true;
    for (auto it = _gm->_p1._ships.begin(); it != _gm->_p1._ships.end(); ++it)
    {
        bret = _isP1ShipDestroy(*it);
        if (!bret) { return bret; }
    }
    return bret;
}

bool MainWindow::_isP1ShipDestroy(Ship* ship)
{
    auto shipPoss = Ship::sGetShipPostions(ship->_position, ship->_type, ship->_direct);
    for (auto it = shipPoss.begin(); it != shipPoss.end(); ++it)
    {
        auto ff = std::find_if(_p2Attacks.begin(), _p2Attacks.end(), [it](QPoint pt)->bool {
            if (pt.x() == it->x() && pt.y() == it->y())
            {
                return true;
            }
            else
            {
                return false;
            }
            });
        if (ff == _p2Attacks.end())
        {
            return false;
        }
    }
    /*for (auto it = _p1Attacks.begin(); it != _p1Attacks.end(); ++it)
    {
        if (ship->_position.x() == it->x() && ship->_position.y() == it->y())
        {
            return true;
        }
    }*/
    return true;
    /*for (auto it = _p2Attacks.begin(); it != _p2Attacks.end(); ++it)
    {
        if (ship->_position.x() == it->x() && ship->_position.y() == it->y())
        {
            return true;
        }
    }
    return false;*/
}

bool MainWindow::_isP2ShipDestroy(Ship* ship)
{
    auto shipPoss = Ship::sGetShipPostions(ship->_position, ship->_type, ship->_direct);
    for (auto it = shipPoss.begin(); it != shipPoss.end(); ++it)
    {
        auto ff = std::find_if(_p1Attacks.begin(), _p1Attacks.end(), [it](QPoint pt)->bool {
            if (pt.x() == it->x() && pt.y() == it->y())
            {
                return true;
            }
            else
            {
                return false;
            }
            });
        if (ff == _p1Attacks.end())
        {
            return false;
        }
    }
    /*for (auto it = _p1Attacks.begin(); it != _p1Attacks.end(); ++it)
    {
        if (ship->_position.x() == it->x() && ship->_position.y() == it->y())
        {
            return true;
        }
    }*/
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
    for (auto it = _p1ShipImages.begin(); it != _p1ShipImages.end(); ++it)
    {
        delete *it;
    }
    for (auto it = _p2ShiImages.begin(); it != _p2ShiImages.end(); ++it)
    {
        delete *it;
    }
    _p1ShipImages.clear();
    _p2ShiImages.clear();

    if (_curDestoryImage)
    {
        delete _curDestoryImage;
    }
    if (_historyDestoryImage)
    {
        delete _historyDestoryImage;
    }

    if (_waveImage)
    {
        delete _waveImage;
    }

    _curDestoryImage = nullptr;
    _historyDestoryImage = nullptr;
    _waveImage = nullptr;
}


void MainWindow::on_btnAction_clicked()
{
    switch (_gm->_status)
    {
    case NotStarted:
    case Overed:
    {
        _initSelectPane();
        _gm->_status = P1Place;
    }break;
    case P1Place:
    {
        int row = ui->comboBoxRow->currentIndex();
        int col = ui->comboBoxCol->currentIndex();
        ShipDirect direct = (ShipDirect)(ui->comboBoxDirect->currentIndex());
        auto addshipPoss = Ship::sGetShipPostions(QPoint(col, row), _curaddShipType, direct);
        if (!_gm->_p1._canAddShip(addshipPoss))
        {
            qDebug() << "cannot add ship at this position";
            return;
        }
        _gm->_p1.addShip(ui->comboBoxRow->currentIndex(), ui->comboBoxCol->currentIndex(), _curaddShipType, direct);
        if (_gm->_p1._ships.size() == _gm->shipCount)
        {
            _gm->_status = P2Place;
            _curaddShipType = Ship1;
        }
        else
        {
            int cc = (int)(_curaddShipType);
            ++cc;
            _curaddShipType = (ShipType)cc;
        }
    }break;
    case P2Place:
    {
        int row = ui->comboBoxRow->currentIndex();
        int col = ui->comboBoxCol->currentIndex();
        ShipDirect direct = (ShipDirect)(ui->comboBoxDirect->currentIndex());
        auto addshipPoss = Ship::sGetShipPostions(QPoint(col, row), _curaddShipType, direct);
        if (!_gm->_p2._canAddShip(addshipPoss))
        {
            qDebug() << "cannot add ship at this position";
            return;
        }
        _gm->_p2.addShip(ui->comboBoxRow->currentIndex(), ui->comboBoxCol->currentIndex(), _curaddShipType, direct);
        
        if (_gm->_p2._ships.size() == _gm->shipCount)
        {
            _gm->_status = WaitP1Attack;
        }
        else
        {
            int cc = (int)(_curaddShipType);
            ++cc;
            _curaddShipType = (ShipType)cc;
        }
    }break;
    case WaitP1Attack:
    {
        if (!_canP1Attack(ui->comboBoxRow->currentIndex(), ui->comboBoxCol->currentIndex()))
        {
            return;
        }
        _p1Attack(ui->comboBoxRow->currentIndex(), ui->comboBoxCol->currentIndex());
        _gm->_status = P1Attack;
    }break;
    case WaitP2Attack:
    {
        if (!_canP2Attack(ui->comboBoxRow->currentIndex(), ui->comboBoxCol->currentIndex()))
        {
            return;
        }
        _p2Attack(ui->comboBoxRow->currentIndex(), ui->comboBoxCol->currentIndex());
        _gm->_status = P2Attack;
    }break;
    default:
        break;
    }
    update();
}

void MainWindow::fireEffectTimer()
{
    if (_gm->_status == P1Attack)
    {
        _gm->_status = P1AttackFinish;
    }
    else if (_gm->_status == P2Attack)
    {
        _gm->_status = P2AttachFinish;
    }
    if (_isGameOver())
    {
        _gm->_status = Overed;
    }
    update();
}
