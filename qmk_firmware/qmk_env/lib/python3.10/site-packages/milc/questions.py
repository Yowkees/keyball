"""Sometimes you need to ask the user a question. MILC provides basic functions for collecting and validating user input. You can find these in the `milc.questions` module.
"""
from getpass import getpass
from typing import Any, Callable, Optional, Sequence, Union

from milc import cli
from .ansi import format_ansi


def yesno(prompt: str, *args: Any, default: Optional[bool] = None, **kwargs: Any) -> bool:
    """Displays `prompt` to the user and gets a yes or no response.

    Returns `True` for a yes and `False` for a no.

    | Argument | Description |
    |----------|-------------|
    | prompt | The prompt to present to the user. Can include ANSI and format strings like `cli.echo()`. |
    | default | Whether to default to a Yes or No when the user presses enter.<br><br>None- force the user to enter Y or N<br>True- Default to yes<br>False- Default to no |

    If you add `--yes` and `--no` arguments to your program the user can answer questions by passing command line flags.

    ```python
    @cli.argument('-y', '--yes', action='store_true', arg_only=True, help='Answer yes to all questions.')
    @cli.argument('-n', '--no', action='store_true', arg_only=True, help='Answer no to all questions.')
    ```
    """
    if args and kwargs:
        raise ValueError("You can't pass both args and kwargs!")

    # Check if we should return an answer without asking
    if 'no' in cli.args and cli.args.no:
        return False

    if 'yes' in cli.args and cli.args.yes:
        return True

    if not cli.interactive:
        return False

    # Format the prompt
    if args:
        formatted_prompt = prompt % args
    else:
        formatted_prompt = prompt % kwargs

    if default is None:
        formatted_prompt = formatted_prompt + ' [y/n] '
    elif default:
        formatted_prompt = formatted_prompt + ' [Y/n] '
    else:
        formatted_prompt = formatted_prompt + ' [y/N] '

    # Get input from the user
    while True:
        answer = input(format_ansi(formatted_prompt))

        if not answer and default is not None:
            return default

        elif answer.lower() in ['y', 'yes']:
            return True

        elif answer.lower() in ['n', 'no']:
            return False


def password(
    prompt: str = 'Enter password:',
    *args: Any,
    confirm: bool = False,
    confirm_prompt: str = 'Confirm password:',
    confirm_limit: int = 3,
    validate: Optional[Callable[[str], bool]] = None,
    **kwargs: Any,
) -> Optional[str]:
    """Securely receive a password from the user. Returns the password or None.

    When running in non-interactive mode this will always return None. Otherwise it will return the confirmed password the user provides.

    | Argument | Description |
    |----------|-------------|
    | prompt | The prompt to present to the user. Can include ANSI and format strings like milc's `cli.echo()`. |
    | confirm | Prompt the user to type the password again and make sure they match. |
    | confirm_prompt | The prompt to present to the user. Can include ANSI and format strings like milc's `cli.echo()`. |
    | confirm_limit | Number of attempts to confirm before giving up. Default: 3 |
    | validate | This is an optional function that can be used to validate the password, EG to check complexity. It should return True or False and have the following signature:<br><br>`def function_name(answer):` |
    """
    if not cli.interactive:
        return None

    if args:
        formatted_prompt = prompt % args
    else:
        formatted_prompt = prompt % kwargs

    if formatted_prompt[-1] != ' ':
        formatted_prompt += ' '

    if confirm_prompt[-1] != ' ':
        confirm_prompt += ' '

    i = 0

    while not confirm_limit or i < confirm_limit:
        pw = getpass(format_ansi(formatted_prompt))

        if pw:
            if validate is not None and not validate(pw):
                continue

            elif confirm:
                if getpass(format_ansi(confirm_prompt % args)) == pw:
                    return pw
                else:
                    cli.log.error('Passwords do not match!')

            else:
                return pw

            i += 1

    return None


def _cast_answer(answer_type: Callable[[str], str], answer: str) -> Any:
    """Attempt to convert answer to answer_type.
    """
    try:
        return answer_type(answer)
    except Exception as e:
        cli.log.error('Could not convert answer (%s) to type %s: %s', answer, answer_type.__name__, str(e))
        return None


