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

class Arg
  attr_reader :name
  attr_reader :value
  def initialize(name, value)
    @name = name
    @value = value
  end
end

class Desc
  
  attr_accessor :class_name
  attr_accessor :required_args
  attr_accessor :optional_args
  
  def initialize
    @class_name = nil
    @required_args = []
    @optional_args = []
  end

end

class Generator

  def initialize
    @known_classes = {}
  end

  def generate_preamble(out)
    out.puts <<-END
require 'fox16'

module Fox

END
    out.puts(DATA.read)
  end

  def generate_class_initializer(desc)
    argument_names = desc.optional_args.map { |arg| arg.name }
    defaults_hash = desc.optional_args.map { |arg| ":#{arg.name} => #{arg.value}"}
    defaults_hash = "{ #{defaults_hash.join(', ')} }"
    required_args = desc.required_args.join(", ")
    optional_args = desc.optional_args.map { |arg| "params[:#{arg.name}]"}
    optional_args = optional_args.join(", ")
    buffer = ""
    buffer << "  class #{desc.class_name}\n"
    buffer << "    alias old_initialize initialize\n"
    buffer << "    def initialize(#{required_args}#{desc.required_args.length > 0 ? ', ' : ''}*args, &blk)\n"
    buffer << "      argument_names = %w{#{argument_names.join(' ')}}\n"
    buffer << "      default_params = #{defaults_hash}\n"
    buffer << "      params = {}\n"
    buffer << "      params = args.pop if args.last.is_a? Hash\n"
    buffer << "      args.each_with_index { |e, i| params[argument_names[i].intern] = e }\n"
    if desc.optional_args.any? { |arg| arg.name == "padLeft" }
    buffer << "      if params.key? :padding\n"
    buffer << "        value = params.delete(:padding)\n"
    buffer << "        [:padLeft, :padRight, :padTop, :padBottom].each { |s| params[s] ||= value }\n"
    buffer << "      end\n"
    end
    buffer << "      params.keys.each { |key| raise ArgumentError, \"Unrecognized parameter \#{key}\" unless default_params.keys.include?(key) }\n"
    buffer << "      params = default_params.merge(params)\n"
    buffer << "      old_initialize(#{required_args}#{(desc.required_args.length > 0) && (desc.optional_args.length > 0) ? ', ' : ''}#{optional_args}, &blk)\n"
    buffer << "    end\n"
    buffer << "  end\n\n"
    buffer
  end
  
  def go(filenames, output_filename)
    out = File.new(output_filename, "w")
    descriptions = []
    filenames.each { |filename| descriptions += scan_for_descriptions(filename) }
    generate_preamble(out)
    descriptions.each do |desc|
      out.puts generate_class_initializer(desc) if desc.optional_args.length > 0
    end
    generate_closing(out)
  end
  
  def generate_closing(out)
    out.puts "end"
  end
  
  def scan_for_descriptions(filename)
    desc = nil
    descriptions = []
    IO.foreach(filename) do |str|
      if str =~ /^  class\s*(\w+).*$/
        desc = Desc.new
        desc.class_name = $1
      elsif str =~ /def initialize\((.*)\)/
#       args = $1.split(',').map { |x| x.strip }
        args = $1.split(', ').map { |x| x.strip }
        args.each do |arg|
          if arg =~ /(.*)=(.*)/
            desc.optional_args << Arg.new($1, $2)
          elsif
            desc.required_args << arg
          end
        end
        if @known_classes.has_key? desc.class_name
          warn "Overloaded initialize method for class: #{desc.class_name}"
        end
        @known_classes[desc.class_name] = 1
      elsif str =~ /^  end/
        descriptions << desc unless skip?(desc.class_name)
        desc = nil
      end
    end
    descriptions
  end
  
  def skip?(name)
    %w{FX4Splitter FXCursor FXDCWindow FXExtentd FXExtentf FXFont FXGLCanvas FXGLShape FXGLViewer FXDockBar FXMenuBar FXToolBar FXQuatd FXQuatf FXRanged FXRangef FXRecentFiles FXRectangle FXRegion FXSize FXSphered FXSpheref FXSplitter FXWindow}.include? name
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

