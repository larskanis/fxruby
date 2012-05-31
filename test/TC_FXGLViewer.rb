require 'test/unit'
require 'fox16'
require 'testcase'

class TC_FXGLViewer < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
    vis = FXGLVisual.new(app, VISUAL_DOUBLEBUFFER)
    @viewer = FXGLViewer.new(mainWindow, vis)
  end

  def test_supported
    assert FXGLVisual.supported?(app)
  end

  def test_nil_app_raises_argument_error
    assert_raise(ArgumentError){ FXGLVisual.supported?(nil) }
  end

=begin
  def test_readPixels
    pixels = @viewer.readPixels(0, 0, @viewer.width, @viewer.height)
    assert(pixels)
    assert_equal(3*@viewer.width*@viewer.height, pixels.size)
  end
=end
end
