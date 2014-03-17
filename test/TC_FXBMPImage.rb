require 'fox16'
require 'test/unit'
require 'testcase'

class TC_FXBMPImage < Fox::TestCase
  include Fox

  def setup
    super(self.class.name)
  end

  def test_fileExt
    assert_equal("bmp", FXBMPImage.fileExt)
  end

  def test_image_from_pixel_data
    img = FXBMPImage.new app
    img.setPixels "rgbaRGBA", 0, 1, 2
    bmp_data = FXMemoryStream.open(FXStreamSave, nil) do |outfile|
      img.savePixels(outfile)
      outfile.takeBuffer
    end
    assert_not_equal "rgbaRGBA", bmp_data

    img2 = FXBMPImage.new app, bmp_data
    assert_equal "rgbaRGBA", img2.pixel_string
  end
end
