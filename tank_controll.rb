#!/usr/bin/env ruby

require 'typhoeus'
IP = '192.168.43.26'.freeze

def command(x, y)
  url = "http://#{IP}/set.php"
  req = Typhoeus::Request.new(url, method: :post, params: {
                                mode: 'G91',
                                unit: 'G21',
                                x: "X#{x}",
                                y: "Y#{y}"
                              })
  req.run
end

def straight
  command(1, 1)
end

def left
  command(-1, 1)
end

def right
  command(1, -1)
end

def dance
  left; left; right; right; left; right
end

dance

