from subprocess import Popen
import pytest
import zmq
import lte_pb2
from ue_functions import attach_ue, detach_ue, uplink_ue

@pytest.fixture(scope='function')
def socket_for_single_message(request):
    proc = Popen('build/CP_eNB/src/hwserver')
    context = zmq.Context()
    socket = context.socket(zmq.DEALER)
    socket.connect("tcp://localhost:5555")
    
    def tear_down():
        socket.close()
        proc.kill()
    
    request.addfinalizer(tear_down)
    return socket
    
def test_uplink(socket_for_single_message):
    socket = socket_for_single_message
    
    id = 1
    resp = attach_ue(id, socket)
    uplink_ue(id, socket, "so what")
    uplink_ue(id, socket, "so what")
    uplink_ue(id, socket, "so what")

    