from subprocess import Popen
import pytest
import sys
import zmq
import messages_pb2
from ue_functions import attach_ue, detach_ue

@pytest.fixture(scope='function')
def socket_for_single_message(request):
    proc = Popen('build/CP_eNB/src/hwserver2')
    context = zmq.Context()
    socket = context.socket(zmq.PAIR)
    socket.connect("tcp://localhost:5555")
    
    def tear_down():
        socket.close()
        proc.kill()
    
    request.addfinalizer(tear_down)
    return socket
    
def test_sib(socket_for_single_message):
    socket = socket_for_single_message
    
    id = 1
    attach_ue(id, socket)
    
    poller = zmq.Poller()
    poller.register(socket, zmq.POLLIN)
    
    if poller.poll(5000):
        message = socket.recv()
        resp = messages_pb2.ASN1()
        resp.ParseFromString(message)
        assert 1986 == resp.rrc.sib.cell_identity
        
    else:
        raise IOError("Timeout processing auth request")

    
    
    
