# encoding: UTF-8

require 'English'

# Load Ceedling Rake tasks
PROJECT_CEEDLING_ROOT = 'vendor/ceedling'
load "#{PROJECT_CEEDLING_ROOT}/lib/rakefile.rb"

def check_system(*args)
  system(*args)
  exit $CHILD_STATUS.exitstatus if $CHILD_STATUS != 0
end

desc 'Build documentation with Doxygen'
task :doc do
  check_system 'doxygen'
end

desc 'Check the style using astyle'
task :style do
  puts 'Style check'
  puts
  check_system 'scripts/astyle_check.bash'
end

namespace :test do
  desc 'Run style check and unit tests'
  task everything: [:style, 'test:all'] {}
end

task default: 'test:everything'
