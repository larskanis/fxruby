=begin
Generate replacement initialize() methods that use keyword-argument style
hash arguments instead of positional arguments.

Known problems (due to overloaded constructors):

* FXCursor
* FXQuat{d,f}
* FXRange{d,f}
* FXRecentFiles
* FXRectangle
* FXSphere{d,f}

=end

CLASSES_TO_SKIP = %w{FX4Splitter FXCursor FXDCWindow FXExtentd FXExtentf FXFont FXGLCanvas FXGLShape FXGLViewer FXDockBar FXMenuBar FXToolBar FXQuatd FXQuatf FXRanged FXRangef FXRecentFiles FXRectangle FXRegion FXSize FXSphered FXSpheref FXSplitter FXVec2d FXVec2f FXVec3d FXVec3f FXVec4d FXVec4f FXWindow}

class Arg
  attr_reader :name
  attr_reader :value

  def initialize(name, value)
    @name = name
    @value = value
  end
end

class MethodDescription
  attr_accessor :method_name
  attr_accessor :required_args
  attr_accessor :optional_args

  def initialize
    @method_name = nil
    @required_args = []
    @optional_args = []
  end

  def generate_alias
    "    alias old_#{method_name} #{method_name}\n"
  end

  def generate_body
    argument_names = optional_args.map { |arg| arg.name }
    defaults_hash = optional_args.map { |arg| ":#{arg.name} => #{arg.value}"}
    defaults_hash = "{ #{defaults_hash.join(', ')} }"
    required = required_args.join(", ")
    optional = optional_args.map { |arg| "params[:#{arg.name}]"}
    optional = optional.join(", ")
    buffer = ""
    buffer << "    def #{method_name}(#{required}#{required_args.length > 0 ? ', ' : ''}*args#{expects_block? ? ', &blk' : ''})\n"
    buffer << "      argument_names = %w{#{argument_names.join(' ')}}\n"
    buffer << "      default_params = #{defaults_hash}\n"
    buffer << "      params = {}\n"
    buffer << "      params = args.pop if args.last.is_a? Hash\n"
    buffer << "      args.each_with_index { |e, i| params[argument_names[i].intern] = e }\n"
    if optional_args.any? { |arg| arg.name == "padLeft" }
      buffer << "      if params.key? :padding\n"
      buffer << "        value = params.delete(:padding)\n"
      buffer << "        [:padLeft, :padRight, :padTop, :padBottom].each { |s| params[s] ||= value }\n"
      buffer << "      end\n"
    end
    buffer << "      params.keys.each { |key| raise ArgumentError, \"Unrecognized parameter \#{key}\" unless default_params.keys.include?(key) }\n"
    buffer << "      params = default_params.merge(params)\n"
    buffer << "      old_#{method_name}(#{required}#{(required_args.length > 0) && (optional_args.length > 0) ? ', ' : ''}#{optional}#{expects_block? ? ', &blk' : ''})\n"
    buffer << "    end\n"
    buffer
  end

  def expects_block?
    method_name == "initialize"
  end
end

class ClassDescription
  attr_accessor :class_name
  attr_accessor :method_descriptions

  def initialize
    @class_name = nil
    @method_descriptions = []
  end

  def generate_class_initializer
    buffer = ""
    buffer << "  class #{class_name}\n"
    method_descriptions.each do |method_description|
      buffer << method_description.generate_alias
      buffer << method_description.generate_body
    end
    buffer << "  end\n\n"
    buffer
  end

  def has_methods_with_optional_arguments?
    method_descriptions.each do |m|
      return true if m.optional_args.length > 0
    end
    false
  end
end

class Generator

  def initialize
    @known_classes = {}
  end

  def generate_preamble(out)
    out.puts <<-END
old_verbose = $VERBOSE; $VERBOSE = nil

module Fox

