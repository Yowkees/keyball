#!/usr/bin/env python
# -*- coding: utf-8 -*-
try:
    from collections.abc import Mapping
except ImportError:
    from collections import Mapping

from functools import lru_cache
import json

__author__ = 'Pawel Zadrozny'
__copyright__ = 'Copyright (c) 2017, Pawel Zadrozny'


def dotty(dictionary=None, no_list=False):
    """Factory function for Dotty class.

    Create Dotty wrapper around existing or new dictionary.

    :param dict dictionary: Any dictionary or dict-like object
    :param bool no_list: If set to True then numeric keys will NOT be converted to list indices
    :return: Dotty instance
    """
    if dictionary is None:
        dictionary = {}
    return Dotty(dictionary, separator='.', esc_char='\\', no_list=no_list)


class Dotty:
    """Dictionary and dict-like objects wrapper.

    Dotty wraps dictionary and provides proxy for quick accessing to deeply
    nested keys and values using dot notation.

    Dot notation can be customize in special cases. Let's say dot character
    has special meaning, and you want to use other character for accessing
    deep keys.

    Dotty does not copy original dictionary but it operates on it.
    All changes made in original dictionary are reflected in dotty wrapped dict
    and vice versa.

    :param dict dictionary: Any dictionary or dict-like object
    :param str separator: Character used to chain deep access.
    :param str esc_char: Escape character for separator.
    :param bool no_list: If set to True then numeric keys will NOT be converted to list indices
    """

    def __init__(self, dictionary, separator='.', esc_char='\\', no_list=False):
        if not isinstance(dictionary, (Mapping, dict)):
            raise AttributeError('Dictionary must be type of dict')
        else:
            self._data = dictionary
        self.separator = separator
        self.esc_char = esc_char
        self.no_list = no_list

    def __repr__(self):
        return 'Dotty(dictionary={}, separator={!r}, esc_char={!r})'.format(
            self._data, self.separator, self.esc_char)

    def __str__(self):
        return str(self._data)

    def __hash__(self):
        return hash(str(self))

    def __eq__(self, other):
        try:
            return sorted(self._data.items()) == sorted(other.items())
        except AttributeError:
            return False

    def __len__(self):
        return len(self._data)

    def __getattr__(self, item):
        return getattr(self._data, item)

    def __contains__(self, item):
        def search_in(items, data):
            """Recursively search for deep key in dict.

            :param list items: List of dictionary keys
            :param data: Portion of dictionary to operate on
            :return bool: Predicate of key existence
            """
            it = items.pop(0)
            if it.isdigit():
                idx = int(it)
                if idx < len(data):
                    if items:
                        return search_in(items, data[idx])
                    else:
                        return data[idx]
                else:
                    return False

            if items and it in data:
                return search_in(items, data[it])
            return it in data

        return search_in(self._split(item), self._data)

    @staticmethod
    def _find_data_type(item, data):
        """This method returns item in datatype that exists in data dict.

        Method creates set of types present in dict keys
        and then iterates through them trying to convert item
        into one of types and check whether item under this type
        exists in dict keys. If yes then it'll return converted item.
        Otherwise item stays the same type as it was on entry.

        :param item: Item to convert to proper type
        :type item: any type

        :return: Converted or unchanged item
        :rtype: any type
        """
        data_types = [type(i) for i in data.keys()]
        for t in set(data_types):
            try:
                if t(item) in data:
                    item = t(item)
                    return item
            except ValueError:
                pass
        return item

    @lru_cache(maxsize=32)  # noqa: B019  # TODO: find a workaround for B019
    def __getitem__(self, item):
        def get_from(items, data):
            """Recursively get value from dictionary deep key.

            :param list items: List of dictionary keys
            :param data: Portion of dictionary to operate on
            :return: Value from dictionary
            :raises KeyError: If key does not exist
            """
            it = items.pop(0)
            if isinstance(data, list) and it.isdigit() and not self.no_list:
                it = int(it)
            elif it not in data and isinstance(data, dict):
                it = self._find_data_type(it, data)
            elif isinstance(data, list) and ':' in it and not self.no_list:
                # TODO: fix C417 Unnecessary use of map - use a generator expression instead.
                list_slice = slice(*map(lambda x: None if x == '' else int(x), it.split(':')))  # noqa: C417
                if items:
                    return [get_from(items.copy(), x) for x in data[list_slice]]
                else:
                    return data[list_slice]
            try:
                data = data[it]
            except TypeError:
                raise KeyError("List index must be an integer, got {}".format(it))
            if items and data is not None:
                return get_from(items, data)
            else:
                return data

        return get_from(self._split(item), self._data)

    def __setitem__(self, key, value):
        def set_to(items, data):
            """Recursively set value to dictionary deep key.

            :param list items: List of dictionary keys
            :param data: Portion of dictionary to operate on
            """
            it = items.pop(0)
            if items:

                if items[0].isdigit():
                    next_item = []
                else:
                    next_item = {}

                if it.isdigit():
                    it = int(it)
                    try:
                        if not data[it]:
                            data[it] = next_item
                    except IndexError:
                        self.set_list_index(data, it, next_item)
                    set_to(items, data[it])
                else:
                    if not data.get(it):
                        data[it] = next_item
                    set_to(items, data[it])

            else:
                if it.isdigit():
                    self.set_list_index(data, it, value)
                else:
                    data[it] = value

        set_to(self._split(key), self._data)

    @staticmethod
    def set_list_index(data, index, value):
        """Set value in list at specified index.
        All the values before target index should stay unchanged
        or be filled with None.
        :param data: List where value should be set
        :param index: String or Int of target index
        :param value: Target value to put under index
        """
        for _ in range(len(data), int(index) + 1):
            data.append(None)
        else:
            data[int(index)] = value

    def __delitem__(self, key):
        def del_key(items, data):
            """Recursively remove deep key from dict.

            :param list items: List of dictionary keys
            :param data: Portion of dictionary to operate on
            :raises KeyError: If key does not exist
            """
            it = items.pop(0)
            if it.isdigit():
                it = int(it)
            if items:
                del_key(items, data[it])
            else:
                del data[it]

        del_key(self._split(key), self._data)

    def copy(self):
        """Returns a shallow copy of dictionary wrapped in Dotty.

        :return: Dotty instance
        """
        return dotty(self._data.copy())

    @staticmethod
    def fromkeys(seq, value=None):
        """Create a new dictionary with keys from seq and values set to value.

        New created dictionary is wrapped in Dotty.

        :param seq: Sequence of elements which is to be used as keys for the new dictionary
        :param value: Value which is set to each element of the dictionary
        :return: Dotty instance
        """
        return dotty(dict.fromkeys(seq, value))

    def get(self, key, default=None):
        """Get value from deep key or default if key does not exist.

        This method match 1:1 with dict .get method except that it
        accepts deeply nested key with dot notation.

        :param str key: Single key or chain of keys
        :param Any default: Default value if deep key does not exist
        :return: Any or default value
        """
        try:
            return self.__getitem__(key)
        except (KeyError, IndexError):
            return default

    def pop(self, key, default=None):
        """Pop key from Dotty.

        This method match 1:1 with dict .pop method except that
        it accepts deeply nested key with dot notation.

        :param str key: Single key or chain of keys
        :param Any default: If default is provided will be returned
        :raises KeyError: If key does not exist and default has not been provided
        :return: Any or default value
        """

        def pop_from(items, data):
            it = items.pop(0)
            if it not in data:
                return default
            if items:
                data = data[it]
                return pop_from(items, data)
            else:
                return data.pop(it, default)

        return pop_from(self._split(key), self._data)

    def setdefault(self, key, default=None):
        """Get key value if exist otherwise set default value under given key
        and return its value.

        This method match 1:1 with dict .setdefault method except that
        it accepts deeply nested key with dot notation.

        :param str key: Single key or chain of keys
        :param Any default: Default value for not existing key
        :return: Value under given key or default
        """
        try:
            return self.__getitem__(key)
        except KeyError:
            self.__setitem__(key, default)
            return default

    def to_dict(self):
        """Return wrapped dictionary.

        This method does not copy wrapped dictionary.

        :return dict: Wrapped dictionary
        """
        return json.loads(self.to_json())

    def to_json(self):
        """Return wrapped dictionary as json string.

        This method does not copy wrapped dictionary.

        :return str: Wrapped dictionary as json string
        """
        return json.dumps(self._data, cls=DottyEncoder)

    def _split(self, key):
        """Split dot notated chain of keys.

        Works with custom separators and escape characters.

        :param str key: Single key or chain of keys
        :return list: List of keys
        """
        if not isinstance(key, str):
            return [key]
        esc_stamp = (self.esc_char + self.separator, '<#esc#>')
        skp_stamp = ('\\' + self.esc_char + self.separator, '<#skp#>' + self.separator)

        stamp_esc = ('<#esc#>', self.separator)
        stamp_skp = ('<#skp#>', self.esc_char)

        key = key.replace(*skp_stamp).replace(*esc_stamp)
        keys = key.split(self.separator)
        for i, k in enumerate(keys):
            keys[i] = k.replace(*stamp_esc).replace(*stamp_skp)

        return keys


class DottyEncoder(json.JSONEncoder):
    """Helper class for encoding of nested Dotty dicts into standard dict
    """
    def default(self, obj):
        """Return dict data of Dotty when possible or encode with standard format

        :param object: Input object

        :return: Serializable data
        """
        if hasattr(obj, '_data'):
            return obj._data
        else:
            return json.JSONEncoder.default(self, obj)
