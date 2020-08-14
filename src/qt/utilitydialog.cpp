// Copyright (c) 2011-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "utilitydialog.h"

#include "ui_helpmessagedialog.h"

#include "bitcoingui.h"
#include "clientmodel.h"
#include "guiutil.h"

#include "clientversion.h"
#include "init.h"
#include "rpcmisc.h"

#include <stdio.h>

#include <QCloseEvent>
#include <QLabel>
#include <QRegExp>
#include <QVBoxLayout>

#include "json/json_spirit_value.h"

/** "Help message" or "About" dialog box */
HelpMessageDialog::HelpMessageDialog(QWidget *parent, bool about, bool checkUpdates) :
    QDialog(parent),
    ui(new Ui::HelpMessageDialog)
{
    ui->setupUi(this);
    GUIUtil::restoreWindowGeometry("nHelpMessageDialogWindow", this->size(), this);

    QString version = tr("Reddcoin Core") + " " + tr("version") + " " + QString::fromStdString(FormatFullVersion());
    /* On x86 add a bit specifier to the version so that users can distinguish between
     * 32 and 64 bit builds. On other architectures, 32/64 bit may be more ambigious.
     */
#if defined(__x86_64__)
    version += " " + tr("(%1-bit)").arg(64);
#elif defined(__i386__ )
    version += " " + tr("(%1-bit)").arg(32);
#endif

    if (about || checkUpdates)
    {
        // Make URLs clickable
        QRegExp uri("<(.*)>", Qt::CaseSensitive, QRegExp::RegExp2);
        uri.setMinimal(true); // use non-greedy matching
        ui->helpMessageLabel->setTextFormat(Qt::RichText);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->helpMessageLabel->setWordWrap(true);

        if (about) {
            // Switching back to normal dialog window size
            resize(800, 400);
            setWindowTitle(tr("About Reddcoin Core"));
            /// HTML-format the license message from the core
            QString licenseInfo = QString::fromStdString(LicenseInfo());
            QString licenseInfoHTML = licenseInfo;

            licenseInfoHTML.replace(uri, "<a href=\"\\1\">\\1</a>");
            // Replace newlines with HTML breaks
            licenseInfoHTML.replace("\n\n", "<br><br>");

            text = version + "\n" + licenseInfo;
            ui->helpMessageLabel->setText(version + "<br><br>" + licenseInfoHTML);
        } else {
            // Set small initial dialog window size for checkupdates dialog
            resize(800, 200);

            setWindowTitle(tr("Check for Updates"));
            text = "Checking for updates. Please wait...";
            ui->helpMessageLabel->setText(text);

            // Get checkforupdatesinfo from rpcmisc
            json_spirit::Value result = checkforupdatesinfo();
            json_spirit::Object jsonObject = result.get_obj();
            QString installedVersion = "";
            QString latestReleaseVersion = "";
            QString message = "";
            QString officialDownloadLink = "";
            QString errors = "";

            for (auto entry : jsonObject) {
                if (entry.name_ == "installedVersion") {
                    installedVersion = QString::fromStdString(entry.value_.get_str());
                } else if (entry.name_ == "latestReleaseVersion") {
                    latestReleaseVersion = QString::fromStdString(entry.value_.get_str());
                } else if (entry.name_ == "message") {
                    message = QString::fromStdString(entry.value_.get_str());
                } else if (entry.name_ == "officialDownloadLink") {
                    officialDownloadLink = QString::fromStdString(entry.value_.get_str());
                } else {
                    errors = QString::fromStdString(entry.value_.get_str());
                }
            }

            if (!errors.isEmpty()) {
                text = "<font color = 'red'>Error: </font>";
                text += errors;
            } else if (installedVersion == latestReleaseVersion) {
                text = message;
            } else {
                QString url = "<a href=\""+ officialDownloadLink +"\">"+ officialDownloadLink +"</a>";

                text = "Installed version: <b>" + installedVersion  + "</b><br>";
                text += "Latest release version: <b>" + latestReleaseVersion + "</b><br><br>";
                text += "Please download the latest version from our official website (" + url + ").";
            }

            ui->helpMessageLabel->setText(text);
        }
    } else {
        // Switching back to normal dialog window size
        resize(800, 400);
        setWindowTitle(tr("Command-line options"));
        QString header = tr("Usage:") + "\n" +
                "  reddcoin-qt [" + tr("command-line options") + "]                     " + "\n";

        QString coreOptions = QString::fromStdString(HelpMessage(HMM_BITCOIN_QT));
        QString uiOptions = tr("UI options") + ":\n" +
                "  -choosedatadir            " + tr("Choose data directory on startup (default: 0)") + "\n" +
                "  -lang=<lang>              " + tr("Set language, for example \"de_DE\" (default: system locale)") + "\n" +
                "  -min                      " + tr("Start minimized") + "\n" +
                "  -rootcertificates=<file>  " + tr("Set SSL root certificates for payment request (default: -system-)") + "\n" +
                "  -splash                   " + tr("Show splash screen on startup (default: 1)");

        ui->helpMessageLabel->setFont(GUIUtil::bitcoinAddressFont());
        text = version + "\n" + header + "\n" + coreOptions + "\n" + uiOptions;
        ui->helpMessageLabel->setText(text);
    }
}

HelpMessageDialog::~HelpMessageDialog()
{
    GUIUtil::saveWindowGeometry("nHelpMessageDialogWindow", this);
    delete ui;
}

void HelpMessageDialog::printToConsole()
{
    // On other operating systems, the expected action is to print the message to the console.
    fprintf(stdout, "%s\n", qPrintable(text));
}

void HelpMessageDialog::showOrPrint()
{
#if defined(WIN32)
    // On Windows, show a message box, as there is no stderr/stdout in windowed applications
    exec();
#else
    // On other operating systems, print help text to console
    printToConsole();
#endif
}

void HelpMessageDialog::on_okButton_accepted()
{
    close();
}


/** "Shutdown" window */
ShutdownWindow::ShutdownWindow(QWidget *parent, Qt::WindowFlags f):
    QWidget(parent, f)
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel(
        tr("Reddcoin Core is shutting down...") + "<br /><br />" +
        tr("Do not shut down the computer until this window disappears.")));
    setLayout(layout);
}

void ShutdownWindow::showShutdownWindow(BitcoinGUI *window)
{
    if (!window)
        return;

    // Show a simple window indicating shutdown status
    QWidget *shutdownWindow = new ShutdownWindow();
    // We don't hold a direct pointer to the shutdown window after creation, so use
    // Qt::WA_DeleteOnClose to make sure that the window will be deleted eventually.
    shutdownWindow->setAttribute(Qt::WA_DeleteOnClose);
    shutdownWindow->setWindowTitle(window->windowTitle());

    // Center shutdown window at where main window was
    const QPoint global = window->mapToGlobal(window->rect().center());
    shutdownWindow->move(global.x() - shutdownWindow->width() / 2, global.y() - shutdownWindow->height() / 2);
    shutdownWindow->show();
}

void ShutdownWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
}