END
    out.puts(DATA.read)
  end

  def go(filenames, output_filename)
    out = File.new(output_filename, "w")
    class_descriptions = []
    filenames.each { |filename| class_descriptions += scan_for_descriptions(filename) }
    generate_preamble(out)
    class_descriptions.each do |class_description|
      out.puts class_description.generate_class_initializer if class_description.has_methods_with_optional_arguments?
    end
    generate_closing(out)
  end

  def generate_closing(out)
    out.puts "end"
    out.puts ""
    out.puts "$VERBOSE = old_verbose"
  end

  def scan_for_descriptions(filename)
    class_description = nil
    class_descriptions = []
    IO.foreach(filename) do |str|
      if str =~ /^  class\s*(\w+).*$/
        class_description = ClassDescription.new
        class_description.class_name = $1
      elsif str =~ /def (initialize|findText)\((.*)\)/
        method_description = MethodDescription.new
        method_description.method_name = $1
#       args = $2.split(',').map { |x| x.strip }
        args = $2.split(', ').map { |x| x.strip }
        args.each do |arg|
          if arg =~ /(.*)=(.*)/
            method_description.optional_args << Arg.new($1, $2)
          elsif
            method_description.required_args << arg
          end
        end
        if @known_classes.has_key? class_description.class_name
          warn "Overloaded initialize method for class: #{class_description.class_name}"
        end
        @known_classes[class_description.class_name] = 1
        class_description.method_descriptions << method_description
      elsif str =~ /^  end/
        class_descriptions << class_description unless skip?(class_description.class_name)
        class_description = nil
      end
    end
    class_descriptions
  end

  def skip?(name)
    CLASSES_TO_SKIP.include? name
  end

end

if __FILE__ == $0
  Generator.new.go(Dir.glob('rdoc-sources/*.rb'), 'lib/fox16/kwargs.rb')
end

