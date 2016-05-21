import pytest
import messages_pb2
import zmq

def test_attach_request():
    context = zmq.Context()

    #  Socket to talk to server
    socket = context.socket(zmq.PAIR)
    socket.connect("tcp://localhost:5555")

    attach_req = messages_pb2.AttachReq()
    attach_req.id = 10
    socket.send(attach_req.SerializeToString())

    message = socket.recv()
    attach_resp = messages_pb2.AttachResp()
    attach_resp.ParseFromString(message)
    
    assert attach_resp.id == attach_req.id
    socket.close()
