#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QPixmap>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onLoadImage();
    void onResizeImage();
private:
    Ui::MainWindow *ui;
    QString m_imagePath;
    QPushButton* btnLoad;
    QPushButton* btnResize;
    QLabel* showImg;
    QLabel* imgSize;
    QLineEdit* newWidth;
    QLineEdit* newHeight;


};
#endif // MAINWINDOW_H
