"""Read and write configuration settings
"""
from typing import Any, Tuple

import milc
from milc.milc import MILC


def print_config(section: str, key: str) -> None:
    """Print a single config setting to stdout.
    """
    if milc.cli.config_source[section][key] == 'config_file':
        milc.cli.echo('%s.%s{fg_blue}={fg_reset}%s', section, key, milc.cli.config[section][key])
    else:
        milc.cli.echo('{fg_cyan}%s.%s=%s', section, key, milc.cli.config[section][key])


def show_config() -> None:
    """Print the current configuration to stdout.
    """
    for section in sorted(milc.cli.config):
        for key in sorted(milc.cli.config[section]):
            if milc.cli.config_source[section][key] == 'config_file' or milc.cli.config.config.all:
                print_config(section, key)


def parse_config_token(config_token: str) -> Tuple[str, str, Any]:
    """Split a user-supplied configuration-token into its components.
    """
    section = option = value = ''

    if '=' in config_token and '.' not in config_token:
        milc.cli.log.error('Invalid configuration token, the key must be of the form <section>.<option>: %s', config_token)
        return section, option, value

    # Separate the key (<section>.<option>) from the value
    if '=' in config_token:
        key, value = config_token.split('=')
    else:
        key = config_token

    # Extract the section and option from the key
    if '.' in key:
        section, option = key.split('.', 1)
    else:
        section = key

    return section, option, value


def set_config(section: str, option: str, value: str) -> None:
    """Set a config key in the running config.
    """
    log_string = '%s.%s{fg_cyan}:{fg_reset} %s {fg_cyan}->{fg_reset} %s'

    if milc.cli.args.read_only:
        log_string += ' {fg_red}(change not written)'

    milc.cli.echo(log_string, section, option, milc.cli.config[section][option], value)

    if not milc.cli.args.read_only:
        if value == 'None':
            del milc.cli.config[section][option]

        else:
            milc.cli.config[section][option] = value
            milc.cli.config_source[section][option] = 'config_file'


@milc.cli.argument('-a', '--all', action='store_true', help='Show all configuration options.')
@milc.cli.argument('-ro', '--read-only', arg_only=True, action='store_true', help='Operate in read-only mode.')
@milc.cli.argument('configs', nargs='*', arg_only=True, help='Configuration options to read or write.')
@milc.cli.subcommand("Read and write configuration settings.")
def config(cli: MILC) -> bool:
    """Read and write config settings.

    This script iterates over the config_tokens supplied as argument. Each config_token has the following form:

        section[.key][=value]

    If only a section (EG 'compile') is supplied all keys for that section will be displayed.

    If section.key is supplied the value for that single key will be displayed.

    If section.key=value is supplied the value for that single key will be set.

    If section.key=None is supplied the key will be deleted.

    No validation is done to ensure that the supplied section.key is actually used by a subcommand.
    """
    if not milc.cli.args.configs:
        show_config()
        return False

    # Process config_tokens
    save_config = False

    for config_token in milc.cli.args.configs:
        section, option, value = parse_config_token(config_token)

        # Validation
        if option and '.' in option:
            milc.cli.log.error('Config keys may not have more than one period! "%s" is not valid.', config_token)
            return False

        # Do what the user wants
        if section and option and value:
            # Write a configuration option
            set_config(section, option, value)
            if not milc.cli.args.read_only:
                save_config = True

        elif section and option:
            # Display a single key
            print_config(section, option)

        elif section:
            # Display an entire section
            for key in milc.cli.config[section]:
                if milc.cli.config_source[section][key] == 'config_file':
                    print_config(section, key)

    # Ending actions
    if save_config:
        milc.cli.save_config()

    return True
