#!/usr/bin/env ruby
ENV["RAILS_ENV"] = "production" # I want that the exe runs 
automatically in the production mode 
APP_PATH = File.expand_path('../../config/application', __FILE__) 
require File.expand_path('../../config/boot', __FILE__) 
# copied from: railties/lib/rails/commands.rb: 
require 'rails/commands/server' 
Rails::Server.new.tap { |server| 
  require APP_PATH 
  Dir.chdir(Rails.application.root) 
  server.start 
} 
