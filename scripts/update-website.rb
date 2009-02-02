#
# This script uses John Carter's RExpect module for Ruby; the original is
# available at:
#
#     http://www.rubygarden.org/ruby?RExpect
#

require 'pty'
require 'thread'
require 'timeout'

$expect_verbose = false

Thread.abort_on_exception = true

class RExpect
  attr_reader :pid

  def RExpect.spawn(cmd)
    mutex = Mutex.new
    mutex.synchronize do
      
      resultResource = ConditionVariable.new
      result = nil
      Thread.new do
        pid = nil
        mutex.synchronize do
          inf, outf, pid, fileName = PTY.spawn(cmd)
          result = RExpect.new( inf, outf, pid, fileName)
          resultResource.signal
        end
        result.inputData
      end
      
      resultResource.wait( mutex)
      return result
    end
  end
  
  def log(a)
    @log.puts "#{caller(1)[0]}:#{a}" unless @log.nil?
  end

  def initialize(inf,outf,pid,fileName)
    @inf,@outf,@pid,@fileName = inf,outf,pid,fileName
    if $expect_verbose then
      @log = File.open( "rexpect.log.#{@pid}", "w")
      @log.sync = true
    else
      @log = nil
    end

    @outf.sync=true
    @buffer = ''
    @mutex = Mutex.new
    @bufferResource = ConditionVariable.new
  end

  def wait
    Process.waitpid(@pid,0)
  rescue
  end

  def kill
    kill( "SIGTERM", @pid)
    wait
  end

  def inputData
    while true
      data = @inf.sysread( 65536)
      @mutex.synchronize do
        log( "BUFFER:#{@buffer}\nNEWDATA:#{data}" )
        @buffer << data
        if !@e_pat.nil? && @buffer =~ @e_pat then
          @result = [@buffer,$1,$2,$3,$4,$5,$6,$7,$8,$9]
          @buffer = $'
          log( "Buffer matched#{@e_pat.source}")
          @e_pat = nil
          @bufferResource.signal
        end
      end
    end
  rescue SystemCallError, EOFError => details
    log( details)
    log( details.backtrace.join("\n"))
    @mutex.synchronize do
      @bufferResource.signal
    end
  rescue RuntimeError => details
    raise details if details.to_s !~ /Child_changed/
  ensure
    @log.close
  end
  
  def expect(pat,time_out=5)
    @result = nil

    @mutex.synchronize do
      case pat
      when String
        @e_pat = Regexp.new(Regexp.quote(pat))
      when Regexp
        @e_pat = pat
      end
      log( @e_pat.source)
      
      if @buffer =~ @e_pat then
        @result = [@buffer,$1,$2,$3,$4,$5,$6,$7,$8,$9]
        @buffer = $'
        log( "Existing buffer matched#{@e_pat.source}")
        @e_pat = nil
        return @result
      end
      timeout( time_out) do
        @bufferResource.wait( @mutex)
        raise EOFError if @result.nil?
      end
    end
    return @result
  end

  def puts(str)
    log( str)
    @outf.puts str
  end 

end

if __FILE__ == $0
  PAUSE = 60  
  session = RExpect.spawn("ssh -l lyle fxruby.sourceforge.net")
  session.expect("-bash-2.05b$", PAUSE)
  session.puts("cd fxruby-htdocs/1.2")
  session.expect("-bash-2.05b$", PAUSE)
  session.puts("tar xzf ../doc.tar.gz")
  session.expect("-bash-2.05b$", PAUSE)
  session.puts("tar xzf ../examples.tar.gz")
  session.expect("-bash-2.05b$", PAUSE)
# session.puts("tar xzf web.tar.gz")
# session.expect("-bash-2.05b$", PAUSE)
  session.puts("exit")
end
