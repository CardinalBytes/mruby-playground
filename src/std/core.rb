# This leverages ruby to wrap calls to inner functions to load a module

def require(mod_name)
    rvm_load "#{STD_PATH}/#{mod_name}"
end

# this acts mostly like the require_relative from regular ruby
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