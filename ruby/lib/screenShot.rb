#!/usr/bin/ruby

## screenShot module

require "cloudinary"

class ScreenShot
  def get_screen_windows

  end

  def get_screen_linux
    #linux platform
    #get screenshot with shell linux
    res = %x{import -window root -resize 1360x768 -delay 200 screenshot.png}
    #setting Cloudinary api
    auth = {
        cloud_name: "dnno5u4ug",
        api_key:    "577794173378992",
        api_secret: "5MFNU2rcqMWg69lCHJDcxX15I_Y"
    }
    #sneding photo for upload
    Cloudinary::Uploader.upload("screenshot.png", auth)
  end
end
