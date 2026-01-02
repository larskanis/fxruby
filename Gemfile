source 'https://rubygems.org'

# No fxruby gemspec, since "bundle package" fails on bundler-2.7+, if the extension isn't built
# gemspec

# For some reason this is required in addition to the gemspec
# when 'bundle config force_ruby_platform true' is active:
gem 'mini_portile2'

group :development do
  gem 'rake-compiler', '~> 1.0'
  gem 'rake-compiler-dock', '~> 1.11.0'
  gem 'yard', '~> 0.8'
  gem "bundler", ">= 1.12", "< 5.a"
  gem "rake", "~> 13.0"
end

group :test do
  gem 'opengl-bindings2', '~> 2.0'
  gem 'test-unit', '~> 3.1'
end
