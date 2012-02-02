require 'test/unit'

require 'fox16'

class TC_FXRangef < Test::Unit::TestCase
  include Fox


  WIDTH, HEIGHT, DEPTH = 2, 4, 6

  def setup
    @range = FXRangef.new(0, WIDTH, 0, HEIGHT, 0, DEPTH)
  end

  def test_lower_is_a_vector
    assert_instance_of(FXVec3f, @range.lower)
  end

  def test_upper_is_a_vector
    assert_instance_of(FXVec3f, @range.upper)
  end

  def test_width
    assert_equal(@range.width, WIDTH)
  end

  def test_height
    assert_equal(@range.height, HEIGHT)
  end

  def test_depth
    assert_equal(@range.depth, DEPTH)
  end

  def test_longest
    assert_equal([@range.width, @range.height, @range.depth].max, @range.longest)
  end

  def test_shortest
    assert_equal([@range.width, @range.height, @range.depth].min, @range.shortest)
  end
end
