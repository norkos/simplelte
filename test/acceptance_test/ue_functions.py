import messages_pb2

def attach_ue(ue_id, socket):
    req = messages_pb2.MessageWrapper()
    req.attach_req.id = ue_id; 
    socket.send(req.SerializeToString())

    message = socket.recv()
    resp = messages_pb2.MessageWrapper()
    resp.ParseFromString(message)
    
    return resp.attach_resp

def detach_ue(ue_id, socket):
    req = messages_pb2.MessageWrapper()
    req.detach_req.id = ue_id; 
    socket.send(req.SerializeToString())

    message = socket.recv()
    resp = messages_pb2.MessageWrapper()
    resp.ParseFromString(message)
    
    return resp.detach_resp