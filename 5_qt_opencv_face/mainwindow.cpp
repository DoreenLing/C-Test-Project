#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(660,660);
    this->setAutoFillBackground(true);
    QPalette palette;
	palette.setColor(QPalette::Background,QColor("#B1723C"));
    this->setPalette(palette);
    setMouseTracking(true);

    ui->pushButton_Openfile->setStyleSheet("background_color:rgb(0,255,100)");
	ui->pushButton_Openfile->setStyleSheet("color:red");
	ui->label_edge->setStyleSheet("background-color: rgb(76,71,100)");//设置label控件颜色
    ui->textBrowser_Sex->setTextColor("color:yellow");
    ui->label_check->setStyleSheet("color:yellow");
    ui->label_model->setStyleSheet("color:yellow");
    ui->label_next->setStyleSheet("color:yellow");
    ui->label_open->setStyleSheet("color:yellow");
    ui->label_show->setStyleSheet("color:yellow");
	//加载检测器
	cascade = cvLoadHaarClassifierCascade("D:\\OPENCV\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt_tree.xml", cvSize(30, 30));
	storage = cvCreateMemStorage(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*对界面进行绘制*/
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen = painter.pen();//画笔
	pen.setColor(QColor("#8d5822"));
    pen.setWidth(7);
    painter.setPen(pen);

    QBrush brush;
	brush.setColor(QColor("green"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(20,40,600,600);

}
void MainWindow::DisplayMat(cv::Mat image)
{
	cv::Mat rgb;
	QImage img;
	if (image.channels() == 3)
	{
		cvtColor(image, rgb, CV_BGR2RGB);
		img = QImage((const unsigned char*)(rgb.data),
			rgb.cols, rgb.rows, 
			rgb.cols*rgb.channels(),//rgb.cols*rgb.channels()锟斤拷锟斤拷锟芥换为image.step
			QImage::Format_RGB888);
	}
	else
	{
		img = QImage((const unsigned char*)(image.data),
			image.cols, image.rows,
			rgb.cols*image.channels(),
			QImage::Format_RGB888);
	}
    ui->labelimage->setPixmap(QPixmap::fromImage(img).scaled(ui->labelimage->size()));
    ui->labelimage->resize(ui->labelimage->pixmap()->size());
	ui->labelimage->show();
}

void MainWindow::on_pushButton_Openfile_clicked()
{
	filename = QFileDialog::getOpenFileName(this,
		tr("Open Image"), ".", tr("Image File (*.jpg *.png *.bmp)"));//锟斤拷取锟侥硷拷锟斤拷
	//QTextCodec *code = QTextCodec::codecForName("gb18030");
	image = cv::imread(filename.toLatin1().data());//讲QString 类型的转化为String类型的
	if (!image.data)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Image Data Is Null"));
        msgBox.exec();
	}
	else {
     //   DisplayMat(image);
		string check_filename = filename.toLatin1().data();//QString转String
		checkFace(check_filename);
   // cv::imshow("my image test",image);
	}
	NextImage();//为获取下一张图片提供位置信息
}

void MainWindow::NextImage()
{
	//以下步骤得到上层路径并求得图像序列号
	int len = filename.length() - 1;
	while (filename[len] != '/')
	{
		len--;
	}
	stringstream os;
	string s = filename.toStdString();
	int indeximage;//图片索引
	os << s[len + 1];
	os << s[len + 2];
	os >> indeximage;//获取当前图片索引

	os.str("");
	QString fileDir(len);//获取路径长度
	for (int i = 0; i < len; i++)
	{
		fileDir[i] = filename[i];
	}

	QStringList filter;
	imgDirVideo.setPath(fileDir);
	filter << "*.jpg" << "*.bmp" << "*.jpeg" << "*.png" << "*.xpm";
	imgListVideo = imgDirVideo.entryList(filter, QDir::Files | QDir::NoSymLinks, QDir::Name);//创建完整路径
	indeximage_next = indeximage%imgListVideo.size();//为下一章图片的索引做准备
													 //cv::imshow("my image test", image);
}
void MainWindow::on_pushButton_NextImage_clicked()
{
	indeximage_next++;//图片索引
	if (indeximage_next >= imgListVideo.size())//为循环显示提供基础
		indeximage_next = indeximage_next%imgListVideo.size();
	QString Image_path1 = imgDirVideo.absolutePath() + QDir::separator() + imgListVideo.at(indeximage_next);//获取完整路径
	QString Image_path2 = QDir::toNativeSeparators(Image_path1);//反斜杠
	string Image_path3 = Image_path2.toLatin1().data();//QString转String
	image = cv::imread(Image_path3);
	update();//更新窗口
	//DisplayMat(image);//显示图片
	checkFace(Image_path3);

}
void MainWindow::checkFace(string Filename)
{
	//载入图片
	char* imagename = (char*)Filename.data();//类型转换
	IplImage* img = cvLoadImage(imagename, 1);

	/**********初始化**********/
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);

	/**********灰度化**********/
	if (img->nChannels == 3)
	{
		cvCvtColor(img, gray, CV_BGR2GRAY);//将图像灰度化存放在gray中 
	}
	else
	{
		gray = img;
	}
	cvClearMemStorage(storage);

	CvSeq* objects = cvHaarDetectObjects(gray,//待检测图像  
		cascade,                              //分类器标识 
		storage,                              //存储检测到的候选矩形 
		1.2,                                  //相邻两次检测中窗口扩大的比例 
		3,                                    //认为是人脸的最小矩形数（阈值） 
		0,                                    //CV_HAAR_DO_CANNY_PRUNING
		cvSize(30, 30));                       //初始检测窗口大小


											   /**********对检测出的人脸区域面积做比较，选取其中的最大矩形**********/
	int maxface_label = 0;                    //最大面积人脸标签
	Mat max_face = Mat::zeros(objects->elem_size, 1, CV_32FC1);       //候选矩形面积
	for (int i = 0; i< objects->total; i++)
	{
		CvRect* r = (CvRect*)cvGetSeqElem(objects, i);
		max_face.at<float>(i, 0) = (float)(r->height * r->width);
		if (i > 0 && max_face.at<float>(i, 0) > max_face.at<float>(i - 1, 0))
		{
			maxface_label = i;
		}

	}
	/**********绘制检测结果**********/
	if (objects->total > 0)                    //如果人脸检测成功
	{
		CvRect* rect = (CvRect*)cvGetSeqElem(objects, maxface_label);
		cvRectangle(img, cvPoint(rect->x, rect->y),
			cvPoint(rect->x + rect->width, rect->y + rect->height), cvScalar(100.100, 0), 3, 3);

		/**********分割人脸区域 为性别检测做准备**********/
		cvSetImageROI(img, *rect);                //设置图像人脸部分ROI区域
		faceImage = cvCreateImage(cvSize(rect->width, rect->width), IPL_DEPTH_8U, 1);
		if (img->nChannels = 3)
		{
  			cvCvtColor(img, faceImage, CV_BGR2GRAY);//将图像灰度化存放在 faceImage中 
		}
		else
		{
			faceImage = img;
		}
		cvResetImageROI(img);
	}

	else
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Sorry ,It isn't a people face!!!"));
		msgBox.exec();
	}
	/**********在图像控件上显示图像**********/
	cv::Mat myimg;
	myimg = cvarrToMat(img,true);//将IplImage*转化为mat型
	//imshow("img_1", myimg);