def question(
    prompt: str,
    *args: Any,
    default: Optional[str] = None,
    confirm: bool = False,
    answer_type: Callable[[str], str] = str,
    validate: Optional[Callable[..., bool]] = None,
    **kwargs: Any,
) -> Union[str, Any]:
    """Allow the user to type in a free-form string to answer.

    | Argument | Description |
    |----------|-------------|
    | prompt | The prompt to present to the user. Can include ANSI and format strings like milc's `cli.echo()`. |
    | default | The value to return when the user doesn't enter any value. Use None to prompt until they enter a value. |
    | confirm | Present the user with a confirmation dialog before accepting their answer. |
    | answer_type | Specify a type function for the answer. Will re-prompt the user if the function raises any errors. Common choices here include int, float, and decimal.Decimal. |
    | validate | This is an optional function that can be used to validate the answer. It should return True or False and have the following signature:<br><br>`def function_name(answer, *args, **kwargs):` |
    """
    if not cli.interactive:
        return default

    if default is not None:
        prompt = '%s [%s] ' % (prompt, default)
    elif prompt and prompt[-1] != ' ':
        prompt += ' '

    while True:
        answer = input(format_ansi(prompt % (args or kwargs)))

        if answer:
            if validate is not None and not validate(answer, *args, **kwargs):
                continue

            elif confirm:
                if yesno('Is the answer "%s" correct?', answer, default=True):
                    return _cast_answer(answer_type, answer)

            else:
                return _cast_answer(answer_type, answer)

        elif default is not None:
            return default


def choice(
    heading: str,
    options: Sequence[str],
    *args: Any,
    default: Optional[int] = None,
    confirm: bool = False,
    prompt: str = 'Please enter your choice: ',
    **kwargs: Any,
) -> Optional[str]:
    """Present the user with a list of options and let them select one.

    Users can enter either the number or the text of their choice. This will return the value of the item they choose, not the numerical index.

    | Argument | Description |
    |----------|-------------|
    | heading | The text to place above the list of options. |
    | options | A sequence of items to choose from. |
    | default | The index of the item to return when the user doesn't enter any value. Use None to prompt until they enter a value. |
    | confirm | When True present the user with a confirmation dialog before accepting their answer. |
    | prompt | The prompt to present to the user. Can include color and format strings like milc's `cli.echo()`. |

    Users can enter either the number or the text of their choice.

    !!! warning
        This will return the value of the item they choose, not the numerical index.
    """
    if args:
        formatted_heading = heading % args
    else:
        formatted_heading = heading % kwargs

    if not cli.interactive:
        if default is None:
            return None
        return options[default]

    if prompt[-1] != ' ':
        prompt += ' '

    if default is not None:
        prompt = '%s[%s] ' % (prompt, default + 1)

    while True:
        answer = _choice_get_answer(options, default, prompt, formatted_heading)

        if answer:
            if confirm and not yesno('Is the answer "%s" correct?', answer, default=True):
                continue

            return answer


def _choice_get_answer(
    options: Sequence[str],
    default: Optional[int],
    prompt: str,
    formatted_heading: str,
) -> Optional[str]:
    """Get an answer from the user for choice().
    """
    # Prompt for an answer.
    cli.echo(formatted_heading)

    for i, option in enumerate(options, 1):
        cli.echo('\t{fg_cyan}%d.{fg_reset} %s', i, option)

    answer = input(format_ansi(prompt))

    # If the user types in one of the options exactly use that
    if answer in options:
        return answer

    # Massage the answer into a valid integer
    if answer == '' and default is not None:
        answer_index = default
    elif answer.isnumeric():
        answer_index = int(answer) - 1
    else:
        cli.log.error('Invalid choice: %s', answer)
        return None

    # Validate the answer
    if answer_index >= len(options) or answer_index < 0:
        cli.log.error('Invalid choice: %s', answer_index + 1)
        return None

    # Return the answer they chose.
    return options[answer_index]
