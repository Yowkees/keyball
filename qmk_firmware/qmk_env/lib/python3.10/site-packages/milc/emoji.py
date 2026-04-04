"""Emoji used by MILC when outputting logs

| Log Level | Emoji |
|-----------|-------|
| `CRITICAL` | `{bg_red}{fg_white}¬_¬` |
| `ERROR` | `{fg_red}☒` |
| `WARNING` | `{fg_yellow}⚠` |
| `INFO` | `{fg_blue}ℹ` |
| `DEBUG` | `{fg_cyan}☐` |
| `NOTSET` | `{style_reset_all}¯\\_(o_o)_/¯` |

If you'd like to use your own icon for a level instead you can simply redefine it:

```python
from milc.emoji import EMOJI_LOGLEVELS

EMOJI_LOGLEVELS['INFO'] = {fg_green}ℹ'
```
"""
EMOJI_LOGLEVELS = {
    'CRITICAL': '{bg_red}{fg_white}¬_¬',
    'ERROR': '{fg_red}☒',
    'WARNING': '{fg_yellow}⚠',
    'INFO': '{fg_blue}ℹ',
    'DEBUG': '{fg_cyan}☐',
    'NOTSET': '{style_reset_all}¯\\_(o_o)_/¯',
}
EMOJI_LOGLEVELS['FATAL'] = EMOJI_LOGLEVELS['CRITICAL']
EMOJI_LOGLEVELS['WARN'] = EMOJI_LOGLEVELS['WARNING']
