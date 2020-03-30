# This leverages ruby to wrap calls to inner functions to load a module

def require(mod_name)
    internals_load "#{STD_PATH}/#{mod_name}"
end

# this acts mostly like the require_relative from regular ruby
def require_relative(fname)
  if File.extname(fname) == ""
    if File.exist?("#{fname}.mrb")
      interals_load fname
    end
  elsif File.extname(fname) == ".mrb" and File.exist?(fname)
    interals_load fname
  else
    raise StandardError.new "file #{fname}.mrb not found"
  end
end
