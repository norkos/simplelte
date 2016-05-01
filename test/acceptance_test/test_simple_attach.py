import pytest
import messages_pb2
import ctypes
lib = ctypes.CDLL('libeNB.so')

def test_hallo():
    attach_req = messages_pb2.AttachReq()
    attach_req.id = 10
    result = lib.response_proxy(attach_req)
    assert 20 == result
