import pytest
import messages_pb2
import zmq
from subprocess import Popen

@pytest.fixture(scope='function')
def socket_for_single_message(request):
    proc = Popen('build/CP_eNB/src/hwserver')
    context = zmq.Context()
    socket = context.socket(zmq.PAIR)
    socket.connect("tcp://localhost:5555")
    
    def tear_down():
        socket.close()
        proc.kill()
    
    request.addfinalizer(tear_down)
    return socket
    
def test_attach_request(socket_for_single_message):
    socket = socket_for_single_message
    
    req = messages_pb2.AttachReq()
    req.id = 1
    socket.send(req.SerializeToString())

    message = socket.recv()
    resp = messages_pb2.AttachResp()
    resp.ParseFromString(message)
    
    assert req.id == resp.id

def test_detach_request_for_not_attached(socket_for_single_message):
    socket = socket_for_single_message
    
    req = messages_pb2.DetachReq()
    req.id = 10
    socket.send(req.SerializeToString())

    message = socket.recv()
    resp = messages_pb2.DetachResp()
    resp.ParseFromString(message)
   
    assert req.id == resp.id
    assert messages_pb2.DetachResp.NOK == resp.status  