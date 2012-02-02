module Fox
  #
  # An FXVisual instance describes the pixel format for a drawable (i.e. an FXDrawable instance).
  #
  # === Construction options for FXVisual
  #
  # +VISUAL_DEFAULT+::		    Default visual
  # +VISUAL_MONO+::	          Must be monochrome visual
  # +VISUAL_BEST+::		        Best (deepest) visual
  # +VISUAL_INDEX+::	        Palette visual
  # +VISUAL_GRAY+::	          Gray scale visual
  # +VISUAL_COLOR+::	        Must be true color visual
  # +VISUAL_OWNCOLORMAP+::	  Allocate private colormap
  # +VISUAL_FORCE+::          Force given visual/format
  # +VISUAL_DOUBLE_BUFFER+::	Double-buffered [FXGLVisual]
  # +VISUAL_STEREO+::		      Stereo [FXGLVisual]
  # +VISUAL_NO_ACCEL+::		    No hardware acceleration [for broken h/w]
  # +VISUAL_SWAP_COPY+::	    Buffer swap by copying (for FXGLVisual)
  #
  class FXVisual < FXId

    Unknown = 0 # Undetermined visual type
    Mono = 1    # Monochrome 1 bit/pixel
    Gray = 2    # Gray scale color
    Index = 3   # Index color
    Color = 4   # True color

    # Visual construction flags [Integer]
    attr_accessor :flags

    # Hints [Integer]
    attr_accessor :hints

    # Visual depth, i.e. number of significant bits in color representation [Integer]
    attr_reader :depth

    # Number of colors [Integer]
    attr_reader :numColors

    # Number of bits of red [Integer]
    attr_reader :numRed

    # Number of bits of green [Integer]
    attr_reader :numGreen

    # Number of bits of blue [Integer]
    attr_reader :numBlue

    # Maximum number of colors [Integer]
    attr_accessor :maxColors

    #
    # The visual type, one of +Mono+, +Gray+, +Index+ or +Color+.
    # The visual type may also be +Unknown+ before the visual is actually
    # created.
    #
    attr_reader :visualType

    #
    # Return an initialized FXVisual instance.
    #
    # ==== Parameters:
    #
    # +a+::	    an application instance [FXApp]
    # +flgs+::	visual construction flags [Integer]
    # +hnt+::	  requested visual depth, in bits [Integer]
    #
    def initialize(a, flgs=VISUAL_DEFAULT, hnt=32); end

    #
    # Get device pixel value for color value _clr_.
    #
    def getPixel(clr); end

    #
    # Get color value for device pixel value _pix_.
    #
    def getColor(pix); end
  end
end

