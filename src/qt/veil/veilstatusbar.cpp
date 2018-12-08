#include <qt/veil/veilstatusbar.h>
#include <qt/veil/forms/ui_veilstatusbar.h>

#include <qt/bitcoingui.h>
#include <qt/walletmodel.h>
#include <qt/veil/qtutils.h>
#include <iostream>

VeilStatusBar::VeilStatusBar(QWidget *parent, BitcoinGUI* gui) :
    QWidget(parent),
    mainWindow(gui),
    ui(new Ui::VeilStatusBar)
{
    ui->setupUi(this);

    ui->checkStacking->setProperty("cssClass" , "switch");

    connect(ui->btnLock, SIGNAL(clicked()), this, SLOT(onBtnLockClicked()));
    connect(ui->btnSync, SIGNAL(clicked()), this, SLOT(onBtnSyncClicked()));
    connect(ui->checkStacking, SIGNAL(toggled(bool)), this, SLOT(onCheckStakingClicked(bool)));
}

void VeilStatusBar::updateSyncStatus(QString status){
    ui->btnSync->setText(status);
}

void VeilStatusBar::onBtnSyncClicked(){
    mainWindow->showModalOverlay();
}

void VeilStatusBar::onCheckStakingClicked(bool res){
    // Miner starts here..
    GenerateBitcoins(res, 1, nullptr);
    if(res){
        openToastDialog("Miner started", mainWindow);
    }else{
        openToastDialog("Miner stopped", mainWindow);
    }

}

void VeilStatusBar::onBtnLockClicked(){
    mainWindow->encryptWallet(walletModel->getEncryptionStatus() != WalletModel::Locked);
}

void VeilStatusBar::setWalletModel(WalletModel *model) {
    this->walletModel = model;
    if(walletModel->getEncryptionStatus() == WalletModel::Locked){
        ui->btnLock->setChecked(true);
    }else{
        ui->btnLock->setChecked(false);
    }
}

VeilStatusBar::~VeilStatusBar()
{
    delete ui;
}