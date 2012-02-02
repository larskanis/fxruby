module Fox
  class FXPoint
    # Point x-coordinate [Integer]
    attr_accessor :x

    # Point y-coordinate [Integer]
    attr_accessor :y

    # Initialize from an FXSize instance
    def initialize(size); end

    # Initialize from another FXPoint instance
    def initialize(point); end

    # Initialize from x and y coordinates
    def initialize(x=0, y=0); end
  end
end

