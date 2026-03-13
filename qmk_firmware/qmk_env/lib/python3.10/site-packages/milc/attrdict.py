from typing import Any, Dict, List


class AttrDict(object):
    """A dictionary that can also be accessed by attribute.
    """
    def __contains__(self, key: Any) -> bool:
        return self._data.__contains__(key)

    def __iter__(self) -> Any:
        return self._data.__iter__()

    def __len__(self) -> Any:
        return self._data.__len__()

    def __repr__(self) -> Any:
        return self._data.__repr__()

    def keys(self) -> Any:
        return self._data.keys()

    def items(self) -> Any:
        return self._data.items()

    def values(self) -> Any:
        return self._data.values()

    def __init__(self, *args: List[Any], **kwargs: Dict[Any, Any]) -> None:
        self._data: Dict[Any, Any] = {}

    def __getattr__(self, key: Any) -> Any:
        return self.__getitem__(key)

    def __getitem__(self, key: Any) -> Any:
        """Returns an item.
        """
        return self._data[key]

    def __setitem__(self, key: Any, value: Any) -> None:
        self._data[key] = value
        self.__setattr__(key, value)

    def __delitem__(self, key: Any) -> None:
        if key in self._data:
            del self._data[key]


class SparseAttrDict(AttrDict):
    """A dictionary that can also be accessed by attribute.

    This class never raises IndexError, instead it will return None if a
    key does not yet exist.
    """
    def __getitem__(self, key: Any) -> Any:
        """Returns an item, creating it if it doesn't already exist
        """
        if key not in self._data:
            self._data[key] = None

        return self._data[key]
