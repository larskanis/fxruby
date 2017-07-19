require 'test/unit'
require 'fox16'
require 'testcase'
require 'socket'

class TC_FXApp < Test::Unit::TestCase
  include Fox

  def test_exception_for_second_app
    assert_raise RuntimeError do
      FXApp.new
    end
  end
end

class TC_FXApp2 < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end

  def test_nil_window_raises_argument_error
    assert_raise(ArgumentError){ app.runPopup(nil) }
  end

  def check_events(pipe_rd, pipe_wr)
    app.addInput(pipe_wr, INPUT_WRITE, app, FXApp::ID_QUIT)
    app.run
    app.removeInput(pipe_wr, INPUT_WRITE)

    app.addInput(pipe_rd, INPUT_READ, app, FXApp::ID_QUIT)
    2.times do
      data_sent = false
      app.addTimeout(1) do
        data_sent = true
        pipe_wr.write " "
      end
      app.run
      assert data_sent, "the read input event shouldn't fire before some data is available"
      assert " ", pipe_rd.read(1)
    end
    app.removeInput(pipe_rd, INPUT_READ)
    pipe_wr.close
    pipe_rd.close unless pipe_rd.closed?
  end

  def test_addInput_on_pipe
    pend "addInput on IO.pipe object isn't supported on Windows" if RUBY_PLATFORM=~/mingw|mswin/i
    check_events(*IO.pipe)
  end

  def test_addInput_on_socket_accept
    s = TCPServer.open 'localhost', 0
    app.addInput(s, INPUT_READ, app, FXApp::ID_QUIT)
    2.times do
      pipe_wr = nil
      app.addTimeout(1) do
        pipe_wr = TCPSocket.open 'localhost', s.addr[1]
      end
      app.run
      assert pipe_wr, "the read input event shouldn't fire before client connection happens"
      s.accept.close
    end
    app.removeInput(s, INPUT_READ)
    s.close
  end

  def test_addInput_on_socket
    s = TCPServer.open 'localhost', 0
    pipe_wr = TCPSocket.open 'localhost', s.addr[1]
    pipe_rd = s.accept
    s.close

    check_events pipe_rd, pipe_wr
  end

  def test_addInput_on_popen
    pend "addInput on IO.popen object isn't supported on Windows" if RUBY_PLATFORM=~/mingw|mswin/i
    pipe_rdwr = IO.popen("cat", "r+")
    check_events pipe_rdwr, pipe_rdwr
  end

  def test_runOnUiThread
    count = 0
    thread = nil
    Thread.new do
      10.times do |idx|
        app.runOnUiThread do
          count += 1
          thread = Thread.current
          app.stop if idx == 9
        end
        sleep 0.001
      end
    end
    app.run

    assert_equal Thread.current, thread
    assert_equal 10, count
  end

  def test_runOnUiThread_same_thread
    count = 0
    app.addTimeout(1) do
      10.times do |idx|
        app.runOnUiThread do
          count += 1
          app.stop if idx == 9
        end
        sleep 0.001
      end
    end
    app.run

    assert_equal 10, count
  end
end
