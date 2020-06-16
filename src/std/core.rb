# This leverages ruby to wrap calls to inner functions to load a module

def require(mod_name)
  if File.extname(fname) == ""
    Internals.CLoader("#{STD_PATH}/#{mod_name}.mrb")
  else
    Internals.CLoader("#{STD_PATH}/#{mod_name}")
  end
end

# this acts mostly like the require_relative from regular ruby
def require_relative(fname)
  if File.extname(fname) == ""
    if File.exist?("#{CR_BPAT}/#{fname}.mrb")
      Internals.CLoader("#{CR_BPAT}/#{fname}.mrb")
    elsif File.exist?("#{CR_BPAT}/#{fname}.rb")
      Internals.CLoader("#{CR_BPAT}/#{fname}.rb")
    end
  elsif File.extname(fname) != "" and File.exist?(fname)
    Internals.CLoader("#{CR_BPAT}/#{fname}")
  else
    raise StandardError.new "file #{fname}.mrb not found"
  end
end
