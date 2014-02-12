#include <QtWidgets>
#include <QtNetwork>

#include "httpwindow.h"

HttpWindow::HttpWindow(QWidget *parent)
    : QDialog(parent)
{
#ifndef QT_NO_SSL
    urlLineEdit = new QLineEdit("http://www.chi-square.org");
#else
    urlLineEdit = new QLineEdit("http://www.chi-square.org");
#endif


    urlLabel = new QLabel(tr("&URL:"));
    urlLabel->setBuddy(urlLineEdit);

    //downloading status text/progress bar
    statusLabel = new QLabel(tr(""));
    statusLabel->setWordWrap(true);
    progressBar = new QProgressBar(this);
    progressBar->hide();

    //body of text on left
    introBody = new QLabel(tr("Welcome to Chi-Square! The Linux distro for data scientists. Chi-Square is built off of Lubuntu, a lightweight Ubuntu Distribution.  \n\nSelect the data sets on the right you would like to download and have automaticaly set up into your programs. \n\nFor even more datasets right click and copy the link below to paste into your browser."));
    introBody->setWordWrap(true);
    introBody->setFixedWidth(200);
    webLink = new QLabel();
    webLink->setText("<a href=\"chi-square.org\">chi-square.org/datasets</a>");
    webLink->setFixedWidth(200);
    webLink->setFixedHeight(25);

    //scrollArea = new QAbstractScrollArea();
    //scrollArea->setFixedWidth(500);

    //bottom right buttons
    downloadButton = new QPushButton(tr("Download"));
    downloadButton->setDefault(true);
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);
    cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setDefault(false);
    cancelButton->setEnabled(false);
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(downloadButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::DestructiveRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    //autostart checkbox
    checkBox = new QCheckBox;
    checkBox->setText("Show on boot");
    checkBox->setFocusPolicy(Qt::NoFocus);
    checkBox->setChecked(false);


    //*****************************************************************************************************************************
    //  CREATE OBJECTS FOR ACCORDIAN MENU
    //*****************************************************************************************************************************
    statButton = new QPushButton(tr("Statistical")); statButton->setFocusPolicy(Qt::NoFocus); statButton->setStyleSheet("Text-align: left; padding-left: 5px; padding-top: 3px; padding-bottom: 3px;");
    statBox1 = new QCheckBox(tr("Ministerial Expenditures by Standard Object - Volume 2, Table 3")); statBox1->setFocusPolicy(Qt::NoFocus); statBox1->setToolTip("Free for non-commercial use.");
    statBox2 = new QCheckBox(tr("Ten Year Comparative Financial Information - Volume 1")); statBox2->setFocusPolicy(Qt::NoFocus); statBox2->setToolTip("Free for non-commercial use.");
    statBox3 = new QCheckBox(tr("Statistical Report on International Assistance - by Country Spending 2009-2010 ")); statBox3->setFocusPolicy(Qt::NoFocus); statBox3->setToolTip("Free for non-commercial use.");
    statBox4 = new QCheckBox(tr("Statistical Report on International Assistance - by Country Spending 2004-2005")); statBox4->setFocusPolicy(Qt::NoFocus); statBox4->setToolTip("Free for non-commercial use.");

    textButton = new QPushButton(tr("Text")); textButton->setFocusPolicy(Qt::NoFocus); textButton->setStyleSheet("Text-align: left; padding-left: 5px; padding-top: 3px; padding-bottom: 3px;");
    textBox1 = new QCheckBox(tr("Twitter Sentiment Corpus")); textBox1->hide(); textBox1->setFocusPolicy(Qt::NoFocus);textBox1->setToolTip("Free for non-commercial use.");
    textBox2 = new QCheckBox(tr("Sentiment Analysis")); textBox2->hide(); textBox2->setFocusPolicy(Qt::NoFocus); textBox2->setToolTip("Free for non-commercial use.");
    textBox3 = new QCheckBox(tr("Slashdot Zoo signed social network of users")); textBox3->hide(); textBox3->setFocusPolicy(Qt::NoFocus); textBox3->setToolTip("Free for non-commercial use.");
    textBox4 = new QCheckBox(tr("Newswire FSD Corpus")); textBox4->hide(); textBox4->setFocusPolicy(Qt::NoFocus); textBox4->setToolTip("Free for non-commercial use.");

    imageButton = new QPushButton(tr("Image")); imageButton->setFocusPolicy(Qt::NoFocus); imageButton->setStyleSheet("Text-align: left; padding-left: 5px; padding-top: 3px; padding-bottom: 3px;");
    imageBox1 = new QCheckBox(tr("Labeled Faces in the Wild Home")); imageBox1->hide(); imageBox1->setFocusPolicy(Qt::NoFocus); imageBox1->setToolTip("Free for non-commercial use.");
    imageBox2 = new QCheckBox(tr("The Database of Faces (formerly 'The ORL Database of Faces')")); imageBox2->hide(); imageBox2->setFocusPolicy(Qt::NoFocus); imageBox2->setToolTip("Free for non-commercial use.");
    imageBox3 = new QCheckBox(tr("Collection of Facial Images: Grimace")); imageBox3->hide(); imageBox3->setFocusPolicy(Qt::NoFocus); imageBox3->setToolTip("Free for non-commercial use.");
    imageBox4 = new QCheckBox(tr("Amsterdam Library of Object Images - Wide-baseline stereo")); imageBox4->hide(); imageBox4->setFocusPolicy(Qt::NoFocus); imageBox4->setToolTip("Free for non-commercial use.");

    geoButton = new QPushButton(tr("Geospatial")); geoButton->setFocusPolicy(Qt::NoFocus); geoButton->setStyleSheet("Text-align: left; padding-left: 5px; padding-top: 3px; padding-bottom: 3px;");
    geoBox1 = new QCheckBox(tr("RTI Spatial Impact Factor Data based on county-level geography inc. 1960-2000")); geoBox1->hide(); geoBox1->setFocusPolicy(Qt::NoFocus); geoBox1->setToolTip("Free for non-commercial use.");
    geoBox2 = new QCheckBox(tr("RTI Spatial Impact Factor Data based on tract-level geography–1990")); geoBox2->hide(); geoBox2->setFocusPolicy(Qt::NoFocus); geoBox2->setToolTip("Free for non-commercial use.");
    geoBox3 = new QCheckBox(tr("RTI Spatial Impact Factor Data based on PCSA-level geography; November 2011")); geoBox3->hide(); geoBox3->setFocusPolicy(Qt::NoFocus); geoBox3->setToolTip("Free for non-commercial use.");
    geoBox4 = new QCheckBox(tr("RTI Spatial Impact Factor Data based on ZCTA-level geography–1990")); geoBox4->hide(); geoBox4->setFocusPolicy(Qt::NoFocus); geoBox4->setToolTip("Free for non-commercial use.");

    ecoButton = new QPushButton(tr("Economic")); ecoButton->setFocusPolicy(Qt::NoFocus); ecoButton->setStyleSheet("Text-align: left; padding-left: 5px; padding-top: 3px; padding-bottom: 3px;");
    ecoBox1 = new QCheckBox(tr("Occupational Wages around the World (OWW) Database")); ecoBox1->hide(); ecoBox1->setFocusPolicy(Qt::NoFocus); ecoBox1->setToolTip("Free for non-commercial use.");
    ecoBox2 = new QCheckBox(tr("Historical Cross-Country Technology Adoption (HCCTA) Dataset")); ecoBox2->hide(); ecoBox2->setFocusPolicy(Qt::NoFocus); ecoBox2->setToolTip("Free for non-commercial use.");
    ecoBox3 = new QCheckBox(tr("Public Use Tape on the Aging of Veterans of the Union Army")); ecoBox3->hide(); ecoBox3->setFocusPolicy(Qt::NoFocus); ecoBox3->setToolTip("Free for non-commercial use.");
    ecoBox4 = new QCheckBox(tr("Management practices across firms and countries")); ecoBox4->hide(); ecoBox4->setFocusPolicy(Qt::NoFocus); ecoBox4->setToolTip("Free for non-commercial use.");


    connect(urlLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableDownloadButton()));

    connect(&qnam, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this, SLOT(slotAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
#ifndef QT_NO_SSL
    connect(&qnam, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
#endif
    connect(progressBar, SIGNAL(canceled()), this, SLOT(cancelDownload()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelDownload()));
    connect(downloadButton, SIGNAL(clicked()), this, SLOT(weedOut()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(statButton, SIGNAL(clicked()), this, SLOT(statButtonActive()));
    connect(textButton, SIGNAL(clicked()), this, SLOT(textButtonActive()));
    connect(imageButton, SIGNAL(clicked()), this, SLOT(imageButtonActive()));
    connect(geoButton, SIGNAL(clicked()), this, SLOT(geoButtonActive()));
    connect(ecoButton, SIGNAL(clicked()), this, SLOT(ecoButtonActive()));
    connect(checkBox, SIGNAL(clicked()), this, SLOT (checkBoxChanged()));


    //********************************************************************************************************************
    //  SET UP USER INTERFACE
    //********************************************************************************************************************
    QVBoxLayout *statBoxes = new QVBoxLayout;
    statBoxes->addWidget(statBox1);
    statBoxes->addWidget(statBox2);
    statBoxes->addWidget(statBox3);
    statBoxes->addWidget(statBox4);

    QVBoxLayout *textBoxes = new QVBoxLayout;
    textBoxes->addWidget(textBox1);
    textBoxes->addWidget(textBox2);
    textBoxes->addWidget(textBox3);
    textBoxes->addWidget(textBox4);

    QVBoxLayout *imageBoxes = new QVBoxLayout;
    imageBoxes->addWidget(imageBox1);
    imageBoxes->addWidget(imageBox2);
    imageBoxes->addWidget(imageBox3);
    imageBoxes->addWidget(imageBox4);

    QVBoxLayout *geoBoxes = new QVBoxLayout;
    geoBoxes->addWidget(geoBox1);
    geoBoxes->addWidget(geoBox2);
    geoBoxes->addWidget(geoBox3);
    geoBoxes->addWidget(geoBox4);

    QVBoxLayout *ecoBoxes = new QVBoxLayout;
    ecoBoxes->addWidget(ecoBox1);
    ecoBoxes->addWidget(ecoBox2);
    ecoBoxes->addWidget(ecoBox3);
    ecoBoxes->addWidget(ecoBox4);

    QVBoxLayout *accordianLayout = new QVBoxLayout;
    accordianLayout->addWidget(statButton);
    accordianLayout->addLayout(statBoxes);
    accordianLayout->addWidget(textButton);
    accordianLayout->addLayout(textBoxes);
    accordianLayout->addWidget(imageButton);
    accordianLayout->addLayout(imageBoxes);
    accordianLayout->addWidget(geoButton);
    accordianLayout->addLayout(geoBoxes);
    accordianLayout->addWidget(ecoButton);
    accordianLayout->addLayout(ecoBoxes);

    QVBoxLayout *sideLayout = new QVBoxLayout;
    sideLayout->addWidget(introBody);
    sideLayout->addWidget(webLink);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(sideLayout);
    topLayout->addLayout(accordianLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(checkBox);
    bottomLayout->addWidget(buttonBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(progressBar);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);

    urlLineEdit->setFocus();
    checkCheckBoxState();
}

//set mode of autostart checkbox depending on if autostart is activated
void HttpWindow::checkCheckBoxState() {
    if (QFile::exists("/usr/share/datasets/datasets.desktop")) {
        checkBox->setChecked(true);
    }
}
//function to activate/deactivate autostart through the autostart checkbox
void HttpWindow::checkBoxChanged() {
    if (checkBox->isChecked()) {
        system("gksudo cp /usr/share/applications/datasets.desktop /usr/share/datasets/datasets.desktop");
    }else{
        system("gksudo rm /usr/share/datasets/datasets.desktop");
    }
}

//on downloadButton click
void HttpWindow::weedOut() {
    //set all checkboxes as not downloaded yet
    yupStat1 = false; yupStat2 = false; yupStat3 = false; yupStat4 = false;
    yupText1 = false; yupText2 = false; yupText3 = false; yupText4 = false;
    yupIMG1 = false; yupIMG2 = false; yupIMG3 = false; yupIMG4 = false;
    yupGeo1 = false; yupGeo2 = false; yupGeo3 = false; yupGeo4 = false;
    yupEco1 = false; yupEco2 = false; yupEco3 = false; yupEco4 = false;

    //continue with download
    determine();
}

//used to loop after a download is completed without resetting checkboxes
void HttpWindow::determine() {

    determineDownload(statBox1);
}

//determine which checkboxes to download
void HttpWindow::determineDownload(QCheckBox *) {

    QString home = QDir::homePath();

        //asyncronos download. after one download completes "determine();" is called
        if (yupStat1 == false && statBox1->isChecked()) {
            yupStat1 = true; //downloaded, dont download again
            QString downloadName("Ministerial Expenditures by Standard Object - Volume 2, Table 3.zip");
            if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
            if (!QFile::exists(QString(home)+"/Data/Statistical/")) { system("mkdir ~/Data/Statistical/"); }
            QString downloadLocation("/Data/Statistical/%1");
            url = "http://thinknook.com/wp-content/uploads/2012/09/Sentiment-Analysis-Dataset.zip";
            downloadFile(url, downloadName, downloadLocation);
        }else{
            if (yupStat2 == false && statBox2->isChecked()) {
                yupStat2 = true; //downloaded, dont download again
                QString downloadName("Ten Year Comparative Financial Information - Volume 1.csv");
                if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                if (!QFile::exists(QString(home)+"/Data/Statistical/")) { system("mkdir ~/Data/Statistical/"); }
                QString downloadLocation("/Data/Statistical/%1");
                url = "http://www.tpsgc-pwgsc.gc.ca/recgen/donneesouvertes-opendata/cpc-pac/PA-V1-eng.csv";
                downloadFile(url, downloadName, downloadLocation);
            }else{
                if (yupStat3 == false && statBox3->isChecked()) {
                    yupStat3 = true; //downloaded, dont download again
                    QString downloadName("Statistical Report on International Assistance - by Country Spending 2009-2010.csv");
                    if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                    if (!QFile::exists(QString(home)+"/Data/Statistical/")) { system("mkdir ~/Data/Statistical/"); }
                    QString downloadLocation("/Data/Statistical/%1");
                    url = "http://www.acdi-cida.gc.ca/INET/IMAGES.NSF/vLUImages/Open%20Data/$file/OpenData-Country-Statistics-2009-2010.csv";
                    downloadFile(url, downloadName, downloadLocation);
                }else{
                    if (yupStat4 == false && statBox4->isChecked()) {
                        yupStat4 = true; //downloaded, dont download again
                        QString downloadName("Statistical Report on International Assistance - by Country Spending 2004-2005.csv");
                        if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                        if (!QFile::exists(QString(home)+"/Data/Statistical/")) { system("mkdir ~/Data/Statistical/"); }
                        QString downloadLocation("/Data/Statistical/%1");
                        url = "http://www.acdi-cida.gc.ca/INET/IMAGES.NSF/vLUImages/Open%20Data/$file/OpenData-Country-Statistics-2004-2005.csv";
                        downloadFile(url, downloadName, downloadLocation);
                    }else{
                        if (yupText1 == false && textBox1->isChecked()) {
                            yupText1 = true; //downloaded, dont download again
                            QString downloadName("Twitter Sentiment Corpus.zip");
                            if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                            if (!QFile::exists(QString(home)+"/Data/Text/")) { system("mkdir ~/Data/Text/"); }
                            QString downloadLocation("/Data/Text/%1");
                            url = "http://www.sananalytics.com/lab/twitter-sentiment/sanders-twitter-0.2.zip";
                            downloadFile(url, downloadName, downloadLocation);
                        }else{
                            if (yupText2 == false && textBox2->isChecked()) {
                                yupText2 = true; //downloaded, dont download again
                                QString downloadName("Sentiment Analysis.zip");
                                if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                if (!QFile::exists(QString(home)+"/Data/Text/")) { system("mkdir ~/Data/Text/"); }
                                QString downloadLocation("/Data/Text/%1");
                                url = "http://thinknook.com/wp-content/uploads/2012/09/Sentiment-Analysis-Dataset.zip";
                                downloadFile(url, downloadName, downloadLocation);
                            }else{
                                if (yupText3 == false && textBox3->isChecked()) {
                                    yupText3 = true; //downloaded, dont download again
                                    QString downloadName("Slashdot Zoo signed social network of users.bz2");
                                    if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                    if (!QFile::exists(QString(home)+"/Data/Text/")) { system("mkdir ~/Data/Text/"); }
                                    QString downloadLocation("/Data/Text/%1");
                                    url = "http://konect.uni-koblenz.de/downloads/own/slashdot-zoo.tar.bz2";
                                    downloadFile(url, downloadName, downloadLocation);
                                }else{
                                    if (yupText4 == false && textBox4->isChecked()) {
                                        yupText4 = true; //downloaded, dont download again
                                        QString downloadName("Newswire FSD Corpus.tar.gz");
                                        if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                        if (!QFile::exists(QString(home)+"/Data/Text/")) { system("mkdir ~/Data/Text/"); }
                                        QString downloadLocation("/Data/Text/%1");
                                        url = "http://demeter.inf.ed.ac.uk/cross/docs/Newswire_Events.tar.gz";
                                        downloadFile(url, downloadName, downloadLocation);
                                    }else{
                                        if (yupIMG1 == false && imageBox1->isChecked()) {
                                            yupIMG1 = true; //downloaded, dont download again
                                            QString downloadName("Labeled Faces in the Wild Home.tgz");
                                            if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                            if (!QFile::exists(QString(home)+"/Data/Image/")) { system("mkdir ~/Data/Image/"); }
                                            QString downloadLocation("/Data/Image/%1");
                                            url = "http://vis-www.cs.umass.edu/lfw/lfw.tgz";
                                            downloadFile(url, downloadName, downloadLocation);
                                        }else{
                                            if (yupIMG2 == false && imageBox2->isChecked()) {
                                                yupIMG2 = true;
                                                QString downloadName("The Database of Faces (formerly 'The ORL Database of Faces').zip");
                                                if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                if (!QFile::exists(QString(home)+"/Data/Image/")) { system("mkdir ~/Data/Image/"); }
                                                QString downloadLocation("/Data/Image/%1");
                                                url = "http://www.cl.cam.ac.uk/Research/DTG/attarchive/pub/data/att_faces.zip";
                                                downloadFile(url, downloadName, downloadLocation);
                                            }else{
                                                if (yupIMG3 == false && imageBox3->isChecked()) {
                                                    yupIMG3 = true;
                                                    QString downloadName("Collection of Facial Images: Grimace.zip");
                                                    if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                    if (!QFile::exists(QString(home)+"/Data/Image/")) { system("mkdir ~/Data/Image/"); }
                                                    QString downloadLocation("/Data/Image/%1");
                                                    url = "http://cswww.essex.ac.uk/mv/allfaces/grimace.zip";
                                                    downloadFile(url, downloadName, downloadLocation);
                                                }else{
                                                    if (yupIMG4 == false && imageBox4->isChecked()) {
                                                        yupIMG4 = true;
                                                        QString downloadName("Amsterdam Library of Object Images - Wide-baseline stereo.tar");
                                                        if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                        if (!QFile::exists(QString(home)+"/Data/Image/")) { system("mkdir ~/Data/Image/"); }
                                                        QString downloadLocation("/Data/Image/%1");
                                                        url = "http://www.science.uva.nl/sites/ALOI/aloi_stereo.tar";
                                                        downloadFile(url, downloadName, downloadLocation);
                                                    }else{
                                                        if (yupGeo1 == false && geoBox1->isChecked()) {
                                                            yupGeo1= true;
                                                            QString downloadName("RTI Spatial Impact Factor Data based on county-level geography inc. 1960-2000.zip");
                                                            if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                            if (!QFile::exists(QString(home)+"/Data/Geospatial/")) { system("mkdir ~/Data/Geospatial/"); }
                                                            QString downloadLocation("/Data/Geospatial/%1");
                                                            url = "https://rtispatialdata.rti.org/LinkClick.aspx?fileticket=98SGN2EM9xM%3d&tabid=56&mid=383";
                                                            downloadFile(url, downloadName, downloadLocation);
                                                        }else{
                                                            if (yupGeo2 == false && geoBox2->isChecked()) {
                                                                yupGeo2 = true;
                                                                QString downloadName("RTI Spatial Impact Factor Data based on tract-level geography–1990.zip");
                                                                if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                                if (!QFile::exists(QString(home)+"/Data/Geospatial/")) { system("mkdir ~/Data/Geospatial/"); }
                                                                QString downloadLocation("/Data/Geospatial/%1");
                                                                url = "https://rtispatialdata.rti.org/LinkClick.aspx?fileticket=ixuKOw%2fwT9c%3d&tabid=56&mid=383";
                                                                downloadFile(url, downloadName, downloadLocation);
                                                            }else{
                                                                if (yupGeo3 == false && geoBox3->isChecked()) {
                                                                    yupGeo3 = true;
                                                                    QString downloadName("RTI Spatial Impact Factor Data based on PCSA-level geography; November 2011.zip");
                                                                    if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                                    if (!QFile::exists(QString(home)+"/Data/Geospatial/")) { system("mkdir ~/Data/Geospatial/"); }
                                                                    QString downloadLocation("/Data/Geospatial/%1");
                                                                    url = "https://rtispatialdata.rti.org/LinkClick.aspx?fileticket=iW%2fJagnoctg%3d&tabid=56&mid=383";
                                                                    downloadFile(url, downloadName, downloadLocation);
                                                                }else{
                                                                    if (yupGeo4 == false && geoBox4->isChecked()) {
                                                                        yupGeo4 = true;
                                                                        QString downloadName("RTI Spatial Impact Factor Data based on ZCTA-level geography–1990.zip");
                                                                        if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                                        if (!QFile::exists(QString(home)+"/Data/Geospatial/")) { system("mkdir ~/Data/Geospatial/"); }
                                                                        QString downloadLocation("/Data/Geospatial/%1");
                                                                        url = "https://rtispatialdata.rti.org/LinkClick.aspx?fileticket=zTxG%2fpGvtJA%3d&tabid=56&mid=383";
                                                                        downloadFile(url, downloadName, downloadLocation);
                                                                    }else{
                                                                        if (yupEco1 == false && ecoBox1->isChecked()) {
                                                                            yupEco1 = true;
                                                                            QString downloadName("Occupational Wages around the World (OWW) Database.csv");
                                                                            if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                                            if (!QFile::exists(QString(home)+"/Data/Economic/")) { system("mkdir ~/Data/Economic/"); }
                                                                            QString downloadLocation("/Data/Economic/%1");
                                                                            url = "http://www.nber.org/oww/oww3.csv";
                                                                            downloadFile(url, downloadName, downloadLocation);
                                                                        }else{
                                                                            if (yupEco2 == false && ecoBox2->isChecked()) {
                                                                                yupEco2 = true;
                                                                                QString downloadName("Historical Cross-Country Technology Adoption (HCCTA) Dataset.csv");
                                                                                if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                                                if (!QFile::exists(QString(home)+"/Data/Economic/")) { system("mkdir ~/Data/Economic/"); }
                                                                                QString downloadLocation("/Data/Economic/%1");
                                                                                url = "http://www.nber.org/hccta/hcctad.txt";
                                                                                downloadFile(url, downloadName, downloadLocation);
                                                                            }else{
                                                                                if (yupEco3 == false && ecoBox3->isChecked()) {
                                                                                    yupEco3 = true;
                                                                                    QString downloadName("Public Use Tape on the Aging of Veterans of the Union Army.zip");
                                                                                    if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                                                    if (!QFile::exists(QString(home)+"/Data/Economic/")) { system("mkdir ~/Data/Economic/"); }
                                                                                    QString downloadLocation("/Data/Economic/%1");
                                                                                    url = "http://www.nber.org/milpen/EntireDataset/milaxt.zip";
                                                                                    downloadFile(url, downloadName, downloadLocation);
                                                                                }else{
                                                                                    if (yupEco4 == false && ecoBox4->isChecked()) {
                                                                                        yupEco4 = true;
                                                                                        QString downloadName("Management practices across firms and countries.zip");
                                                                                        if (!QFile::exists(QString(home)+"/Data/")) { system("mkdir ~/Data/"); }
                                                                                        if (!QFile::exists(QString(home)+"/Data/Economic/")) { system("mkdir ~/Data/Economic/"); }
                                                                                        QString downloadLocation("/Data/Economic/%1");
                                                                                        url = "http://worldmanagementsurvey.org/wp-content/images/2012/07/AMP.zip";
                                                                                        downloadFile(url, downloadName, downloadLocation);
                                                                                    }else{
                                                                                        statBox1->setChecked(false); statBox2->setChecked(false); statBox3->setChecked(false); statBox4->setChecked(false);
                                                                                        textBox1->setChecked(false); textBox2->setChecked(false); textBox3->setChecked(false); textBox4->setChecked(false);
                                                                                        imageBox1->setChecked(false); imageBox2->setChecked(false); imageBox3->setChecked(false); imageBox4->setChecked(false);
                                                                                        geoBox1->setChecked(false); geoBox2->setChecked(false); geoBox3->setChecked(false); geoBox4->setChecked(false);
                                                                                        ecoBox1->setChecked(false); ecoBox2->setChecked(false); ecoBox3->setChecked(false); ecoBox4->setChecked(false);
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }


}

void HttpWindow::startRequest(QUrl url) {
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(reply, SIGNAL(finished()),
            this, SLOT(determine()));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void HttpWindow::downloadFile(QUrl url, QString downloadName, QString downloadLocation) {

    QFileInfo fileInfo(downloadName);
    QString fileName = fileInfo.fileName();
    QString home = QDir::homePath();
    if (fileName.isEmpty())
        fileName = "index.html";

    file = new QFile(QString(home)+QString(downloadLocation).arg(fileName));
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        file = 0;
        return;
    }

    statusLabel->setText(tr("Downloading %1").arg(fileName));
    progressBar->show();
    downloadButton->setEnabled(false);
    quitButton->setEnabled(false);
    cancelButton->setEnabled(true);
    cancelButton->setDefault(true);

    // schedule the request
    httpRequestAborted = false;
    startRequest(url);
}

void HttpWindow::cancelDownload() {
    statusLabel->setText(tr("Download canceled."));
    httpRequestAborted = true;
    reply->disconnect();
    progressBar->hide();
    progressBar->reset();
    cancelButton->setEnabled(false);
    downloadButton->setEnabled(true);
    downloadButton->setDefault(true);
    quitButton->setEnabled(true);
}

void HttpWindow::httpFinished() {
    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
        progressBar->hide();
        return;
    }

    progressBar->hide();
    progressBar->reset();
    quitButton->setEnabled(true);
    cancelButton->setEnabled(false);

    file->flush();
    file->close();

    if (reply->error()) {
        file->remove();
        QMessageBox::information(this, tr("error"),
                                 tr("Download failed: %1.")
                                 .arg(reply->errorString()));
        downloadButton->setEnabled(true);
        statusLabel->setText(tr("Download failed."));
    } else {
        QString displayedDownloadLocation("~/Data/");
        statusLabel->setText(tr("Downloaded data set(s) to %1.").arg(displayedDownloadLocation));
        downloadButton->setEnabled(true);
    }

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void HttpWindow::httpReadyRead() {
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());
}

void HttpWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes) {
    if (httpRequestAborted)
        return;

    progressBar->setMaximum(totalBytes);
    progressBar->setValue(bytesRead);
}

void HttpWindow::enableDownloadButton() {
    downloadButton->setEnabled(!urlLineEdit->text().isEmpty());
}


//********************************************************************************************************************************
//  FUNCTIONS TO CONTROL ACCORDIAN MENU
//********************************************************************************************************************************
void HttpWindow::statButtonActive() {
    statBox1->show(); statBox2->show(); statBox3->show(); statBox4->show();
    textBox1->hide(); textBox2->hide(); textBox3->hide(); textBox4->hide();
    imageBox1->hide(); imageBox2->hide(); imageBox3->hide(); imageBox4->hide();
    geoBox1->hide(); geoBox2->hide(); geoBox3->hide(); geoBox4->hide();
    ecoBox1->hide(); ecoBox2->hide(); ecoBox3->hide(); ecoBox4->hide();
}

void HttpWindow::textButtonActive() {
    statBox1->hide(); statBox2->hide(); statBox3->hide(); statBox4->hide();
    textBox1->show(); textBox2->show(); textBox3->show(); textBox4->show();
    imageBox1->hide(); imageBox2->hide(); imageBox3->hide(); imageBox4->hide();
    geoBox1->hide(); geoBox2->hide(); geoBox3->hide(); geoBox4->hide();
    ecoBox1->hide(); ecoBox2->hide(); ecoBox3->hide(); ecoBox4->hide();
}

void HttpWindow::imageButtonActive() {
    statBox1->hide(); statBox2->hide(); statBox3->hide(); statBox4->hide();
    textBox1->hide(); textBox2->hide(); textBox3->hide(); textBox4->hide();
    imageBox1->show(); imageBox2->show(); imageBox3->show(); imageBox4->show();
    geoBox1->hide(); geoBox2->hide(); geoBox3->hide(); geoBox4->hide();
    ecoBox1->hide(); ecoBox2->hide(); ecoBox3->hide(); ecoBox4->hide();
}

void HttpWindow::geoButtonActive() {
    statBox1->hide(); statBox2->hide(); statBox3->hide(); statBox4->hide();
    textBox1->hide(); textBox2->hide(); textBox3->hide(); textBox4->hide();
    imageBox1->hide(); imageBox2->hide(); imageBox3->hide(); imageBox4->hide();
    geoBox1->show(); geoBox2->show(); geoBox3->show(); geoBox4->show();
    ecoBox1->hide(); ecoBox2->hide(); ecoBox3->hide(); ecoBox4->hide();
}

void HttpWindow::ecoButtonActive() {
    statBox1->hide(); statBox2->hide(); statBox3->hide(); statBox4->hide();
    textBox1->hide(); textBox2->hide(); textBox3->hide(); textBox4->hide();
    imageBox1->hide(); imageBox2->hide(); imageBox3->hide(); imageBox4->hide();
    geoBox1->hide(); geoBox2->hide(); geoBox3->hide(); geoBox4->hide();
    ecoBox1->show(); ecoBox2->show(); ecoBox3->show(); ecoBox4->show();
}

#ifndef QT_NO_SSL
void HttpWindow::sslErrors(QNetworkReply*,const QList<QSslError> &errors) {
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += ", ";
        errorString += error.errorString();
    }

    if (QMessageBox::warning(this, tr("HTTP"),
                             tr("One or more SSL errors has occurred: %1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        reply->ignoreSslErrors();
    }
}


void HttpWindow::slotAuthenticationRequired(QNetworkReply*,QAuthenticator *authenticator) {

}
#endif
