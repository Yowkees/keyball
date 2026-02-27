"""Public interface for MILC.

This is where the public interface for `cli` is kept. This allows us to reinstantiate MILC without having to recreate the cli object, as well as allowing us to have a well defined public API.
"""
import warnings
import sys
from logging import Logger
from pathlib import Path
from types import TracebackType
from typing import Any, Callable, Dict, Optional, Sequence, Type, Union

from halo import Halo  # type: ignore

from .attrdict import AttrDict
from .configuration import Configuration
from .milc import MILC


class MILCInterface:
    def __init__(self) -> None:
        self._milc: Optional[MILC] = None
        self._name: Optional[str] = None
        self._author: Optional[str] = None
        self._version: Optional[str] = None
        self._logger: Optional[Logger] = None

    def milc_options(self, *, name: Optional[str] = None, author: Optional[str] = None, version: Optional[str] = None, logger: Optional[Logger] = None) -> None:
        if self._milc and self._milc._inside_context_manager:
            raise RuntimeError('You must run cli.milc_options() before cli() or anything else!')

        self._name = name or self._name
        self._author = author or self._author
        self._version = version or self._version
        self._logger = logger or self._logger
        self._milc = MILC(self._name, self._author, self._version, self._logger)

    @property
    def milc(self) -> MILC:
        if not self._milc:
            self._milc = MILC()

        return self._milc

    @property
    def args(self) -> AttrDict:
        return self.milc.args

    @property
    def config(self) -> Configuration:
        return self.milc.config

    @property
    def config_dir(self) -> Path:
        return self.milc.config_dir

    @property
    def config_source(self) -> Configuration:
        return self.milc.config_source

    @property
    def description(self) -> Optional[str]:
        return self.milc.description

    @property
    def interactive(self) -> bool:
        return self.milc.interactive

    @property
    def log(self) -> Logger:
        return self.milc.log

    @property
    def platform(self) -> str:
        return self.milc.platform

    @property
    def _subcommand(self) -> Any:
        warnings.warn("cli._subcommand has been deprecated, please use cli.subcommand_name to get the subcommand name instead.", stacklevel=2)

        return self.milc._subcommand

    @property
    def subcommands(self) -> Dict[str, Any]:
        return self.milc.subcommands

    @property
    def subcommand_name(self) -> Optional[str]:
        return self.milc.subcommand_name

    def echo(self, text: str, *args: Any, **kwargs: Any) -> None:
        """Print colorized text to stdout.

        ANSI color strings (such as {fg_blue}) will be converted into ANSI
        escape sequences, and the ANSI reset sequence will be added to all
        strings.

        If *args or **kwargs are passed they will be used to %-format the strings.
        """
        return self.milc.echo(text, *args, **kwargs)

    def run(self, command: Sequence[str], capture_output: bool = True, combined_output: bool = False, text: bool = True, **kwargs: Any) -> Any:  # FIXME: In python 3.10 we can use subprocess.CompletedProcess[bytes | str] instead
        """Run a command using `subprocess.run`, but using some different defaults.

        Unlike subprocess.run you must supply a sequence of arguments. You can use `shlex.split()` to build this from a string.

        The **kwargs arguments get passed directly to `subprocess.run`.

        Args:
            command
                A sequence where the first item is the command to run, and any remaining items are arguments to pass.

            capture_output
                Set to False to have output written to the terminal instead of being available in the returned `subprocess.CompletedProcess` instance.

            combined_output
                When true STDERR will be written to STDOUT. Equivalent to the shell construct `2>&1`.

            text
                Set to False to disable encoding and get `bytes()` from `.stdout` and `.stderr`.
        """
        return self.milc.run(command, capture_output, combined_output, text, **kwargs)

    def print_help(self, *args: Any, **kwargs: Any) -> None:
        """Print a help message for the main program or subcommand, depending on context.
        """
        return self.milc.print_help(*args, **kwargs)

    def print_usage(self, *args: Any, **kwargs: Any) -> None:
        """Print brief description of how the main program or subcommand is invoked, depending on context.
        """
        return self.milc.print_usage(*args, **kwargs)

    def add_argument(self, *args: Any, **kwargs: Any) -> None:
        """Wrapper to add arguments and track whether they were passed on the command line.
        """
        return self.milc.add_argument(*args, **kwargs)

    def acquire_lock(self, blocking: bool = True) -> bool:
        """Acquire the MILC lock for exclusive access to properties.
        """
        return self.milc.acquire_lock(blocking)

    def release_lock(self) -> None:
        """Release the MILC lock.
        """
        return self.milc.release_lock()

    def argument(self, *args: Any, **kwargs: Any) -> Callable[..., Any]:
        """Decorator to add an argument to a MILC command or subcommand.
        """
        return self.milc.argument(*args, **kwargs)

    def save_config(self) -> None:
        """Save the current configuration to the config file.
        """
        return self.milc.save_config()

    def __call__(self) -> Any:
        """Execute the entrypoint function.
        """
        return self.milc()

    def entrypoint(self, description: str, deprecated: Optional[str] = None) -> Callable[..., Any]:
        """Decorator that marks the entrypoint used when a subcommand is not supplied.
        Args:
            description
                A one-line description to display in --help

            deprecated
                Deprecation message. When set the subcommand will marked as deprecated and this message will be displayed in the help output.
        """
        return self.milc.entrypoint(description, deprecated)

    def subcommand(self, description: str, hidden: bool = False, **kwargs: Any) -> Callable[..., Any]:
        """Decorator to register a subcommand.

        Args:

            description
                A one-line description to display in --help

            hidden
                When True don't display this command in --help
        """
        return self.milc.subcommand(description, hidden, **kwargs)

    def __enter__(self) -> Any:
        return self.milc.__enter__()

    def __exit__(
        self,
        exc_type: Optional[Type[BaseException]],
        exc_val: Optional[BaseException],
        exc_tb: Optional[TracebackType],
    ) -> None:
        return self.milc.__exit__(exc_type, exc_val, exc_tb)

    def add_spinner(self, name: str, spinner: Dict[str, Union[int, Sequence[str]]]) -> None:
        """Adds a new spinner to the list of spinners.

        A spinner is a dictionary with two keys:

            interval
                An integer that sets how long (in ms) to wait between frames.

            frames
                A list of frames for this spinner
        """
        return self.milc.add_spinner(name, spinner)

    def spinner(
        self,
        text: str,
        *args: Any,
        spinner: Optional[str] = None,
        animation: str = 'ellipsed',
        placement: str = 'left',
        color: str = 'blue',
        interval: int = -1,
        stream: Any = sys.stdout,
        enabled: bool = True,
        **kwargs: Any,
    ) -> Halo:
        """Create a spinner object for showing activity to the user.

        This uses halo <https://github.com/ManrajGrover/halo> behind the scenes, most of the arguments map to Halo objects 1:1.

        There are 3 basic ways to use this:

        * Instantiating a spinner and then using `.start()` and `.stop()` on your object.
        * Using a context manager (`with cli.spinner(...):`)
        * Decorate a function (`@cli.spinner(...)`)

        #### Instantiating a spinner

        ```python
        spinner = cli.spinner(text='Loading', spinner='dots')
        spinner.start()

        # Do something here

        spinner.stop()
        ```

        #### Using a context manager

        ```python
        with cli.spinner(text='Loading', spinner='dots'):
            # Do something here
        ```

        #### Decorate a function

        ```python
        @cli.spinner(text='Loading', spinner='dots')
        def long_running_function():
            # Do something here
        ```

        ### Arguments

            text
                The text to display next to the spinner. ANSI color strings
                (such as {fg_blue}) will be converted into ANSI escape
                sequences, and the ANSI reset sequence will be added to the
                end of the string.

                If *args or **kwargs are passed they will be used to
                %-format the text.

            spinner
                The name of the spinner to use. Available names are here:
                <https://raw.githubusercontent.com/sindresorhus/cli-spinners/dac4fc6571059bb9e9bc204711e9dfe8f72e5c6f/spinners.json>

            animation
                The animation to apply to the text if it doesn't fit the
                terminal. One of `ellipsed`, `bounce`, `marquee`.

            placement
                Which side of the text to display the spinner on. One of
                `left`, `right`.

            color
                Color of the spinner. One of `blue`, `grey`, `red`, `green`,
                `yellow`, `magenta`, `cyan`, `white`

            interval
                How long in ms to wait between frames. Defaults to the spinner interval (recommended.)

            stream
                Stream to write the output. Defaults to sys.stdout.

            enabled
                Enable or disable the spinner. Defaults to `True`.
        """
        return self.milc.spinner(text, *args, spinner=spinner, animation=animation, placement=placement, color=color, interval=interval, stream=stream, enabled=enabled, **kwargs)
