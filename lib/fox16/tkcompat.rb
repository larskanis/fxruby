#
# The purpose of this library is to provide a few new methods
# similar to those used by Ruby/Tk.
#

module Fox
  class FXObject
    def bind(str, pr)
      tokens = str.split('-')
      modifiers = []
      type = nil
      detail = nil
      case type
        when "Button"
        when "ButtonPress"
          connect(SEL_LEFTBUTTONPRESS, pr)
        when "ButtonRelease"
          connect(SEL_LEFTBUTTONRELEASE, pr)
        when "Configure"
          connect(SEL_CONFIGURE, pr)
        when "Deactivate"
        when "Destroy"
          connect(SEL_DESTROY, pr)
        when "Enter"
          connect(SEL_ENTER, pr)
        when "Expose"
          connect(SEL_PAINT, pr)
        when "FocusIn"
          connect(SEL_FOCUSIN, pr)
        when "FocusOut"
          connect(SEL_FOCUSOUT, pr)
        when "Key"
        when "KeyPress"
          connect(SEL_KEYPRESS, pr)
        when "KeyRelease"
          connect(SEL_KEYRELEASE, pr)
        when "Leave"
          connect(SEL_LEAVE, pr)
        when "Motion"
          connect(SEL_MOTION, pr)
        when "Map"
          connect(SEL_MAP, pr)
        when "Unmap"
          connect(SEL_UNMAP, pr)
        when "Activate"
        when "Circulate"
        when "Colormap"
        when "Gravity"
        when "Property"
        when "Reparent"
        when "Visibility"
          raise NotImplementedError
      end
    end
  end
end
