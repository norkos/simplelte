from subprocess import Popen
import pytest
import zmq
import messages_pb2
from ue_functions import attach_ue, detach_ue

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
    resp = attach_ue(id, socket)
    
    assert id == resp.id
    assert messages_pb2.AttachResp.OK == resp.status
    
def test_attach_already_attached(socket_for_single_message):
    socket = socket_for_single_message
    
    id = 1
    attach_ue(id, socket)
    resp = attach_ue(id, socket)
    
    assert id == resp.id
    assert messages_pb2.AttachResp.NOK == resp.status

def test_detach_request_for_not_attached(socket_for_single_message):
    socket = socket_for_single_message
    
    id = 1
    resp = detach_ue(id, socket)
    
    assert id == resp.id
    assert messages_pb2.DetachResp.NOK == resp.status 
    
def test_detach_request_for_attached(socket_for_single_message):
    socket = socket_for_single_message
    
    id = 1
    attach_ue(id, socket)
    resp = detach_ue(id, socket)
    
    assert id == resp.id
    assert messages_pb2.DetachResp.OK == resp.status
    
