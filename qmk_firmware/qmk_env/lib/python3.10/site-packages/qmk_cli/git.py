"""Helpers for working with git.
"""
import subprocess

from milc import cli

default_repo = 'qmk_firmware'
default_fork = 'qmk/' + default_repo
default_branch = 'master'


def git_clone(url, destination, branch):
    git_clone = [
        'git',
        'clone',
        '--recurse-submodules',
        '--branch=' + branch,
        url,
        str(destination),
    ]
    cli.log.debug('Git clone command: %s', git_clone)

    try:
        with subprocess.Popen(git_clone, stderr=subprocess.STDOUT, stdout=subprocess.PIPE, bufsize=1, universal_newlines=True, encoding='utf-8') as p:
            for line in p.stdout:
                print(line, end='')

    except Exception as e:
        git_cmd = ' '.join([s.replace(' ', r'\ ') for s in git_clone])

        cli.log.error("Could not run '%s': %s: %s", git_cmd, e.__class__.__name__, e)
        return False

    if p.returncode == 0:
        cli.log.info('Successfully cloned %s to %s!', url, destination)
        return True

    else:
        cli.log.error('git clone exited %d', p.returncode)
        return False