//	cvShowImage("result", img);
	DisplayMat(myimg);//显示图片
	cvReleaseImage(&gray);//释放灰度图片
}
void MainWindow::checkSex(IplImage* image)
{
	if (flag_load != "No") {
		cv::Mat img = cvarrToMat(image, true);//将IplImage*转化为mat型
		if(flag_load == "PCA") {
			int modelPCA1 = modelPCA->predict(img);
		}
		if (flag_load == "LBP") {
			int modelLBP1 = modelLBP->predict(img);
            if(modelLBP1 == 1)
                ui->textBrowser_Sex->setText("Man");
            else if(modelLBP1 == 2)
                ui->textBrowser_Sex->setText("Woman");
            else ui->textBrowser_Sex->setText("Error");
			}
		if (flag_load == "Fisher") {
			int modelFisher1 = modelFisher->predict(img);
		}
	}
}
void MainWindow::on_pushButton_checkSex_clicked()
{
	checkSex(faceImage);
}
//加载分类器
void MainWindow::on_comboBox_checkSex_activated(const QString &arg1)
{
	if (arg1 == "PCA") {
		modelPCA = EigenFaceRecognizer::create();
		modelPCA->load<EigenFaceRecognizer>("PCA_Model1.xml");//加载分类器
		modelPCA->read("PCA_Model1.xml");//读取分类器，使用load必须加上这一句
		flag_load = "PCA";//分类器加载标志
	}
	else if (arg1 == "LBP") {
		modelLBP = LBPHFaceRecognizer::create();
		modelLBP->load<LBPHFaceRecognizer>("LBP_Model1.xml");
		modelLBP->read("LBP_Model1.xml");
		flag_load = "LBP";
	}
	else if (arg1 == "Fisher") {
		modelFisher = FisherFaceRecognizer::create();
		modelFisher->load<FisherFaceRecognizer>("Fisher_Model1.xml");
		modelFisher->read("Fisher_Model1.xml");
		flag_load = "Fisher";
	}
	else flag_load = "No";
}
