# encoding: UTF-8

require 'English' # for $CHILD_STATUS
require 'rubocop'
require 'tmpdir'

# Load Ceedling Rake tasks
PROJECT_CEEDLING_ROOT = 'vendor/ceedling'
load "#{PROJECT_CEEDLING_ROOT}/lib/rakefile.rb"

DOC_HTML_DIR = 'doc/html'

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
task :upload_doc do
  # If the repository exists already, don't re-clone it.
  unless Dir.exists? "#{DOC_HTML_DIR}/.git"
    # But do clone it if the path is not yet a git repository.
    FileUtils.remove_entry_secure DOC_HTML_DIR if Dir.exists? DOC_HTML_DIR
    puts "Cloning copy of repository to #{DOC_HTML_DIR}"
    sh 'git', 'clone', '--branch', 'gh-pages',
       'git@github.com:seanfisk/c-hash-map.git', DOC_HTML_DIR
  end
  # Build the docs.
  Rake::Task['doc'].invoke
  # Upload the new documentation.
  Dir.chdir(DOC_HTML_DIR)
  puts 'Uploading new documentation...'
  sh 'git', 'add', '.'
  # We amend so we don't add useless commits.
  sh 'git', 'commit', '--amend', '-m',
     'new documentation uploaded to Github pages'
  # Now that we've amended, we must force push.
  sh 'git', 'push', '--force', 'origin', 'gh-pages'
end

task default: 'test:everything'
