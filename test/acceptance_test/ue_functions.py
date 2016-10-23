import lte_pb2
import rrc_pb2

def attach_ue(ue_id, socket):
    req = lte_pb2.ASN1()
    req.rrc.attach_req.id = ue_id 
    socket.send(req.SerializeToString())

    message = socket.recv()
    resp = lte_pb2.ASN1()
    resp.ParseFromString(message)
    
    return resp.rrc.attach_resp

def detach_ue(ue_id, socket):
    req = lte_pb2.ASN1()
    req.rrc.detach_req.id = ue_id 
    socket.send(req.SerializeToString())

    message = socket.recv()
    resp = lte_pb2.ASN1()
    resp.ParseFromString(message)
    
    return resp.rrc.detach_resp

def uplink_ue(ue_id, socket, data):
    req = lte_pb2.ASN1()
    req.rrc.uplink.id = ue_id
    req.rrc.uplink.data = data
    socket.send(req.SerializeToString())