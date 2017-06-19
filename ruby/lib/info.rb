#!/usr/bin/ruby

## info module

require "net/http"

class Info
  def get_info
    host = Socket.gethostname
    res = Net::HTTP.get(URI("http://ipinfo.io/json"))
    res.to_s
  end
end

=begin
      #Backup code :

      host = Socket.gethostname
      res = Net::HTTP.get(URI("http://ipinfo.io/json"))
      resf = res.to_s
      parsed = JSON.parse(resf)

      bot.api.send_message(chat_id: message.chat.id, text: "[*] IP Adress : #{parsed["ip"]} \n[*] Host Name : #{parsed["hostname"]} \n
[*] City : #{parsed["city"]} \n[*] Region : #{parsed["region"]} \n
[*] Country : #{parsed["country"]} \n[*] Locations : #{parsed["loc"]} \n
[*] Org : #{parsed["org"]}")

=end
