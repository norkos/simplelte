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
    
    id = 1
    req = messages_pb2.MessageWrapper()
    req.attach_req.id = id; 
    socket.send(req.SerializeToString())

    message = socket.recv()
    resp = messages_pb2.MessageWrapper()
    resp.ParseFromString(message)
    
    assert id == resp.attach_resp.id

def test_detach_request_for_not_attached(socket_for_single_message):
    socket = socket_for_single_message
    
    id = 1
    req = messages_pb2.MessageWrapper()
    req.detach_req.id = id; 
    socket.send(req.SerializeToString())

    message = socket.recv()
    resp = messages_pb2.MessageWrapper()
    resp.ParseFromString(message)
    
    assert id == resp.detach_resp.id
    assert messages_pb2.DetachResp.OK == resp.detach_resp.status  