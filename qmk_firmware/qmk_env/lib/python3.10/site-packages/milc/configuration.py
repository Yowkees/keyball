from typing import Any, Hashable, List

from .attrdict import AttrDict


class Configuration(AttrDict):
    """Represents the running configuration.

    This class never raises IndexError, instead it will return None if a
    section or option does not yet exist.
    """
    def __getitem__(self, key: Hashable) -> Any:
        """Returns a config section, creating it if it doesn't exist yet.
        """
        if key not in self._data:
            self._data[key] = ConfigurationSection(self)

        return self._data[key]


class ConfigurationSection(Configuration):
    def __init__(self, parent: AttrDict, *args: Any, **kwargs: Any) -> None:
        super(ConfigurationSection, self).__init__(*args, **kwargs)
        self._parent = parent

    def __getitem__(self, key: Hashable) -> Any:
        """Returns a config value, pulling from the `user` section as a fallback.
        This is called when the attribute is accessed either via the get method or through [ ] index.
        """
        if key in self._data and self._data.get(key) is not None:
            return self._data[key]

        elif key in self._parent.user:
            return self._parent.user[key]

        return None

    def __getattr__(self, key: str) -> Any:
        """Returns the config value from the `user` section.
        This is called when the attribute is accessed via dot notation but does not exist.
        """
        if key[0] != '_' and key in self._parent['user']:
            return self._parent['user'][key]

        return None

    def __setattr__(self, key: str, value: Any) -> None:
        """Sets dictionary value when an attribute is set.
        """
        super().__setattr__(key, value)

        if key[0] != '_':
            self._data[key] = value


class SubparserWrapper(object):
    """Wrap subparsers so we can track what options the user passed.
    """

    # We type `cli` as Any instead of MILC to avoid a circular import
    def __init__(self, cli: Any, submodule: Any, subparser: Any) -> None:
        self.cli = cli
        self.submodule = submodule
        self.subparser = subparser

        for attr in dir(subparser):
            if not hasattr(self, attr):
                setattr(self, attr, getattr(subparser, attr))

    def completer(self, completer: Any) -> None:
        """Add an arpcomplete completer to this subcommand.
        """
        self.subparser.completer = completer

    def add_argument(self, *args: Any, **kwargs: Any) -> None:
        """Add an argument for this subcommand.

        This also stores the default for the argument in `self.cli.default_arguments`.
        """
        if kwargs.get('action') == 'store_boolean':
            # Store boolean will call us again with the enable/disable flag arguments
            handle_store_boolean(self, *args, **kwargs)

        else:
            completer = None

            if kwargs.get('completer'):
                completer = kwargs['completer']
                del kwargs['completer']

            self.cli.acquire_lock()
            argument_name = get_argument_name(self.cli._arg_parser, *args, **kwargs)

            if completer:
                self.subparser.add_argument(*args, **kwargs).completer = completer
            else:
                self.subparser.add_argument(*args, **kwargs)

            if kwargs.get('action') == 'store_false':
                self.cli._config_store_false.append(argument_name)

            if kwargs.get('action') == 'store_true':
                self.cli._config_store_true.append(argument_name)

            if self.submodule not in self.cli.default_arguments:
                self.cli.default_arguments[self.submodule] = {}

            self.cli.default_arguments[self.submodule][argument_name] = kwargs.get('default')
            self.cli.release_lock()


def get_argument_strings(arg_parser: Any, *args: Any, **kwargs: Any) -> List[str]:
    """Takes argparse arguments and returns a list of argument strings or positional names.
    """
    try:
        return arg_parser._get_optional_kwargs(*args, **kwargs)['option_strings']  # type: ignore[no-any-return]

    except ValueError:
        return [arg_parser._get_positional_kwargs(*args, **kwargs)['dest']]


def get_argument_name(arg_parser: Any, *args: Any, **kwargs: Any) -> Any:
    """Takes argparse arguments and returns the dest name.
    """
    try:
        return arg_parser._get_optional_kwargs(*args, **kwargs)['dest']

    except ValueError:
        return arg_parser._get_positional_kwargs(*args, **kwargs)['dest']


# FIXME: We should not be using self in this way
def handle_store_boolean(self: Any, *args: Any, **kwargs: Any) -> Any:
    """Does the add_argument for action='store_boolean'.
    """
    disabled_args = None
    disabled_kwargs = kwargs.copy()
    disabled_kwargs['action'] = 'store_false'
    disabled_kwargs['dest'] = get_argument_name(getattr(self, 'cli', self)._arg_parser, *args, **kwargs)
    disabled_kwargs['help'] = 'Disable ' + kwargs['help']
    kwargs['action'] = 'store_true'
    kwargs['help'] = 'Enable ' + kwargs['help']

    for flag in args:
        if flag[:2] == '--':
            disabled_args = ('--no-' + flag[2:],)
            break

    self.add_argument(*args, **kwargs)
    self.add_argument(*disabled_args, **disabled_kwargs)

    return (args, kwargs, disabled_args, disabled_kwargs)
