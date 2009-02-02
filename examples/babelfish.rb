#!/usr/bin/env ruby

require 'fox16'
require 'fox16/kwargs'
require 'soap/rpc/driver'

include Fox

TRANSLATIONS = {
  "English to French" => "en_fr",
  "English to German" => "en_de",
  "English to Italian" => "en_it",
  "English to Japanese" => "en_jp",
  "English to Korean" => "en_kr",
  "English to Portugese" => "en_pt",
  "English to Spanish" => "en_es",
  "French to English" => "fr_en",
  "German to English" => "de_en",
  "Italian to English" => "it_en",
  "Japanese to English" => "jp_en",
  "Korean to English" => "kr_en",
  "Portugese to English" => "pt_en",
  "Spanish to English" => "es_en",
  "Russian to English" => "ru_en",
  "German to French" => "de_fr",
  "French to German" => "fr_de"
}

class Babelfish < FXMainWindow

  def initialize(app)
    # Invoke base class initialize first
    super(app, "Babelfish", nil, nil, DECOR_ALL,
      0, 0, 600, 400, 0, 0)

    # Initialize the SOAP driver
    @drv = SOAP::RPC::Driver.new('http://services.xmethods.net/perl/soaplite.cgi', 'urn:xmethodsBabelFish')
    @drv.add_rpc_method_with_soapaction('BabelFish',
      'urn:xmethodsBabelFish#BabelFish', 'translationmode', 'sourcedata')

    # Controls area along the bottom
    controlsFrame = FXHorizontalFrame.new(self,
      LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X)
    FXLabel.new(controlsFrame, "Translate from:")
    @transModeCombo = FXComboBox.new(controlsFrame, 15, :opts => COMBOBOX_STATIC|FRAME_SUNKEN|FRAME_THICK)
    @transModeCombo.numVisible = 6
    TRANSLATIONS.keys.each do |key|
      @transModeCombo.appendItem(key, TRANSLATIONS[key])
    end
    btn = FXButton.new(controlsFrame, "Translate", :opts => BUTTON_NORMAL|LAYOUT_SIDE_RIGHT)
    btn.connect(SEL_COMMAND) do
      transMode = @transModeCombo.getItemData(@transModeCombo.currentItem)
      getApp().beginWaitCursor() do
        @translatedText.text = @drv.BabelFish(transMode, @sourceText.text)
      end
    end

    mainFrame = FXVerticalFrame.new(self,
      LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y|PACK_UNIFORM_HEIGHT)

    # Source text area in a sunken frame
    topFrame = FXVerticalFrame.new(mainFrame, LAYOUT_FILL_X|LAYOUT_FILL_Y)
    FXLabel.new(topFrame, "Source Text:", :opts => LAYOUT_FILL_X)
    sunkenFrame = FXHorizontalFrame.new(topFrame,
      FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y)
    @sourceText = FXText.new(sunkenFrame, :opts => LAYOUT_FILL_X|LAYOUT_FILL_Y)

    # Translated text output
    bottomFrame = FXVerticalFrame.new(mainFrame, LAYOUT_FILL_X|LAYOUT_FILL_Y)
    FXLabel.new(bottomFrame, "Translated text:", nil, LAYOUT_FILL_X)
    sunkenFrame = FXHorizontalFrame.new(bottomFrame,
      FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y)
    @translatedText = FXText.new(sunkenFrame, :opts => TEXT_READONLY|LAYOUT_FILL_X|LAYOUT_FILL_Y)
  end
  
  def create
    super
    show(PLACEMENT_SCREEN)
  end
end

if __FILE__ == $0
  # Make application
  application = FXApp.new("Babelfish", "FoxTest")

  # Make window
  window = Babelfish.new(application)

  # Create it
  application.create

  # Run
  application.run
end
