#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QCheckBox>
#include <QAbstractScrollArea>


class QDialogButtonBox;
class QFile;
class QLabel;
class QLineEdit;
class QProgressBar;
class QPushButton;
class QSslError;
class QAuthenticator;
class QNetworkReply;
class QLabel;

class HttpWindow : public QDialog
{
    Q_OBJECT

public:
    HttpWindow(QWidget *parent = 0);

    void startRequest(QUrl url);

private slots:
    void checkCheckBoxState();
    void checkBoxChanged();
    void statButtonActive();
    void textButtonActive();
    void imageButtonActive();
    void geoButtonActive();
    void ecoButtonActive();
    void determineDownload(QCheckBox*);
    void determine();
    void weedOut();
    void downloadFile(QUrl url, QString downloadName, QString downloadLocation);
    void cancelDownload();
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64 bytesRead, qint64 totalBytes);
    void enableDownloadButton();
    void slotAuthenticationRequired(QNetworkReply*,QAuthenticator *);
#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
#endif

private:
    QLabel *statusLabel;
    QLabel *urlLabel;
    QLabel *introBody;
    QLabel *webLink;
    QLineEdit *urlLineEdit;
    QProgressBar *progressBar;
    QDialogButtonBox *buttonBox;
    QPushButton *downloadButton;
    QPushButton *quitButton;
    QPushButton *cancelButton;
    QCheckBox *checkBox;
    QPushButton *statButton;
    QCheckBox *statBox1;
    QCheckBox *statBox2;
    QCheckBox *statBox3;
    QCheckBox *statBox4;
    QPushButton *textButton;
    QCheckBox *textBox1;
    QCheckBox *textBox2;
    QCheckBox *textBox3;
    QCheckBox *textBox4;
    QPushButton *imageButton;
    QCheckBox *imageBox1;
    QCheckBox *imageBox2;
    QCheckBox *imageBox3;
    QCheckBox *imageBox4;
    QPushButton *geoButton;
    QCheckBox *geoBox1;
    QCheckBox *geoBox2;
    QCheckBox *geoBox3;
    QCheckBox *geoBox4;
    QPushButton *ecoButton;
    QCheckBox *ecoBox1;
    QCheckBox *ecoBox2;
    QCheckBox *ecoBox3;
    QCheckBox *ecoBox4;

    QAbstractScrollArea *scrollArea;

    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    int httpGetId;
    bool httpRequestAborted;

    int yupStat1; int yupStat2; int yupStat3; int yupStat4;
    int yupText1; int yupText2; int yupText3; int yupText4;
    int yupIMG1; int yupIMG2; int yupIMG3; int yupIMG4;
    int yupGeo1; int yupGeo2; int yupGeo3; int yupGeo4;
    int yupEco1; int yupEco2; int yupEco3; int yupEco4;
};

#endif
