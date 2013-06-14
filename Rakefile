# encoding: UTF-8

require 'English' # for $CHILD_STATUS
require 'rubocop'

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

namespace :c do
  desc 'Check the style using astyle'
  task :style do
    puts 'Astyle check'
    puts
    check_system 'scripts/astyle_check.bash'
  end
end

namespace :ruby do
  desc 'Run rubocop on all Ruby files'
  task :style do
    puts 'Rubocop check'
    puts
    result = Rubocop::CLI.new.run %W{#{ __FILE__ } Gemfile}
    if result == 0
      puts 'No rubocop errors'
    else
      exit result
    end
  end
end

namespace :test do
  desc 'Run style check and unit tests'
  # Because it outputs at the end of the Rake task, it makes sense to
  # have test:all last.
  task everything: ['c:style', 'ruby:style', 'test:all'] do
    # nothing
  end
end

task default: 'test:everything'
