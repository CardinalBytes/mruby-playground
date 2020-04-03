puts "STD_PATH is #{STD_PATH} and CR_BPATH #{CR_BPAT}, PI: #{Math::PI}, #{Math::E}"
INative.cout "test of importing\n"

def require_relative(fname)
  if File.extname(fname) == ""
    if File.exist?("#{CR_BPAT}/#{fname}.mrb")
      if not INative.load("#{CR_BPAT}/#{fname}.mrb")
        raise StandardError.new "Problem in native function"
      end
    end
  elsif File.extname(fname) == ".mrb" and File.exist?(fname)
    if not INative.load("#{CR_BPAT}/#{fname}")
      raise StandardError.new "Problem in native function"
    end
  else
    raise StandardError.new "file #{fname}.mrb not found"
  end
end

# require_relative "game_demo_require"
begin
  require_relative "trig"
rescue StandardError
  puts "import failed"
end

p = Point2D.new 0.0, 0.0
for i in 0..359
	Trig.trans_point(p, 1, Trig.soft_dtor(i))
	puts "#{p} at #{i}"
end