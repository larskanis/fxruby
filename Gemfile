source 'https://rubygems.org'

# Specify your gem's runtime dependencies in fxruby.gemspec
gemspec

# For some reason this is required in addition to the gemspec
# when 'bundle config force_ruby_platform true' is active:
gem 'mini_portile2'

group :development do
  gem 'rake-compiler', '~> 1.0'
  gem 'rake-compiler-dock', '~> 0.6.2'
  gem 'yard', '~> 0.8'
  gem "bundler", "~> 1.12"
  gem "rake", "~> 12.0"
end

group :test do
  gem 'opengl', '~> 0.8'
  gem 'glu', '~> 8.0'
  gem 'test-unit', '~> 3.1'
end
