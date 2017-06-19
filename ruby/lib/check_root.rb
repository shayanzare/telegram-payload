#!/usr/bin/ruby

class Check_Root
  def check_root
    isRoot = Process.uid.zero?
  end
end
