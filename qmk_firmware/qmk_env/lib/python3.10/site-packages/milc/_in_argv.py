import sys
from typing import Optional


def _in_argv(argument: str) -> bool:
    """Returns true if the argument is found is sys.argv.

    Since long options can be passed as either '--option value' or '--option=value' we need to check for both forms.
    """
    for arg in sys.argv:
        if arg.split('=')[0] == argument:
            return True

    return False


def _index_argv(argument: str) -> Optional[int]:
    """Returns the location of the argument in sys.argv, or None.

    Since long options can be passed as either '--option value' or '--option=value' we need to check for both forms.
    """
    for i, arg in enumerate(sys.argv):
        if arg.split('=')[0] == argument:
            return i

    return None
