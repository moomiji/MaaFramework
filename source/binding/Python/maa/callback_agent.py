import ctypes
import json
from typing import Any, Callable, Optional

from .define import MaaNotificationCallback

Callback = Callable[[str, Any, Any], None]


class CallbackAgent:
    def __init__(self, callback: Optional[Callback] = None, callback_arg: Any = None):
        self._callback = callback
        self._callback_arg = callback_arg

    @property
    def c_callback(self) -> MaaNotificationCallback:
        return self._c_callback_agent

    @property
    def c_callback_arg(self) -> ctypes.c_void_p:
        return ctypes.c_void_p.from_buffer(ctypes.py_object(self))

    @staticmethod
    @MaaNotificationCallback
    def _c_callback_agent(
        msg: ctypes.c_char_p,
        details_json: ctypes.c_char_p,
        callback_arg: ctypes.c_void_p,
    ):
        if not callback_arg:
            return

        self: CallbackAgent = ctypes.cast(callback_arg, ctypes.py_object).value
        if not self._callback:
            return

        self._callback(
            msg.decode(),
            json.loads(details_json.decode()),
            self._callback_arg,
        )
