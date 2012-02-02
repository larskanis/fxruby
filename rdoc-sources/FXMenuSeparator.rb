module Fox
  #
  # The menu separator is a simple decorative groove used to delineate items in a
  # popup menu.  When a target/message is given, the menu separator is usually
  # connected to an instance of the recent files class using the ID_ANYFILES
  # message.  This automatically hides the menu separator when no files are listed
  # in the recent files section.  Another possible target is the MDI client using
  # the +ID_MDI_ANY+ message: in this case, the menu separator will be automatically
  # hidden when no MDI child windows are present.
  #
  class FXMenuSeparator < FXWindow

    # Highlight color [FXColor]
    attr_accessor :hiliteColor

    # Shadow color [FXColor]
    attr_accessor :shadowColor

    #
    # Construct a menu separator
    #
    def initialize(parent, target=nil, selector=0, opts=0) # :yields: theMenuSeparator
    end
  end
end

