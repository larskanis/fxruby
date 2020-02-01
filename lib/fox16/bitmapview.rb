module Fox
  #
  # The FXBitmapView widget displays a scrollable view of a bitmap.
  #
  # === Bitmap alignment styles
  #
  # +BITMAPVIEW_NORMAL+::	Normal mode is centered
  # +BITMAPVIEW_CENTER_X+::	Centered horizontally
  # +BITMAPVIEW_LEFT+::		Left-aligned
  # +BITMAPVIEW_RIGHT+::	Right-aligned
  # +BITMAPVIEW_CENTER_Y+::	Centered vertically
  # +BITMAPVIEW_TOP+::		Top-aligned
  # +BITMAPVIEW_BOTTOM+::	Bottom-aligned
  #
  # === Events
  #
  # +SEL_RIGHTBUTTONPRESS+::	sent when the right mouse button goes down; the message data is an FXEvent instance.
  # +SEL_RIGHTBUTTONRELEASE+::	sent when the right mouse button goes up; the message data is an FXEvent instance.
  #
  class FXBitmapView < FXScrollArea

    # Bitmap alignment styles
    BITMAPVIEW_NORMAL    = 0          # Normal mode is centered
    BITMAPVIEW_CENTER_X  = 0          # Centered horizontally
    BITMAPVIEW_LEFT      = 0x00100000 # Left-aligned
    BITMAPVIEW_RIGHT     = 0x00200000 # Right-aligned
    BITMAPVIEW_CENTER_Y  = 0,         # Centered vertically
    BITMAPVIEW_TOP       = 0x00400000 # Top-aligned
    BITMAPVIEW_BOTTOM    = 0x00800000 # Bottom-aligned

    #
    # Return an initialized FXBitmapView instance.
    #
    def initialize(p, bmp=nil, tgt=nil, sel=0, opts=0, x=0, y=0, w=0, h=0) # :yields: theBitmapView
      super(p, opts, x, y, w, h)
      self.flags |= FLAG_ENABLED
      self.target = tgt
      self.message = sel
      @bitmap = bmp
      @onColor = Fox.FXRGB(0, 0, 0)
      @offColor = backColor
      @grabx = 0
      @graby = 0
    end

    def create
      super
      bitmap.create unless bitmap.nil?
    end

    def detach
      super
      bitmap.detach unless bitmap.nil?
    end

    def canFocus
      true
    end

    def getContentWidth
      bitmap.nil? ? 1 : bitmap.width
    end

    def getContentHeight
      bitmap.nil? ? 1 : bitmap.height
    end

    def layout
      super
      update
      self.flags &= ~FLAG_DIRTY
    end

    # Handle expose (paint) event
    def onPaint(sender, sel, event)
      FXDCWindow.new(self, event) do |dc|
        unless bitmap.nil?
          ww = bitmap.width
          hh = bitmap.height
          xx = pos_x
          yy = pos_y
          if ww < viewport_w
            if (options & BITMAPVIEW_LEFT) != 0
              xx = 0
            elsif (options & BITMAPVIEW_RIGHT) != 0
              xx = viewport_w - ww
            else
              xx = (viewport_w - ww)/2
            end
          end
          if hh < viewport_h
            if (options & BITMAPVIEW_TOP) != 0
              yy = 0
            elsif (options & BITMAPVIEW_BOTTOM) != 0
              yy = viewport_h - hh
            else
              yy = (viewport_h - hh)/2
            end
          end
          dc.foreground = onColor
          dc.background = offColor
          dc.drawBitmap(bitmap, xx, yy)
          dc.foreground = backColor
          xl = xx; xr = xx + ww
          yt = yy; yb = yy + hh
          xl = 0 if (xl < 0)
          xr = viewport_w if (xr > viewport_w)
          yt = 0 if (yt < 0)
          yb = viewport_h if (yb > viewport_h)
          dc.fillRectangle(0, 0, xr, yt)
          dc.fillRectangle(0, yt, xl, viewport_h - yt)
          dc.fillRectangle(xr, 0, viewport_w - xr, yb)
          dc.fillRectangle(xl, yb, viewport_w - xl, viewport_h - yb)
        else
          dc.foreground = backColor
          dc.fillRectangle(0, 0, width, height)
        end
      end
    end

    # Handle right mouse button press
    def onRightBtnPress(sender, sel, ev)
      self.flags &= ~FLAG_TIP
      handle(self, Fox.FXSEL(SEL_FOCUS_SELF, 0), ev)
      if enabled?
        grab
        if target && target.handle(self, Fox.FXSEL(SEL_RIGHTBUTTONPRESS, message), ev) != 0
          return 1
        end
        self.flags &= ~FLAG_UPDATE
        self.flags |= FLAG_PRESSED|FLAG_SCROLLING
        @grabx = ev.win_x - pos_x
        @graby = ev.win_y - pos_y
        return 1
      end
      return 0
    end

    # Handle right mouse button release
    def onRightBtnRelease(sender, sel, ev)
      if enabled?
        ungrab
        self.flags &= ~(FLAG_PRESSED|FLAG_SCROLLING)
        self.flags |= FLAG_UPDATE
        if target && target.handle(self, Fox.FXSEL(SEL_RIGHTBUTTONPRESS, message), ev) != 0
          return 1
        end
        return 1
      end
      return 0
    end

    # Handle real or simulated mouse motion
    def onMotion(sender, sel, ev)
      if (flags & FLAG_SCROLLING) != 0
        setPosition(ev.win_x - @grabx, ev.win_y - @graby)
        return 1
      end
      return 0
    end

    #
    # Set the bitmap for this FXBitmapView, where _bmp_ is either +nil+ or
    # a reference to an FXBitmap instance.
    #
    def bitmap=(bmp)
      @bitmap = bmp
      recalc
      update
    end

    #
    # Return a reference to the bitmap (an FXBitmap instance) for this FXBitmapView,
    # or +nil+ if no bitmap has been set.
    #
    def bitmap; @bitmap; end

    # Set the color used for the "on" bits in the bitmap.
    def onColor=(clr)
      if clr != onColor
        @onColor = clr
        update
      end
    end

    # Return the color used for the "on" bits in the bitmap.
    def onColor; @onColor; end

    # Set the color used for the "off" bits in the bitmap.
    def offColor=(clr)
      if clr != offColor
        @offColor = clr
        update
      end
    end

    # Return the color used for the "off" bits in the bitmap.
    def offColor; @offColor; end

    #
    # Set the current alignment for the bitmap inside the FXBitmapView,
    # where _mode_ is some combination of the bitmap alignment flags
    # listed above.
    #
    def alignment=(mode)
      opts = (options & ~(BITMAPVIEW_LEFT|BITMAPVIEW_RIGHT|BITMAPVIEW_TOP|BITMAPVIEW_BOTTOM)) |
             (mode & (BITMAPVIEW_LEFT|BITMAPVIEW_RIGHT|BITMAPVIEW_TOP|BITMAPVIEW_BOTTOM))
      if options != opts
        @options = opts
        update
      end
    end

    #
    # Return the current alignment for the bitmap inside the
    # FXBitmapView.
    #
    def alignment
      options & (BITMAPVIEW_LEFT|BITMAPVIEW_RIGHT|BITMAPVIEW_TOP|BITMAPVIEW_BOTTOM)
    end
  end
end
