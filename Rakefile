# encoding: UTF-8

require 'English' # for $CHILD_STATUS
require 'rubocop'

# Load Ceedling Rake tasks
PROJECT_CEEDLING_ROOT = 'vendor/ceedling'
load "#{PROJECT_CEEDLING_ROOT}/lib/rakefile.rb"

# Helper functions

def check_system(*args)
  system(*args)
  exit $CHILD_STATUS.exitstatus if $CHILD_STATUS != 0
end

def git_current_branch
  branches = `git branch`
  all_branches = branches.lines()
  current_branch = ''
  all_branches.each do |b|
    current_branch = b.split(' ')[1] if b.start_with? '*'
  end
  return current_branch
end

# Tasks

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

desc 'Upload current documentation to github-pages'
task :upload do
    current_branch = git_current_branch()
    puts 'rake doc...'
    check_system 'rake', 'doc'
    puts 'git checkout gh-pages...'
    check_system 'git', 'checkout', 'gh-pages'
    puts 'cp -r doc/html/* . ...'
    `cp -r doc/html/* .`
    puts 'git add . ...'
    check_system 'git', 'add', '.'
    puts 'git commit -m "new documentation uploaded to github-pages" ...'
    `git commit -m "new documentation uploaded to github-pages"`
    cmd = 'git checkout ' + current_branch
    puts cmd
    `#{cmd}`
end

task default: 'test:everything'
