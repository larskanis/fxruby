require 'opengl'
require 'glu'

module Fox

  HANDLE_SIZE = 4.0

  #
  # OpenGL point object
  #
  class FXGLPoint < FXGLObject
    include OpenGL

    # Point position, in model coordinates (a 3-element array)
    attr_accessor :pos

    #
    # Returns an initialized FXGLPoint instance.
    # If no arguments are passed to #new, the initial point position is
    # (0.0, 0.0, 0.0). You can specify a different initial position by
    # passing in the x, y and z coordinates individually:
    #
    #     aPoint = FXGLPoint.new(x, y, z)
    #
    # or as a 3-element array:
    #
    #     aPoint = FXGLPoint.new([x, y, z])
    #
    def initialize(*args)
      super()
      if args.length == 0
        @pos = [0.0, 0.0, 0.0]
      elsif args.length == 3
        @pos = [args[0], args[1], args[2]]
      else
        @pos = args[0]
      end
    end

    #
    # Return the bounding box (an FXRangef instance) for this point.
    #
    def bounds
      FXRangef.new(@pos[0], @pos[0], @pos[1], @pos[1], @pos[2], @pos[2])
    end

    #
    # Draw this point into _viewer_ (an FXGLViewer instance).
    #
    def draw(viewer)
      glColor3d(0.0, 0.0, 1.0)
      glPointSize(HANDLE_SIZE)
      glBegin(GL_POINTS)
      glVertex3d(*@pos)
      glEnd()
    end

    #
    # Perform hit test for this point in _viewer_ (an FXGLViewer instance).
    #
    def hit(viewer)
      glBegin(GL_POINTS)
      glVertex3d(*@pos)
      glEnd()
    end
  end

  #
  # OpenGL line object
  #
  class FXGLLine < FXGLObject
    include OpenGL

    # Starting point for line [FXGLPoint]
    attr_accessor :fm

    # End point for line [FXGLPoint]
    attr_accessor :to

    #
    # Return an initialized FXGLLine instance.
    #
    # If no arguments are passed to #new, the initial starting and ending
    # points for the line are (-0.5, 0.0, 0.0) and (0.5, 0.0, 0.0), respectively.
    # You can specify different initial start and end points by passing in
    # another FXGLLine instance from which to copy the start and end point
    # values, e.g.
    #
    #     aLine = FXGLLine.new(anotherLine)
    #
    # or by passing in the x, y and z coordinates individually:
    #
    #     aLine = FXGLLine.new(x0, y0, z0, x1, y1, z1)
    #
    def initialize(*args)
      super()
      if args.length == 0
        @fm = FXGLPoint.new(-0.5, 0.0, 0.0)
        @to = FXGLPoint.new( 0.5, 0.0, 0.0)
      elsif args.length == 1
        @fm = args[0].fm
        @to = args[0].to
      else
        @fm = FXGLPoint.new(args[0], args[1], args[2])
        @to = FXGLPoint.new(args[3], args[4], args[5])
      end
    end

    #
    # Return the bounding box (an FXRangef instance) for this line.
    #
    def bounds
      FXRangef.new([@fm.pos[0], @to.pos[0]].min,
                  [@fm.pos[0], @to.pos[0]].max,
                  [@fm.pos[1], @to.pos[1]].min,
                  [@fm.pos[1], @to.pos[1]].max,
                  [@fm.pos[2], @to.pos[2]].min,
                  [@fm.pos[2], @to.pos[2]].max)
    end

    #
    # Draw this line into _viewer_ (an FXGLViewer instance).
    #
    def draw(viewer)
      glColor3d(1.0, 0.0, 0.0)
      glPointSize(HANDLE_SIZE)
      glBegin(GL_LINES)
      glVertex3d(*@fm.pos)
      glVertex3d(*@to.pos)
      glEnd()
    end

    #
    # Perform hit-test for this line in _viewer_ (an FXGLViewer instance).
    #
    def hit(viewer)
      glBegin(GL_LINES)
      glVertex3d(*@fm.pos)
      glVertex3d(*@to.pos)
      glEnd()
    end
  end

  #
  # OpenGL cube object
  #
  class FXGLCube < FXGLShape
    include OpenGL

    # Cube width [Float]
    attr_accessor :width

    # Cube height [Float]
    attr_accessor :height

    # Cube depth [Float]
    attr_accessor :depth

    #
    # Return an initialized FXGLCube instance.
    #
    # One option is to initialize the cube with a specified origin,
    # width, height and depth:
    #
    #     aCube = FXGLCube.new(x, y, z, w, h, d)
    #
    # If left unspecified, the width (_w_), height (_h_) and depth (_d_)
    # default to 1.0.
    #
    # Another option is to initialize the cube with a specified origin,
    # width, height, depth and material:
    #
    #     aCube = FXGLCube.new(x, y, z, w, h, d, material)
    #
    # where the _material_ is an FXMaterial instance.
    #
    def initialize(*args)
      if args.length == 7
        super(args[0], args[1], args[2], SHADING_SMOOTH|STYLE_SURFACE,
              args[6], args[6])
      else
        super(args[0], args[1], args[2], SHADING_SMOOTH|STYLE_SURFACE)
      end
      @width = args[3] ? args[3] : 1.0
      @height = args[4] ? args[4] : 1.0
      @depth = args[5] ? args[5] : 1.0
      setRange(FXRangef.new(-0.5*@width, 0.5*@width,
                          -0.5*@height, 0.5*@height,
                          -0.5*@depth, 0.5*@depth))
    end

    #
    # Draws this cube into _viewer_ (an FXGLViewer instance).
    #
    def drawshape(viewer)
      xmin, xmax = -0.5*@width, 0.5*@width
      ymin, ymax = -0.5*@height, 0.5*@height
      zmin, zmax = -0.5*@depth, 0.5*@depth

      # Draw low face
      glBegin(GL_TRIANGLE_STRIP)
        glNormal3d(0.0, 0.0, -1.0)
        glVertex3d(xmin, ymin, zmin)
        glVertex3d(xmin, ymax, zmin)
        glVertex3d(xmax, ymin, zmin)
        glVertex3d(xmax, ymax, zmin)
      glEnd()

      # Draw east face
      glBegin(GL_TRIANGLE_STRIP)
        glNormal3d(1.0, 0.0, 0.0)
        glVertex3d(xmax, ymin, zmin)
        glVertex3d(xmax, ymax, zmin)
        glVertex3d(xmax, ymin, zmax)
        glVertex3d(xmax, ymax, zmax)
      glEnd()

      # Draw high face
      glBegin(GL_TRIANGLE_STRIP)
        glNormal3d(0.0, 0.0, 1.0)
        glVertex3d(xmax, ymin, zmax)
        glVertex3d(xmax, ymax, zmax)
        glVertex3d(xmin, ymin, zmax)
        glVertex3d(xmin, ymax, zmax)
      glEnd()

      # Draw west face
      glBegin(GL_TRIANGLE_STRIP)
        glNormal3d(-1.0, 0.0, 0.0)
        glVertex3d(xmin, ymin, zmax)
        glVertex3d(xmin, ymax, zmax)
        glVertex3d(xmin, ymin, zmin)
        glVertex3d(xmin, ymax, zmin)
      glEnd()

      # Draw north face
      glBegin(GL_TRIANGLE_STRIP)
        glNormal3d(0.0, 1.0, 0.0)
        glVertex3d(xmin, ymax, zmin)
        glVertex3d(xmin, ymax, zmax)
        glVertex3d(xmax, ymax, zmin)
        glVertex3d(xmax, ymax, zmax)
      glEnd()

      # Draw south face
      glBegin(GL_TRIANGLE_STRIP)
        glNormal3d(0.0, -1.0, 0.0)
        glVertex3d(xmin, ymin, zmax)
        glVertex3d(xmin, ymin, zmin)
        glVertex3d(xmax, ymin, zmax)
        glVertex3d(xmax, ymin, zmin)
      glEnd()
    end
  end

  #
  # OpenGL cone object
  #
  class FXGLCone < FXGLShape
    include OpenGL
    include GLU

    # Cone fidelity
    SLICES_NUMBER = 20
    STACKS_NUMBER = 20
    LOOPS = 4

    # Cone height [Float]
    attr_accessor :height

    # Cone base radius [Float]
    attr_accessor :radius

    # Number of slices (default is 20) [Integer]
    attr_accessor :slices

    # Number of stacks (default is 20) [Integer]
    attr_accessor :stacks

    # Number of loops (default is 4) [Integer]
    attr_accessor :loops

    #
    # Returns an initialized FXGLCone instance.
    #
    # One option is to initialize the cone with a specified origin,
    # height and radius:
    #
    #     aCone = FXGLCone.new(x, y, z, h, r)
    #
    # If left unspecified, the height (_h_) and radius (_r_) default to 1.0.
    #
    # Another option is to initialize the cone with a specified origin,
    # height, radius and material:
    #
    #     aCone = FXGLCone.new(x, y, z, h, r, material)
    #
    # where the _material_ is an FXMaterial instance.
    #
    def initialize(*args)
      if args.length == 5
        super(args[0], args[1], args[2], SHADING_SMOOTH|STYLE_SURFACE)
      elsif args.length == 6
        super(args[0], args[1], args[2], SHADING_SMOOTH|STYLE_SURFACE,
              args[5], args[5])
      end
      @height = args[3] ? args[3] : 1.0
      @radius = args[4] ? args[4] : 1.0
      @slices = SLICES_NUMBER
      @stacks = STACKS_NUMBER
      @loops  = LOOPS
      setRange(FXRangef.new(-@radius, @radius, 0, @height, -@radius, @radius))
    end

    #
    # Draw this cone into _viewer_ (an FXGLViewer instance).
    #
    def drawshape(viewer)
      quad = gluNewQuadric()
      gluQuadricDrawStyle(quad, GLU_FILL)
      glPushMatrix()
      glRotated(-90, 1, 0, 0)
      gluCylinder(quad, @radius, 0, @height, @slices, @stacks)
      gluQuadricOrientation(quad, GLU_INSIDE)
      gluDisk(quad, 0, @radius, @slices, @loops)
      gluDeleteQuadric(quad)
      glPopMatrix()
    end
  end

  #
  # OpenGL cylinder object
  #
  class FXGLCylinder < FXGLShape
    include OpenGL
    include GLU

    # Cylinder fidelity
    SLICES_NUMBER = 20
    STACKS_NUMBER = 20
    LOOPS = 4

    # Cylinder height [Float]
    attr_accessor :height

    # Cylinder radius [Float]
    attr_accessor :radius

    # Number of slices (default is 20) [Integer]
    attr_accessor :slices

    # Number of stacks (default is 20) [Integer]
    attr_accessor :stacks

    # Number of loops (default is 4) [Integer]
    attr_accessor :loops

    #
    # Returns an initialized FXGLCylinder instance.
    #
    # One option is to initialize the cylinder with a specified origin,
    # height and radius:
    #
    #     aCylinder = FXGLCylinder.new(x, y, z, h, r)
    #
    # If left unspecified, the height (_h_) and radius (_r_) default to 1.0.
    #
    # Another option is to initialize the cylinder with a specified origin,
    # height, radius and material:
    #
    #     aCylinder = FXGLCylinder.new(x, y, z, h, r, material)
    #
    # where the _material_ is an FXMaterial instance.
    #
    def initialize(*args)
      if args.length == 5
        super(args[0], args[1], args[2], SHADING_SMOOTH|STYLE_SURFACE)
      else
        super(args[0], args[1], args[2], SHADING_SMOOTH|STYLE_SURFACE,
              args[5], args[5])
      end
      @height = args[3] ? args[3] : 1.0
      @radius = args[4] ? args[4] : 1.0
      @slices = SLICES_NUMBER
      @stacks = STACKS_NUMBER
      @loops  = LOOPS
      setRange(FXRangef.new(-@radius, @radius, 0, @height, -@radius, @radius))
    end

    #
    # Draw this cylinder into _viewer_ (an FXGLViewer instance).
    #
    def drawshape(viewer)
      quad = gluNewQuadric()
      gluQuadricDrawStyle(quad, GLU_FILL)
      glPushMatrix()
      glRotated(-90, 1, 0, 0)
      gluCylinder(quad, @radius, @radius, @height, @slices, @stacks)
      gluQuadricOrientation(quad, GLU_INSIDE)
      gluDisk(quad, 0, @radius, @slices, @loops)
      glTranslated(0, 0, @height)
      gluQuadricOrientation(quad, GLU_OUTSIDE)
      gluDisk(quad, 0, @radius, @slices, @loops)
      glPopMatrix()
      gluDeleteQuadric(quad)
    end
  end

  #
  # OpenGL sphere object
  #
  class FXGLSphere < FXGLShape
    include OpenGL
    include GLU

    # Sphere fidelity
    SLICES_NUMBER = 20
    STACKS_NUMBER = 20

    # Sphere radius [Float]
    attr_accessor :radius

    # Number of slices (default is 20) [Integer]
    attr_accessor :slices

    # Number of stacks (default is 20) [Integer]
    attr_accessor :stacks

    #
    # Returns an initialized FXGLSphere instance.
    #
    # One option is to initialize the sphere with a specified origin and
    # radius:
    #
    #     aSphere = FXGLSphere.new(x, y, z, r)
    #
    # If left unspecified, the radius (_r_) defaults to 1.0.
    #
    # Another option is to initialize the sphere with a specified origin,
    # radius and material:
    #
    #     aSphere = FXGLSphere.new(x, y, z, r, material)
    #
    # where the _material_ is an FXMaterial instance.
    #
    def initialize(*args)
      if args.length == 4
        super(args[0], args[1], args[2], SHADING_SMOOTH|STYLE_SURFACE)
      else
        super(args[0], args[1], args[2], SHADING_SMOOTH|STYLE_SURFACE,
        args[4], args[4])
      end
      @radius = args[3] ? args[3] : 1.0
      @slices = SLICES_NUMBER
      @stacks = STACKS_NUMBER
      setRange(FXRangef.new(-@radius, @radius, -@radius, @radius, -@radius, @radius))
    end

    #
    # Draw this sphere into _viewer_ (an FXGLViewer instance).
    #
    def drawshape(viewer)
      quad = gluNewQuadric()
      gluQuadricDrawStyle(quad, GLU_FILL)
      gluSphere(quad, @radius, @slices, @stacks)
      gluDeleteQuadric(quad)
    end
  end
end
