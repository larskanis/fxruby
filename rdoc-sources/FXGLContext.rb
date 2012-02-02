module Fox
  #
  # OpenGL context
  #
  class FXGLContext < FXId

    # Shared context for this context (if any) [FXGLContext]
    attr_accessor :shared

    # The GL visual [FXGLVisual]
    attr_accessor :visual

    # Active drawable for this context [FXDrawable]
    attr_reader :drawable

		#
		# Construct an GL Context with given GL Visual. Optionally
    # share a display list with another GL Context _shr_.
    #
    # ==== Parameters:
    #
    # +app+::     a reference to the application instance [FXApp]
    # +vis+::     a reference to the GL visual [FXGLVisual]
    # +shr+::     a reference to the GLContext with which this one shares its display lists
    #
    def initialize(app, vis, shr=nil) # :yields: theGLContext
    end

    # Make this OpenGL context current prior to performing OpenGL commands.
    def begin(drawable); end

    # Make this OpenGL context non-current.
    def end(); end

    # Swap front and back buffer
    def swapBuffers(); end

    # Return +true+ if this context supports double-buffering.
    def doubleBuffer? ; end

    # Return +true+ if this context supports stereo buffer.
    def stereoBuffer? ; end

    # Return +true+ if this window's context is current
    def current?; end
  end
end

