puts "STD_PATH is #{STD_PATH} and CR_BPATH #{CR_BPAT}"
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

require_relative "game_demo_require"