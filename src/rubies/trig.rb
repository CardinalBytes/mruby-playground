class Point2D
	def initialize(x, y)
		@x, @y = x, y
	end

	def x(value)
		@x = value
	end

	def y(value)
		@y = value
	end

	def to_s
		"< x: %.4f, y: %.4f >" % [@x, @y]
	end
end

class Trig
	def self.trans_point(p, radius, deg)
		p.x(radius * Math.cos(deg))
		p.y(radius * Math.sin(deg))
	end

	def self.soft_dtor(deg)
		return deg * Math::PI / 180.0
	end
	
	def self.soft_rtod(deg)
		return deg * 180.0 / Math::PI
	end
end