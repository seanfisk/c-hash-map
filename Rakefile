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

task default: 'test:all'

def git_current_branch()
    branches = `git branch`
    all_branches = branches.lines()
    current_branch = ''
    all_branches.each do |b|
	if(b.start_with?('*'))
	    current_branch = b.split(' ')[1]
        end
    end
    return current_branch
end

desc 'Upload current documentation to github-pages'
task :upload do
    current_branch = git_current_branch()
    puts 'rake doc'
    check_system 'rake doc'
    puts 'git checkout gh-pages'
    check_system 'git checkout gh-pages'
    puts 'cp -r doc/html/* .'
    check_system 'cp -r doc/html/* .'
    puts 'git add .'
    check_system 'git add .'
    puts 'git commit -m "new documentation uploaded to github-pages"'
    check_system 'git commit -m "new documentation uploaded to github-pages"'
    cmd = 'git checkout ' + current_branch
    puts cmd
    `cmd`
end
