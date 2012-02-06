module Fox
  #
  # The Canvas module defines a framework similar to that provided by Tk's Canvas
  # widget (and subsequent improvements, such as GNOME's Canvas and wxWindows'
  # Object Graphics Library).
  #
  # Links
  # =====
  #
  # Tk's Canvas Widget
  #     http://starship.python.net/crew/fredrik/tkmanual/canvas.html
  #     http://www.dci.clrc.ac.uk/Publications/Cookbook/chap4.html
  #
  # GNOME's Canvas Widget
  #     http://developer.gnome.org/doc/whitepapers/canvas/canvas.html
  #
  module Canvas

    class CanvasError < Exception
    end

    class Shape

      attr_accessor :x, :y, :foreground, :target, :selector

      def initialize(x, y)
        @enabled = true
        @visible = true
        @selected = false
        @draggable = false
        @x = x
        @y = y
        @foreground = FXRGB(0, 0, 0)
        @target = nil
        @selector = 0
      end

      # Return the bounding box for this shape
      def bounds
        FXRectangle.new(x, y, width, height)
      end

      # Hit test
      def hit?(xpos, ypos)
        (xpos >= x) && (xpos < x+width) && (ypos >= y) && (ypos < y+height)
      end

      # Move shape to specified position
      def move(x, y)
        @x, @y = x, y
      end

      # Resize shape to specified width and height
      def resize(w, h)
      end

      # Move and resize the shape
      def position(x, y, w, h)
        move(x, y)
        resize(w, h)
      end

      # Enable this shape
      def enable
        @enabled = true
      end

      # Disable this shape
      def disable
        @enabled = false
      end

      # Is this shape enabled?
      def enabled?
        @enabled
      end

      # Show this shape
      def show
        @visible = true
      end

      # Hide this shape
      def hide
        @visible = false
      end

      # Is this shape visible?
      def visible?
        @visible
      end

      # Select this shape
      def select
        @selected = true
      end

      # Deselect this shape
      def deselect
        @selected = false
      end

      # Is this shape selected?
      def selected?
        @selected
      end

      # Set this shape's draggability
      def draggable=(d)
        @draggable = d
      end

      # Is this shape draggable?
      def draggable?
        @draggable
      end

      # Draw this shape into the specificed device context
      def draw(dc)
      end

      # Draws outline
      def drawOutline(dc, x, y, w, h)
        points = []
        points << FXPoint.new(x - 0.5*w, y - 0.5*h)
        points << FXPoint.new(x + 0.5*w, y)
        points << FXPoint.new(x + 0.5*w, y + 0.5*h)
        points << FXPoint.new(x - 0.5*w, y + 0.5*h)
        points << points[0]
        dc.drawLines(points)
      end

      # Default: make 6 control points
      def makeControlPoints
      end
    end

    class ShapeGroup

      include Enumerable

      # Initialize this shape group
      def initialize
        @shapes = []
      end

      # Does the group contain this shape?
      def include?(shape)
        @shapes.include?(shape)
      end

      # Add a shape to this group
      def addShape(shape)
        @shapes << shape
      end

      # Remove a shape from this group
      def removeShape(shape)
        @shapes.remove(shape)
      end

      def each
        @shapes.each { |shape| yield shape }
      end

      def reverse_each
        @shapes.reverse_each { |shape| yield shape }
      end
    end

    class LineShape < Shape

      attr_accessor :lineWidth, :lineCap, :lineJoin, :lineStyle
      attr_accessor :x1, :y1, :x2, :y2

      def initialize(x1, y1, x2, y2)
        super(x1, y1)
        @x1, @y1, @x2, @y2 = x1, y1, x2, y2
        @lineWidth = 1
        @lineCap = CAP_NOT_LAST
        @lineJoin = JOIN_MITER
        @lineStyle = LINE_SOLID
      end

      def width
        0
      end

      def height
        0
      end

      def draw(dc)
        # Save old values
        oldForeground = dc.foreground
        oldLineWidth = dc.lineWidth
        oldLineCap = dc.lineCap
        oldLineJoin = dc.lineJoin
        oldLineStyle = dc.lineStyle

        # Set properties for this line
        dc.foreground = foreground
        dc.lineWidth = lineWidth
        dc.lineCap = lineCap
        dc.lineJoin = lineJoin
        dc.lineStyle = lineStyle

        # Draw the line
        dc.drawLine(x1, y1, x2, y2)

        # Restore old properties
        dc.lineWidth = oldLineWidth
        dc.lineCap = oldLineCap
        dc.lineJoin = oldLineJoin
        dc.lineStyle = oldLineStyle
        dc.foreground = oldForeground
      end
    end

    class RectangleShape < Shape

      attr_accessor :width, :height

      def initialize(x, y, w, h)
        super(x, y)
        @width = w
        @height = h
      end

      def draw(dc)
        oldForeground = dc.foreground
        dc.foreground = foreground
        dc.drawRectangle(x, y, width, height)
        dc.foreground = oldForeground
      end
    end

    class TextShape < RectangleShape

      attr_reader :font, :text

      def initialize(x, y, w, h, text=nil)
        super(x, y, w, h)
        @text = text
        @font = FXApp.instance.normalFont
      end

      def draw(dc)
        super(dc)
        oldForeground = dc.foreground
        oldTextFont = dc.font
        dc.font = @font
        dc.drawImageText(x, y, text)
        dc.font = oldTextFont if oldTextFont
        dc.foreground = oldForeground
      end
    end

    class CircleShape < Shape

      attr_accessor :radius

      def initialize(x, y, radius)
        super(x, y)
        @radius = radius
      end

      def width
        2*radius
      end

      def height
        2*radius
      end

      def draw(dc)
        oldForeground = dc.foreground
        oldLineWidth = dc.lineWidth
        dc.foreground = foreground
        dc.lineWidth = 5 if selected?
        dc.drawArc(x, y, width, height,      0, 64*180)
        dc.drawArc(x, y, width, height, 64*180, 64*360)
        dc.foreground = oldForeground
        dc.lineWidth = oldLineWidth
      end
    end

    class PolygonShape < Shape
    end

    class ImageShape < Shape

      attr_accessor :image

      def initialize(x, y, image)
        @image = image
      end

      def draw(dc)
        dc.drawImage(image)
      end
    end

    # Base class for canvas selection policies
    class SelectionPolicy
      def initialize(canvas)
        @canvas = canvas
      end

      def selectShape(shape, notify)
        unless shape.selected?
          shape.select
          @canvas.updateShape(shape)
          if notify && (@canvas.target != nil)
            @canvas.target.handle(@canvas, MKUINT(@canvas.message, SEL_SELECTED), shape)
          end
        end
      end

      def deselectShape(shape, notify)
        if shape.selected?
          shape.deselect
          @canvas.updateShape(shape)
          if notify && (@canvas.target != nil)
            @canvas.target.handle(@canvas, MKUINT(@canvas.message, SEL_DESELECTED), shape)
          end
        end
      end
    end

    # Single shape selected at one time
    class SingleSelectionPolicy < SelectionPolicy
      def initialize(canvas)
        super
      end

      def selectShape(shape, notify)
        unless shape.selected?
          @canvas.killSelection(notify)
        end
        super
      end
    end

    class ShapeCanvas < FXCanvas

      # Window state flags
      FLAG_SHOWN        = 0x00000001 # Is shown
      FLAG_ENABLED      = 0x00000002 # Able to receive input
      FLAG_UPDATE       = 0x00000004 # Is subject to GUI update
      FLAG_DROPTARGET   = 0x00000008 # Drop target
      FLAG_FOCUSED      = 0x00000010 # Has focus
      FLAG_DIRTY        = 0x00000020 # Needs layout
      FLAG_RECALC       = 0x00000040 # Needs recalculation
      FLAG_TIP          = 0x00000080 # Show tip
      FLAG_HELP         = 0x00000100 # Show help
      FLAG_DEFAULT      = 0x00000200 # Default widget
      FLAG_INITIAL      = 0x00000400 # Initial widget
      FLAG_SHELL        = 0x00000800 # Shell window
      FLAG_ACTIVE       = 0x00001000 # Window is active
      FLAG_PRESSED      = 0x00002000 # Button has been pressed
      FLAG_KEY          = 0x00004000 # Keyboard key pressed
      FLAG_CARET        = 0x00008000 # Caret is on
      FLAG_CHANGED      = 0x00010000 # Window data changed
      FLAG_LASSO        = 0x00020000 # Lasso mode
      FLAG_TRYDRAG      = 0x00040000 # Tentative drag mode
      FLAG_DODRAG       = 0x00080000 # Doing drag mode
      FLAG_SCROLLINSIDE = 0x00100000 # Scroll only when inside
      FLAG_SCROLLING    = 0x00200000 # Right mouse scrolling

      include Responder

      attr_accessor :scene

      def initialize(p, tgt=nil, sel=0, opts=FRAME_NORMAL, x=0, y=0, w=0, h=0)
        # Initialize base class
        super(p, tgt, sel, opts, x, y, w, h)

        # Start with an empty group
        @scene = ShapeGroup.new

        # Selection policy
        @selectionPolicy = SingleSelectionPolicy.new(self)

        @flags = 0

        # Map
        FXMAPFUNC(SEL_PAINT, 0, "onPaint")
        FXMAPFUNC(SEL_MOTION, 0, "onMotion")
        FXMAPFUNC(SEL_LEFTBUTTONPRESS, 0, "onLeftBtnPress")
        FXMAPFUNC(SEL_LEFTBUTTONRELEASE, 0, "onLeftBtnRelease")
        FXMAPFUNC(SEL_CLICKED,0,"onClicked")
        FXMAPFUNC(SEL_DOUBLECLICKED,0,"onDoubleClicked")
        FXMAPFUNC(SEL_TRIPLECLICKED,0,"onTripleClicked")
        FXMAPFUNC(SEL_COMMAND,0,"onCommand")
      end

      # Find the shape of the least depth containing this point
      def findShape(x, y)
        @scene.reverse_each do |shape|
          return shape if shape.hit?(x, y)
        end
        nil
      end

      # Repaint
      def updateShape(shape)
        if @scene.include?(shape)
          update
        else
          raise CanvasError
        end
      end

      # Enable one shape
      def enableShape(shape)
        if @scene.include?(shape)
          unless shape.enabled?
            shape.enable
            updateShape(shape)
          end
        else
          raise CanvasError
        end
      end

      # Disable one shape
      def disableShape(shape)
        if @scene.include?(shape)
          if shape.enabled?
            shape.disable
            updateShape(shape)
          end
        else
          raise CanvasError
        end
      end

      # Select one shape
      def selectShape(shape, notify=false)
        if @scene.include?(shape)
          @selectionPolicy.selectShape(shape, notify)
        else
          raise CanvasError
        end
      end

      # Deselect one shape
      def deselectShape(shape, notify=false)
        if @scene.include?(shape)
          @selectionPolicy.deselectShape(shape, notify)
        else
          raise CanvasError
        end
      end

      # Kill selection
      def killSelection(notify)
        changes = false
        @scene.each do |shape|
          if shape.selected?
            shape.deselect
            updateShape(shape)
            changes = true
            if notify && (target != nil)
              target.handle(self, MKUINT(message, SEL_DESELECTED), shape)
            end
          end
        end
        changes
      end

      # Paint
      def onPaint(sender, sel, evt)
        dc = FXDCWindow.new(self, evt)
        dc.foreground = backColor
        dc.fillRectangle(evt.rect.x, evt.rect.y, evt.rect.w, evt.rect.h)
        @scene.each do |shape|
          shape.draw(dc)
        end
        dc.end
        return 1
      end

      # Motion
      def onMotion(sender, sel, evt)
        # Drag and drop mode
        if (@flags & FLAG_DODRAG) != 0
          handle(self, MKUINT(0, SEL_DRAGGED), evt)
          return 1
        end

        # Tentative drag and drop
        if (@flags & FLAG_TRYDRAG) != 0
          if evt.moved?
            @flags &= ~FLAG_TRYDRAG
            if handle(this, MKUINT(0, SEL_BEGINDRAG), evt) != 0
              @flags |= FLAG_DODRAG
            end
          end
          return 1
        end
      end

      # Left button press
      def onLeftBtnPress(sender, sel, evt)
        handle(self, MKUINT(0, SEL_FOCUS_SELF), evt)
        if enabled?
          grab
          flags &= ~FLAG_UPDATE

          # Give target the first chance at handling this
          return 1 if target && (target.handle(self, MKUINT(message, SEL_LEFTBUTTONPRESS), evt) != 0)

          # Locate shape
          shape = findShape(evt.win_x, evt.win_y)

          # No shape here
          if shape.nil?
            return 1
          end

          # Change current shape
          @currentShape = shape

          # Change item selection
          if shape.enabled? && !shape.selected?
            selectShape(shape, true)
          end

          # Are we dragging?
          if shape.selected? && shape.draggable?
            flags |= FLAG_TRYDRAG
          end

          flags |= FLAG_PRESSED
          return 1
        end
        return 0
      end

      # Left button release
      def onLeftBtnRelease(sender, sel, evt)
        flg = @flags
        if enabled?
          ungrab
          @flags |= FLAG_UPDATE
          @flags &= ~(FLAG_PRESSED|FLAG_TRYDRAG|FLAG_LASSO|FLAG_DODRAG)

          # First chance callback
          return 1 if target && target.handle(self, MKUINT(message, SEL_LEFTBUTTONRELEASE), evt) != 0

          # Was dragging
          if (flg & FLAG_DODRAG) != 0
            handle(self, MKUINT(0, SEL_ENDDRAG), evt)
            return 1
          end

          # Must have pressed
          if (flg & FLAG_PRESSED) != 0
            # Change selection
            if @currentShape && @currentShape.enabled?
              deselectShape(@currentShape, true)
            end

            # Generate clicked callbacks
            if evt.click_count == 1
              handle(self, MKUINT(0, SEL_CLICKED), @currentShape)
            elsif evt.click_count == 2
              handle(self, MKUINT(0, SEL_DOUBLECLICKED), @currentShape)
            elseif evt.click_count == 3
              handle(self, MKUINT(0, SEL_TRIPLECLICKED), @currentShape)
            end

            # Generate command callback only when clicked on item
            if @currentShape && @currentShape.enabled?
              handle(self, MKUINT(0, SEL_COMMAND), @currentShape)
            end
            return 1
          end
          return 0
        end
      end

      # Command message
      def onCommand(sender, sel, ptr)
        return target && target.handle(self, MKUINT(message, SEL_COMMAND), ptr)
      end

      # Clicked on canvas
      def onClicked(sender, sel, ptr)
        return target && target.handle(self, MKUINT(message, SEL_CLICKED), ptr)
      end

      # Double-clicked on canvas
      def onDoubleClicked(sender, sel, ptr)
        return target && target.handle(self, MKUINT(message, SEL_DOUBLECLICKED), ptr)
      end

      # Triple-clicked on canvas
      def onTripleClicked(sender, sel, ptr)
        return target && target.handle(self, MKUINT(message, SEL_TRIPLECLICKED), ptr)
      end
    end
  end
end
