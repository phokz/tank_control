#!/usr/bin/env ruby

File.read('tank.html').split("\n").each do |line|
  puts '    "' + line.gsub('"','\\"') + '\n"'
end
