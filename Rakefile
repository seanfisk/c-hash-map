# encoding: UTF-8

require 'English' # for $CHILD_STATUS
require 'rubocop'

# Load Ceedling Rake tasks
PROJECT_CEEDLING_ROOT = 'vendor/ceedling'
load "#{PROJECT_CEEDLING_ROOT}/lib/rakefile.rb"

# Tasks

desc 'Build documentation with Doxygen'
task :doc do
  sh 'doxygen'
end

namespace :c do
  desc 'Check the style using astyle'
  task :style do
    puts 'Astyle check'
    puts
    sh 'scripts/astyle_check.bash'
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
  # Credit:
  # http://stackoverflow.com/questions/6245570/get-current-branch-name
  # symbolic-ref, unlike rev-parse, will blow up when in detached HEAD
  # state, which is probably more what we want.
  current_branch = `git symbolic-ref --short HEAD`.strip()

  Rake::Task['doc'].invoke
  sh 'git', 'checkout', 'gh-pages'
  FileUtils.cp_r Dir.glob('doc/html/*'), '.'
  sh 'git', 'add', '.'
  # We amend so we don't add useless commits.
  sh 'git', 'commit', '--amend', '-m',
     'new documentation uploaded to Github pages'
  # Now that we've amended, we must force push.
  sh 'git', 'push', '--force', 'origin', 'gh-pages'
  sh 'git', 'checkout', current_branch
end

task default: 'test:everything'
