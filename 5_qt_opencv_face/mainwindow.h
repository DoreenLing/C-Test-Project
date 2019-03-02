#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QTextCodec>
#include <QMessageBox>
#include <QPainter>
#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
//#include <opencv2/objdetect/objdetect.hpp>
//#include "opencv2/xfeatures2d.hpp"
#include "opencv2/face.hpp"
#include <QDebug>
//#include <string>
#include <sstream>
#include <fstream>
#include<iostream>

using namespace std;
using namespace cv;
using namespace cv::face;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
	void checkFace(string Filename);
	void NextImage();
	void DisplayMat(cv::Mat image);
	void checkSex(IplImage* image);
private slots:
    void on_pushButton_Openfile_clicked();
    void on_pushButton_NextImage_clicked();
    void on_pushButton_checkSex_clicked();

    //void on_comboBox_activated(const QString &arg1);

    void on_comboBox_checkSex_activated(const QString &arg1);

  //  void on_textBrowser_Sex_anchorClicked(const QUrl &arg1);

private:
    Ui::MainWindow *ui;
    cv::Mat image;
	QString filename;//�ļ�·��
	string Image_path1;//ת������·��
	QDir imgDirVideo;
	QStringList imgListVideo;
	int indeximage_next;
	//���ؼ�����
	CvHaarClassifierCascade* cascade;
	CvMemStorage* storage;
	//������
	Ptr< EigenFaceRecognizer> modelPCA;
	Ptr<FaceRecognizer> modelFisher;
	Ptr< LBPHFaceRecognizer> modelLBP ;
	string flag_load = "No";//���ط�������־
	IplImage* faceImage;//����
};

#endif // MAINWINDOW_H