__END__

  class FX4Splitter
    alias old_initialize initialize
    def initialize(p, *args, &blk)
      argument_names = %w{opts x y width height}
      default_params = { :opts => FOURSPLITTER_NORMAL, :x => 0, :y => 0, :width => 0, :height => 0 }
      params = {}
      params = args.pop if args.last.is_a? Hash
      if args.length > 0 && (args.first.nil? || args.first.is_a?(FXObject))
        tgt, sel = args[0], args[1]
        args.each_with_index { |e, i| params[argument_names[i-2].intern] = e if i >= 2 }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, tgt, sel, params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      else
        args.each_with_index { |e, i| params[argument_names[i].intern] = e }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      end
    end
  end

  class FXDockBar
    alias old_initialize initialize
    def initialize(p, *args, &blk)
      argument_names = %w{opts x y width height padLeft padRight padTop padBottom hSpacing vSpacing}
      default_params = { :opts => LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X, :x => 0, :y => 0, :width => 0, :height => 0, :padLeft => 3, :padRight => 3, :padTop => 2, :padBottom => 2, :hSpacing => DEFAULT_SPACING, :vSpacing => DEFAULT_SPACING }
      params = {}
      params = args.pop if args.last.is_a? Hash
      if args.length > 0 && (args.first.nil? || args.first.is_a?(FXComposite))
        q = args[0]
        args.each_with_index { |e, i| params[argument_names[i-1].intern] = e if i >= 1 }
        if params.key? :padding
          value = params.delete(:padding)
          [:padLeft, :padRight, :padTop, :padBottom].each { |s| params[s] ||= value }
        end
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, q, params[:opts], params[:x], params[:y], params[:width], params[:height], params[:padLeft], params[:padRight], params[:padTop], params[:padBottom], params[:hSpacing], params[:vSpacing], &blk)
      else
        args.each_with_index { |e, i| params[argument_names[i].intern] = e }
        if params.key? :padding
          value = params.delete(:padding)
          [:padLeft, :padRight, :padTop, :padBottom].each { |s| params[s] ||= value }
        end
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, params[:opts], params[:x], params[:y], params[:width], params[:height], params[:padLeft], params[:padRight], params[:padTop], params[:padBottom], params[:hSpacing], params[:vSpacing], &blk)
      end
    end
  end

  class FXFont

    alias old_initialize initialize

    def initialize(a, arg1, *args, &blk)
      if args.length > 0
        face, size = arg1, args[0]
        argument_names = %w{weight slant encoding setWidth hints}
        default_params = { :weight => FXFont::Normal, :slant => FXFont::Straight, :encoding => FONTENCODING_DEFAULT, :setWidth => FXFont::NonExpanded, :hints => 0 }
        params = {}
        params = args.pop if args.last.is_a? Hash
        args.each_with_index { |e, i| params[argument_names[i-1].intern] = e if i >= 1 }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(a, face, size, params[:weight], params[:slant], params[:encoding], params[:setWidth], params[:hints], &blk)
      else
        old_initialize(a, arg1, &blk)
      end
    end

    class << self
      alias old_listFonts listFonts
    end

    def FXFont.listFonts(face, *args)
      argument_names = %w{weight slant setWidth encoding hints}
      default_params = { :weight => 0, :slant => 0, :setWidth => 0, :encoding => 0, :hints => 0 }
      params = {}
      params = args.pop if args.last.is_a? Hash
      args.each_with_index { |e, i| params[argument_names[i].intern] = e }
      params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
      params = default_params.merge(params)
      old_listFonts(face, params[:weight], params[:slant], params[:setWidth], params[:encoding], params[:hints])
    end

  end

  class FXGLCanvas
    alias old_initialize initialize
    def initialize(parent, vis, *args, &blk)
      argument_names = %w{target selector opts x y width height}
      default_params = { :target => nil, :selector => 0, :opts => 0, :x => 0, :y => 0, :width => 0, :height => 0 }
      params = {}
      params = args.pop if args.last.is_a? Hash
      if args.length > 0 && (args[0].is_a?(FXGLCanvas))
        sharegroup = args[0]
        args.each_with_index { |e, i| params[argument_names[i-1].intern] = e if i >= 1 }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(parent, vis, sharegroup, params[:target], params[:selector], params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      else
        args.each_with_index { |e, i| params[argument_names[i].intern] = e }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(parent, vis, params[:target], params[:selector], params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      end
    end
  end

  class FXGLViewer
    alias old_initialize initialize
    def initialize(parent, vis, *args, &blk)
      argument_names = %w{target selector opts x y width height}
      default_params = { :target => nil, :selector => 0, :opts => 0, :x => 0, :y => 0, :width => 0, :height => 0 }
      params = {}
      params = args.pop if args.last.is_a? Hash
      if args.length > 0 && (args[0].is_a?(FXGLViewer))
        sharegroup = args[0]
        args.each_with_index { |e, i| params[argument_names[i-1].intern] = e if i >= 1 }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(parent, vis, sharegroup, params[:target], params[:selector], params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      else
        args.each_with_index { |e, i| params[argument_names[i].intern] = e }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(parent, vis, params[:target], params[:selector], params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      end
    end
  end

  class FXMenuBar
    alias old_initialize initialize
    def initialize(p, *args, &blk)
      argument_names = %w{opts x y width height padLeft padRight padTop padBottom hSpacing vSpacing}
      default_params = { :opts => LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X, :x => 0, :y => 0, :width => 0, :height => 0, :padLeft => 3, :padRight => 3, :padTop => 2, :padBottom => 2, :hSpacing => DEFAULT_SPACING, :vSpacing => DEFAULT_SPACING }
      params = {}
      params = args.pop if args.last.is_a? Hash
      if args.length > 0 && (args[0].nil? || args[0].is_a?(FXComposite))
        q = args[0]
        args.each_with_index { |e, i| params[argument_names[i-1].intern] = e if i >= 1 }
        if params.key? :padding
          value = params.delete(:padding)
          [:padLeft, :padRight, :padTop, :padBottom].each { |s| params[s] ||= value }
        end
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, q, params[:opts], params[:x], params[:y], params[:width], params[:height], params[:padLeft], params[:padRight], params[:padTop], params[:padBottom], params[:hSpacing], params[:vSpacing], &blk)
      else
        args.each_with_index { |e, i| params[argument_names[i].intern] = e }
        if params.key? :padding
          value = params.delete(:padding)
          [:padLeft, :padRight, :padTop, :padBottom].each { |s| params[s] ||= value }
        end
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, params[:opts], params[:x], params[:y], params[:width], params[:height], params[:padLeft], params[:padRight], params[:padTop], params[:padBottom], params[:hSpacing], params[:vSpacing], &blk)
      end
    end
  end

  class FXSplitter
    alias old_initialize initialize
    def initialize(p, *args, &blk)
      argument_names = %w{opts x y width height}
      default_params = { :opts => SPLITTER_NORMAL, :x => 0, :y => 0, :width => 0, :height => 0 }
      params = {}
      params = args.pop if args.last.is_a? Hash
      if args.length > 0 && (args.first.nil? || args.first.is_a?(FXObject))
        tgt, sel = args[0], args[1]
        args.each_with_index { |e, i| params[argument_names[i-2].intern] = e if i >= 2 }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, tgt, sel, params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      else
        args.each_with_index { |e, i| params[argument_names[i].intern] = e }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      end
    end
  end

  class FXToolBar
    alias old_initialize initialize
    def initialize(p, *args, &blk)
      argument_names = %w{opts x y width height padLeft padRight padTop padBottom hSpacing vSpacing}
      default_params = { :opts => LAYOUT_TOP|LAYOUT_LEFT|LAYOUT_FILL_X, :x => 0, :y => 0, :width => 0, :height => 0, :padLeft => 3, :padRight => 3, :padTop => 2, :padBottom => 2, :hSpacing => DEFAULT_SPACING, :vSpacing => DEFAULT_SPACING }
      params = {}
      params = args.pop if args.last.is_a? Hash
      if args.length > 0 && (args[0].nil? || args[0].is_a?(FXComposite))
        q = args[0]
        args.each_with_index { |e, i| params[argument_names[i-1].intern] = e if i >= 1 }
        if params.key? :padding
          value = params.delete(:padding)
          [:padLeft, :padRight, :padTop, :padBottom].each { |s| params[s] ||= value }
        end
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, q, params[:opts], params[:x], params[:y], params[:width], params[:height], params[:padLeft], params[:padRight], params[:padTop], params[:padBottom], params[:hSpacing], params[:vSpacing], &blk)
      else
        args.each_with_index { |e, i| params[argument_names[i].intern] = e }
        if params.key? :padding
          value = params.delete(:padding)
          [:padLeft, :padRight, :padTop, :padBottom].each { |s| params[s] ||= value }
        end
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, params[:opts], params[:x], params[:y], params[:width], params[:height], params[:padLeft], params[:padRight], params[:padTop], params[:padBottom], params[:hSpacing], params[:vSpacing], &blk)
      end
    end
  end

  class FXWindow
    alias old_initialize initialize
    def initialize(p, *args, &blk)
      if p.is_a? FXApp
        old_initialize(p, *args, &blk)
      else
        argument_names = %w{opts x y width height}
        default_params = { :opts => 0, :x => 0, :y => 0, :width => 0, :height => 0 }
        params = {}
        params = args.pop if args.last.is_a? Hash
        args.each_with_index { |e, i| params[argument_names[i].intern] = e }
        params.keys.each { |key| raise ArgumentError, "Unrecognized parameter #{key}" unless default_params.keys.include?(key) }
        params = default_params.merge(params)
        old_initialize(p, params[:opts], params[:x], params[:y], params[:width], params[:height], &blk)
      end
    end
  end

