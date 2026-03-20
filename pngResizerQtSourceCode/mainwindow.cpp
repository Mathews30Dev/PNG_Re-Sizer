#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Main Window
    setWindowTitle("Image Re-sizer App");
    resize(800,600);
    setStyleSheet("background-color:#C08552");
    setWindowIcon(QIcon(":/icon/left-and-right-arrows.png"));

    //Load Button
    btnLoad = new QPushButton("Load Image",this);
    btnLoad->setGeometry(325,20,120,40);
    btnLoad->setStyleSheet("border: 2px solid black; background-color:#003049; color: white");
    connect(btnLoad,&QPushButton::clicked,this,&MainWindow::onLoadImage);

    //Resize Button
    btnResize = new QPushButton("Resize Image",this);
    btnResize->setGeometry(425,490,120,40);
    btnResize->setStyleSheet("border: 2px solid black; background-color:#9B0F06; color: white");
    connect(btnResize,&QPushButton::clicked,this,&MainWindow::onResizeImage);

    //Show Image Uploaded
    showImg = new QLabel(this);
    showImg->setGeometry(120,65,550,400);
    showImg->setAlignment(Qt::AlignCenter);
    showImg->setStyleSheet("border: 4px solid #3E2C23; background-color:white; color: black");
    showImg->setText("No Image loaded");
    showImg->setScaledContents(false);

    //Show Image Uploaded Size
    imgSize = new QLabel(this);
    imgSize->setGeometry(550,35,120,30);
    imgSize->setText("Size: ");
    imgSize->setStyleSheet("border: 4px solid #3E2C23;background-color: white; color:black");

    //Width and Height Input Line
    newWidth = new QLineEdit(this);
    newWidth->setGeometry(200,475,120,30);
    newWidth->setPlaceholderText("New Width");
    newWidth->setStyleSheet("border: 2px solid #5E0006; background-color:white; color: black");

    newHeight = new QLineEdit(this);
    newHeight->setGeometry(200,515,120,30);
    newHeight->setPlaceholderText("New Height");
    newHeight->setStyleSheet("border: 2px solid #5E0006; background-color:white; color: black");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoadImage()
{
    m_imagePath = QFileDialog::getOpenFileName(this,"Open Image","","Images (*.png *.jpg *.bmp)");

    if (!m_imagePath.isEmpty()) {
        // Load image into a QPixmap
        QPixmap pixmap(m_imagePath);

        //Update size text
        int width = pixmap.width();
        int heigth = pixmap.height();
        imgSize->setText("Size: " + QString::number(width) + " x " + QString::number(heigth));

        if(width > 550 || heigth > 600){
            // Scale the pixmap to fit the label while keeping aspect ratio
            QPixmap scaled = pixmap.scaled(showImg->size(), Qt::KeepAspectRatio,
            Qt::SmoothTransformation);
            showImg->setPixmap(scaled);
        }
        else{
            showImg->setPixmap(pixmap);
        }
    }
}

void MainWindow::onResizeImage()
{
    if (m_imagePath.isEmpty()) {
        QMessageBox::warning(this, "No Image", "Please load an image first.");
        return;
    }

    // Get width and height from the line edits
    bool widthOk, heightOk;
    int newWidth  = this->newWidth->text().toInt(&widthOk);
    int newHeight = this->newHeight->text().toInt(&heightOk);

    // Validate the inputs
    if (!widthOk || !heightOk || newWidth <= 0 || newHeight <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter valid width and height values.");
        return;
    }

    // Load, resize and save
    QImage image(m_imagePath);
    QImage resized = image.scaled(newWidth, newHeight,
                                  Qt::IgnoreAspectRatio,
                                  Qt::SmoothTransformation);
    QString savePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png)");

    //Update Img and size in the displayer after conversion
    if (!savePath.isEmpty()) {
        if (resized.save(savePath, "PNG")) {
            imgSize->setText("New Size: " + QString::number(newWidth) + " x " + QString::number(newHeight));

            // Update the preview with the resized image
            QPixmap preview = QPixmap::fromImage(resized);
            if(newWidth > 550 || newHeight > 600){
                preview.scaled(showImg->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                showImg->setPixmap(preview);
            }
            else{
                showImg->setPixmap(preview);
            }

        } else {
            QMessageBox::critical(this, "Error", "Failed to save image.");
        }
    }
}
