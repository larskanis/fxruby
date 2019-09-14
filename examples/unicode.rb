#!/usr/bin/env ruby
# -*- encoding: UTF-8 -*-

require 'fox16'

# Pass UTF-8 encoded Unicode strings to FXRuby.
label = "Les enfants vont \u00E0 l'\u00E9cole.\nLa boulang\u00E8re vend-elle le pain en ao\u00FBt?"

Fox::FXApp.new("Unicode Example", "FoxTest") do |app|
  main = Fox::FXMainWindow.new(app, "Unicode Text", nil, nil, Fox::DECOR_ALL)
  Fox::FXLabel.new(main, label)
  app.create
  main.show(Fox::PLACEMENT_SCREEN)
  app.run
end
