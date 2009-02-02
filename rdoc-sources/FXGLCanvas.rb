module Fox
  #
  # FXGLCanvas is an area drawn by another object.
  #
  # ==== GLCanvas Options
  #
  # +GLCANVAS_OWN_CONTEXT+:: Context is owned
  #
  class FXGLCanvas < FXCanvas
    
    # Context [FXGLContext]
    attr_accessor :context
    
    #
    # Construct a GL canvas with its private context and private display lists.
    #
    def initialize(parent, vis, target=nil, selector=0, opts=0, x=0, y=0, width=0, height=0) # :yields: theGLCanvas
    end
  
    #
    # Construct a GL canvas with its private context but shared display lists.
    #
    def initialize(parent, vis, share, target=nil, selector=0, opts=0, x=0, y=0, width=0, height=0) # :yields: theGLCanvas
    end
    
    #
    # Construct a GL canvas with a shared context.
    #
    def initialize(parent, ctx, target=nil, selector=0, opts=0, x=0, y=0, width=0, height=0) # :yields: theGLCanvas
    end
    
    # Return +true+ if sharing display lists.
    def shared? ; end

    # Change the context
    def setContext(ctx, owned=false); end
    
    # Make OpenGL context current prior to performing OpenGL commands
    def makeCurrent(); end
  
    # Make OpenGL context non-current
    def makeNonCurrent(); end

    # Return +true+ if this canvas' context is the current context.
    def current? ; end

    # Swap front and back buffer
    def swapBuffers(); end
  end
end

