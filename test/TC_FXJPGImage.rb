require 'fox16'
require 'test/unit'
require 'testcase'
require 'openssl'

class TC_FXJPGImage < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end

  def test_save_with_thread
    w, h = 4000, 3000
    img_data = OpenSSL::Random.random_bytes(w) * h * 4

    count = 0
    th = Thread.new do
      loop do
        count += 1
      end
    end

    img = FXJPGImage.new(app)
    img.setPixels( img_data, 0, w, h )

    jpeg_data = FXMemoryStream.open(FXStreamSave, nil) do |outfile|
      img.savePixels(outfile)
      outfile.takeBuffer
    end

    assert_operator(count, :>=, 500000)
    assert_operator(jpeg_data.bytesize, :>=, 1000)

    count = 0
    img = FXJPGImage.new(app)
    FXMemoryStream.open(FXStreamLoad, jpeg_data) do |infile|
      img.loadPixels(infile)
    end

    th.kill

    assert_equal 4000, img.width
    assert_equal 3000, img.height
    assert_operator(count, :>=, 500000)
  end
end
