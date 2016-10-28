import zmq
import lte_pb2
import rrc_pb2

def create_ue(port):
    context = zmq.Context()
    ue = context.socket(zmq.DEALER)
    ue.bind("tcp://*:%s" % port)
    ue.RCVTIMEO = 1000
    
    return ue, port, port

def attach_ue(ue, mme, ue_id, ue_port):    
    mme_req = lte_pb2.ASN1()
    mme_req.s1ap.attach_req.id = ue_id 
    mme_req.s1ap.attach_req.port = ue_port
    mme.send(mme_req.SerializeToString())
    
    message = ue.recv()
    ue_req_ = lte_pb2.ASN1()
    ue_req_.ParseFromString(message)
     
    ue_resp = lte_pb2.ASN1()
    ue_resp.rrc.attach_resp.id = ue_id
    ue_resp.rrc.attach_resp.status = rrc_pb2.AttachResp.OK
    ue.send(ue_resp.SerializeToString())
    
    message = mme.recv()
    mme_resp_ = lte_pb2.ASN1()
    mme_resp_.ParseFromString(message)
    mme_resp = mme_resp_.s1ap.attach_resp