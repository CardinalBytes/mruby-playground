def cim(lm, rm)
  lm = lm.upcase
  rm = rm.upcase
  return lm == rm
end

def prand(max)
  srng = File.open "/dev/urandom", "r"
  rstr = srng.read(16)
  seeds = []
  rstr.each_byte do |c|
    seeds.append(c)
  end
  rng = Random.new(seeds[0])
  return rng.rand max
end