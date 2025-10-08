"""ANSI color support for MILC.
"""
import sys
import re
import logging
import colorama
from typing import Any

from .emoji import EMOJI_LOGLEVELS

ansi_config = {
    'color': True,
    'unicode': sys.stdout.encoding.lower().startswith('utf'),
}

# Regex was gratefully borrowed from kfir on stackoverflow:
# https://stackoverflow.com/a/45448194
ansi_regex = r'\x1b(' \
             r'(\[\??\d+[hl])|' \
             r'([=<>a-kzNM78])|' \
             r'([\(\)][a-b0-2])|' \
             r'(\[\d{0,2}[ma-dgkjqi])|' \
             r'(\[\d+;\d+[hfy]?)|' \
             r'(\[;?[hf])|' \
             r'(#[3-68])|' \
             r'([01356]n)|' \
             r'(O[mlnp-z]?)|' \
             r'(/Z)|' \
             r'(\d+)|' \
             r'(\[\?\d;\d0c)|' \
             r'(\d;\dR))'
ansi_escape = re.compile(ansi_regex, flags=re.IGNORECASE)
ansi_styles = (
    ('fg', colorama.ansi.AnsiFore()),
    ('bg', colorama.ansi.AnsiBack()),
    ('style', colorama.ansi.AnsiStyle()),
)
ansi_colors = {}

for prefix, obj in ansi_styles:
    for color in [x for x in obj.__dict__ if not x.startswith('_')]:
        ansi_colors[prefix + '_' + color.lower()] = getattr(obj, color)


def format_ansi(text: str) -> str:
    """Return a copy of text with certain strings replaced with ansi.
    """
    # Avoid .format() so we don't have to worry about the log content
    for color in ansi_colors:
        text = text.replace('{%s}' % color, ansi_colors[color])

    text = text + ansi_colors['style_reset_all']

    if ansi_config['color']:
        return text

    return ansi_escape.sub('', text)


class MILCFormatter(logging.Formatter):
    """Formats log records per the MILC configuration.
    """
    def format(self, record: Any) -> Any:
        if ansi_config['unicode'] and record.levelname in EMOJI_LOGLEVELS:
            record.levelname = format_ansi(EMOJI_LOGLEVELS[record.levelname])

        msg = super().format(record)

        return format_ansi(msg)
