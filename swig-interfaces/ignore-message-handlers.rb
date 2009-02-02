handlers = {}

Dir.glob('FX*.i') do |filename|
  decls = `grep "long on" #{filename}`
  decls.each_line do |decl|
    decl.strip!
    handlers[decl] = decl
  end
end

handlers.each_key do |decl|
  parts = decl.split
  parts.delete_at(0)
  puts "%ignore #{parts.join(' ')}"
end

