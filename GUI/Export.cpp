#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QMainWindow>
#include <QDate>

#include "Common/ExportData.h"
#include "Common/ExportImage.h"
#include "Charts/PlotBase.h"
#include "Common/Constants.h"
#include "Common/Configuration.h"

#include "Export.h"
#include "ui_Export.h"
#include "DockWidget.h"
#include "ModelsAndViews/DataView.h"
#include "PlotDockWidget.h"

const char* Export::exportFilesDateFormat_ = "yyyyMMdd";

Export::Export(QMainWindow* tab, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Export),
    tab_(tab)
{
    ui->setupUi(this);

    ui->locationLineEdit->setText(Configuration::getInstance().getImportFilePath());

    ui->prefix->setValidator(new QRegExpValidator(QRegExp("[\\w]*"), ui->prefix));

    ui->prefix->setText(tab_->windowTitle().replace(QRegExp("[^\\w]"), QLatin1String("")));

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Export::~Export()
{
    delete ui;
}

void Export::on_save_clicked()
{
    QDir dir(ui->locationLineEdit->text());

    if (ui->locationLineEdit->text().isEmpty() ||
        !dir.exists() ||
        !QFile::permissions(dir.path()).testFlag(QFile::WriteUser))
    {
        QMessageBox::warning(this,
                             QObject::tr("Error"),
                             QObject::tr("Can not create file in given location."));
        return;
    }

    saveOnDisk();

    accept();
}

void Export::on_locationSearch_clicked()
{
    QFileDialog dialog;
    dialog.setDirectory(ui->locationLineEdit->text());
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.exec();
    ui->locationLineEdit->setText(dialog.directory().absolutePath());
}

void Export::saveOnDisk()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::processEvents();

    QString dateString(QDate::currentDate().toString(exportFilesDateFormat_));
    QString fileName(ui->locationLineEdit->text() + "/" + ui->prefix->text() +
                     "_" + dateString);
    QList<PlotDockWidget*> docks = tab_->findChildren<PlotDockWidget*>();
    for (PlotDockWidget* dock : docks)
    {
        QList<PlotBase*> list = dock->exportContent();
        for (PlotBase* plot : list)
        {
            QString name(fileName + "_" + plot->windowTitle() + ".png");
            ExportImage::exportAsImage(plot, name);
        }

    }
    auto view = tab_->findChild<DataView*>();
    Q_ASSERT(nullptr != view);

    if (ui->xlsx->isChecked())
    {
        ExportData::exportAsXLSX(view, fileName + "_" + tr("data") + ".xlsx");
    }
    else
    {
        ExportData::exportAsCsv(view,
                                fileName + "_" + tr("data") + ".csv",
                                false); //false = not inner format
    }

    QApplication::restoreOverrideCursor();
}
