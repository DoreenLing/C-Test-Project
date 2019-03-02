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
	ui->label_edge->setStyleSheet("background-color: rgb(76,71,100)");//����label�ؼ���ɫ
    ui->textBrowser_Sex->setTextColor("color:yellow");
    ui->label_check->setStyleSheet("color:yellow");
    ui->label_model->setStyleSheet("color:yellow");
    ui->label_next->setStyleSheet("color:yellow");
    ui->label_open->setStyleSheet("color:yellow");
    ui->label_show->setStyleSheet("color:yellow");
	//���ؼ����
	cascade = cvLoadHaarClassifierCascade("D:\\OPENCV\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt_tree.xml", cvSize(30, 30));
	storage = cvCreateMemStorage(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*�Խ�����л���*/
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen pen = painter.pen();//����
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
			rgb.cols*rgb.channels(),//rgb.cols*rgb.channels()�����滻Ϊimage.step
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
		tr("Open Image"), ".", tr("Image File (*.jpg *.png *.bmp)"));//��ȡ�ļ���
	//QTextCodec *code = QTextCodec::codecForName("gb18030");
	image = cv::imread(filename.toLatin1().data());//��QString ���͵�ת��ΪString���͵�
	if (!image.data)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Image Data Is Null"));
        msgBox.exec();
	}
	else {
     //   DisplayMat(image);
		string check_filename = filename.toLatin1().data();//QStringתString
		checkFace(check_filename);
   // cv::imshow("my image test",image);
	}
	NextImage();//Ϊ��ȡ��һ��ͼƬ�ṩλ����Ϣ
}

void MainWindow::NextImage()
{
	//���²���õ��ϲ�·�������ͼ�����к�
	int len = filename.length() - 1;
	while (filename[len] != '/')
	{
		len--;
	}
	stringstream os;
	string s = filename.toStdString();
	int indeximage;//ͼƬ����
	os << s[len + 1];
	os << s[len + 2];
	os >> indeximage;//��ȡ��ǰͼƬ����

	os.str("");
	QString fileDir(len);//��ȡ·������
	for (int i = 0; i < len; i++)
	{
		fileDir[i] = filename[i];
	}

	QStringList filter;
	imgDirVideo.setPath(fileDir);
	filter << "*.jpg" << "*.bmp" << "*.jpeg" << "*.png" << "*.xpm";
	imgListVideo = imgDirVideo.entryList(filter, QDir::Files | QDir::NoSymLinks, QDir::Name);//��������·��
	indeximage_next = indeximage%imgListVideo.size();//Ϊ��һ��ͼƬ��������׼��
													 //cv::imshow("my image test", image);
}
void MainWindow::on_pushButton_NextImage_clicked()
{
	indeximage_next++;//ͼƬ����
	if (indeximage_next >= imgListVideo.size())//Ϊѭ����ʾ�ṩ����
		indeximage_next = indeximage_next%imgListVideo.size();
	QString Image_path1 = imgDirVideo.absolutePath() + QDir::separator() + imgListVideo.at(indeximage_next);//��ȡ����·��
	QString Image_path2 = QDir::toNativeSeparators(Image_path1);//��б��
	string Image_path3 = Image_path2.toLatin1().data();//QStringתString
	image = cv::imread(Image_path3);
	update();//���´���
	//DisplayMat(image);//��ʾͼƬ
	checkFace(Image_path3);

}
void MainWindow::checkFace(string Filename)
{
	//����ͼƬ
	char* imagename = (char*)Filename.data();//����ת��
	IplImage* img = cvLoadImage(imagename, 1);

	/**********��ʼ��**********/
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);

	/**********�ҶȻ�**********/
	if (img->nChannels == 3)
	{
		cvCvtColor(img, gray, CV_BGR2GRAY);//��ͼ��ҶȻ������gray�� 
	}
	else
	{
		gray = img;
	}
	cvClearMemStorage(storage);

	CvSeq* objects = cvHaarDetectObjects(gray,//�����ͼ��  
		cascade,                              //��������ʶ 
		storage,                              //�洢��⵽�ĺ�ѡ���� 
		1.2,                                  //�������μ���д�������ı��� 
		3,                                    //��Ϊ����������С����������ֵ�� 
		0,                                    //CV_HAAR_DO_CANNY_PRUNING
		cvSize(30, 30));                       //��ʼ��ⴰ�ڴ�С


											   /**********�Լ�������������������Ƚϣ�ѡȡ���е�������**********/
	int maxface_label = 0;                    //������������ǩ
	Mat max_face = Mat::zeros(objects->elem_size, 1, CV_32FC1);       //��ѡ�������
	for (int i = 0; i< objects->total; i++)
	{
		CvRect* r = (CvRect*)cvGetSeqElem(objects, i);
		max_face.at<float>(i, 0) = (float)(r->height * r->width);
		if (i > 0 && max_face.at<float>(i, 0) > max_face.at<float>(i - 1, 0))
		{
			maxface_label = i;
		}

	}
	/**********���Ƽ����**********/
	if (objects->total > 0)                    //����������ɹ�
	{
		CvRect* rect = (CvRect*)cvGetSeqElem(objects, maxface_label);
		cvRectangle(img, cvPoint(rect->x, rect->y),
			cvPoint(rect->x + rect->width, rect->y + rect->height), cvScalar(100.100, 0), 3, 3);

		/**********�ָ��������� Ϊ�Ա�����׼��**********/
		cvSetImageROI(img, *rect);                //����ͼ����������ROI����
		faceImage = cvCreateImage(cvSize(rect->width, rect->width), IPL_DEPTH_8U, 1);
		if (img->nChannels = 3)
		{
  			cvCvtColor(img, faceImage, CV_BGR2GRAY);//��ͼ��ҶȻ������ faceImage�� 
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
	/**********��ͼ��ؼ�����ʾͼ��**********/
	cv::Mat myimg;
	myimg = cvarrToMat(img,true);//��IplImage*ת��Ϊmat��
	//imshow("img_1", myimg);
//	cvShowImage("result", img);
	DisplayMat(myimg);//��ʾͼƬ
	cvReleaseImage(&gray);//�ͷŻҶ�ͼƬ
}
void MainWindow::checkSex(IplImage* image)
{
	if (flag_load != "No") {
		cv::Mat img = cvarrToMat(image, true);//��IplImage*ת��Ϊmat��
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
//���ط�����
void MainWindow::on_comboBox_checkSex_activated(const QString &arg1)
{
	if (arg1 == "PCA") {
		modelPCA = EigenFaceRecognizer::create();
		modelPCA->load<EigenFaceRecognizer>("PCA_Model1.xml");//���ط�����
		modelPCA->read("PCA_Model1.xml");//��ȡ��������ʹ��load���������һ��
		flag_load = "PCA";//���������ر�־
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
