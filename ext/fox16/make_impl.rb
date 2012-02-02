#!/bin/env ruby

$special_stubclasses = ["FXGLSHAPE", "FXICONITEM", "FXTABLE", "FXTABLEITEM", "FXTREEITEM"]

class Processor
  def initialize
    @inside_class = false
  end

  def inside_class?
    @inside_class
  end

  def getBaseClassName(klass)
    klass.sub(/FXRb/, "FX")
  end

  def start_class(classname, baseclass)
  end

  def end_class
  end

  def process(filename)
    begin
      File.open(filename, "rb") do |f|
	@inside_class = false
	f.readlines.each do |line|
	  if inside_class?
	    if line =~ /^  \};/
	      @inside_class = false
	      end_class
	    else
	      process_line(line)
	    end
	  else
	    if line =~ /^class/
	      classname = line.split.at(1)
	      start_class(classname, getBaseClassName(classname))
	      @inside_class = true
	    end
	  end
	end
      end
    ensure
      @inside_class = false
    end
  end
end

class MyProcessor < Processor
  def initialize(fcpp, finc)
    @fcpp = fcpp
    @finc = finc
    @classname = nil
    @baseclass = nil
  end

  def start_class(classname, baseclass)
    @classname = classname
    @baseclass = baseclass
    if classname == "FXRbScintilla"
      @fcpp.puts "#ifdef WITH_FXSCINTILLA\n\n"
      @finc.puts "#ifdef WITH_FXSCINTILLA\n\n"
    end
    @fcpp.printf("/* Start stub implementations for class %s */\n", classname)
    @finc.printf("/* Start stub declarations for class %s */\n", classname)
  end

  def implement_overrides(filename)
    stubclass = filename.gsub('"', '').sub("FXRb", "FX")
    stubclass = stubclass.sub(/Virtuals\.h/, "").upcase
    unless $special_stubclasses.include? stubclass
      @fcpp.printf("IMPLEMENT_%s_STUBS(%s)\n", stubclass, @classname)
    else
      @fcpp.printf("IMPLEMENT_%s_STUBS(%s,%s)\n", stubclass, @classname, @baseclass)
    end
  end

  def implement_stubs(filename)
    stubclass = filename.gsub('"', '').sub("FXRb", "FX")
    stubclass = stubclass.sub(/Virtuals\.h/, "").upcase
    unless $special_stubclasses.include? stubclass
      @finc.printf("DECLARE_%s_STUBS(%s)\n", stubclass, @baseclass)
    else
      @finc.printf("DECLARE_%s_STUBS(%s,%s)\n", stubclass, @baseclass, @classname)
    end
  end

  def process_line(line)
    if line =~ /^#include/
      words = line.split()
      incfile = words[1]
      implement_overrides(incfile)
      implement_stubs(incfile)
    end
  end

  def end_class
    if @classname == "FXRbScintilla"
      @fcpp.puts "\n#endif"
      @finc.puts "\n#endif"
    end
    @fcpp.puts ""
    @finc.puts ""
    @classname = nil
    @baseclass = nil
  end
end

fcpp = File.new('impl.cpp', 'wb')
finc = File.new('./include/inlinestubs.h', 'wb')
fcpp.puts '#include "FXRbCommon.h"'
Dir.glob("./include/FX*.h").sort.each do |file|
  unless file =~ /BitmapView/
    MyProcessor.new(fcpp, finc).process(file)
  end
end
finc.close
fcpp.close

