"""Useful helper functions.
"""
import os
import json
from functools import lru_cache
from pathlib import Path

from milc import cli


def is_qmk_firmware(qmk_firmware):
    """Returns True if the given Path() is a qmk_firmware clone.
    """
    paths = [
        qmk_firmware,
        qmk_firmware / 'quantum',
        qmk_firmware / 'requirements.txt',
        qmk_firmware / 'requirements-dev.txt',
        qmk_firmware / 'lib/python/qmk/cli/__init__.py'
    ]

    for path in paths:
        if not path.exists():
            return False

    return True


@lru_cache(maxsize=1)
def find_qmk_firmware():
    """Look for qmk_firmware in the usual places.

    This function returns the path to qmk_firmware, or the default location if one does not exist.
    """
    if in_qmk_firmware():
        return in_qmk_firmware()

    if cli.config.user.qmk_home:
        return Path(cli.config.user.qmk_home).expanduser().resolve()

    if 'QMK_HOME' in os.environ:
        path = Path(os.environ['QMK_HOME']).expanduser()
        if path.exists():
            return path.resolve()
        return path

    return Path.home() / 'qmk_firmware'


@lru_cache(maxsize=1)
def in_qmk_firmware():
    """Returns the path to the qmk_firmware we are currently in, or None if we are not inside qmk_firmware.
    """
    cur_dir = Path.cwd()
    while len(cur_dir.parents) > 0:
        if is_qmk_firmware(cur_dir):
            return cur_dir

        # Move up a directory before the next iteration
        cur_dir = cur_dir / '..'
        cur_dir = cur_dir.resolve()


def is_qmk_userspace(qmk_userspace):
    """Returns True if the given Path() is a qmk_userspace clone.
    """
    path = qmk_userspace / 'qmk.json'
    if not path.exists():
        return False

    try:
        return 'userspace_version' in json.loads(path.read_text(encoding="UTF-8"))
    except json.decoder.JSONDecodeError as e:
        return False


@lru_cache(maxsize=1)
def find_qmk_userspace():
    """Look for qmk_userspace in the usual places.
    """
    if in_qmk_userspace():
        return in_qmk_userspace()

    if cli.config.user.overlay_dir:
        return Path(cli.config.user.overlay_dir).expanduser().resolve()

    if 'QMK_USERSPACE' in os.environ:
        path = Path(os.environ['QMK_USERSPACE']).expanduser()
        if path.exists():
            return path.resolve()
        return path

    return Path.home() / 'qmk_userspace'


@lru_cache(maxsize=1)
def in_qmk_userspace():
    """Returns the path to the qmk_userspace we are currently in, or None if we are not inside qmk_userspace.
    """
    cur_dir = Path.cwd()
    while len(cur_dir.parents) > 0:
        if is_qmk_userspace(cur_dir):
            return cur_dir

        # Move up a directory before the next iteration
        cur_dir = cur_dir / '..'
        cur_dir = cur_dir.resolve()
