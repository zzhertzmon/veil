#include <qt/veil/qtutils.h>

#include <qt/veil/toast.h>

void openDialog(QWidget * dialog){
    dialog->setWindowFlags(Qt::CustomizeWindowHint);
    dialog->setAttribute(Qt::WA_TranslucentBackground, true);
    //dialog->move(x() + (width() - dialog->width()) / 2,
    //                 y() + (height() - dialog->height()) / 2);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void openDialogFullScreen(QWidget *parent, QWidget * dialog){
    dialog->setWindowFlags(Qt::CustomizeWindowHint);
    //dialog->setAttribute(Qt::WA_TranslucentBackground, true);
    dialog->move(0, 0);
    dialog->show();
    dialog->activateWindow();
    dialog->resize(parent->width(),parent->height());
}

bool openDialogWithOpaqueBackgroundY(QDialog *widget, BitcoinGUI *gui, double posX, int posY){
    widget->setWindowFlags(Qt::CustomizeWindowHint);
    widget->setAttribute(Qt::WA_TranslucentBackground, true);
    QPropertyAnimation* animation = new QPropertyAnimation(widget, "pos");
    animation->setDuration(300);
    int xPos = gui->width() / posX ;
    animation->setStartValue(QPoint(xPos, gui->height()));
    animation->setEndValue(QPoint(xPos, gui->height() / posY));//- (gui->height()) / posY  ));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    widget->activateWindow();
    bool res = widget->exec();
    gui->showHide(false);
    return res;
}

bool openDialogWithOpaqueBackground(QDialog *widget, BitcoinGUI *gui, double posX){
    return openDialogWithOpaqueBackgroundY(widget, gui, posX, 5);
}

void openDialogWithOpaqueBackgroundFullScreen(QDialog *widget, BitcoinGUI *gui){
    widget->setWindowFlags(Qt::CustomizeWindowHint);
    widget->setAttribute(Qt::WA_TranslucentBackground, true);

    widget->activateWindow();
    widget->resize(gui->width(),gui->height());

    QPropertyAnimation* animation = new QPropertyAnimation(widget, "pos");
    animation->setDuration(300);
    int xPos = 0;
    animation->setStartValue(QPoint(xPos, gui->height()));
    animation->setEndValue(QPoint(xPos, 0));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    widget->activateWindow();
    bool res = widget->exec();
    gui->showHide(false);
}


void openToastDialog(QString text, QWidget* gui){
    Toast* widget = new Toast(gui, text);
    widget->setWindowFlags(Qt::CustomizeWindowHint);
    widget->setAttribute(Qt::WA_TranslucentBackground, true);
    QPropertyAnimation* animation = new QPropertyAnimation(widget, "pos");
    animation->setDuration(250);
    int xPos = gui->width() / 2.75 ;
    animation->setStartValue(QPoint(xPos, gui->height()));
    //- (gui->height() / 5)
    animation->setEndValue(QPoint(xPos, gui->height() - 65));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    widget->activateWindow();
    widget->show();
}


QSettings * getSettings(){
    QString m_path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    QString m_filename = "config.ini" ;
    QSettings *settings = new QSettings(m_path + "/"+ m_filename,QSettings::IniFormat);
    return settings;
}