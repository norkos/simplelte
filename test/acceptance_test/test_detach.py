import pytest
import zmq
import lte_pb2
import rrc_pb2
import s1ap_pb2
from fixtures import create_eNB, create_mme
from ue_functions import create_ue, attach_ue

def test_deatch(create_eNB, create_mme):
    mme = create_mme  
    try:
        ue, ue_port, ue_id = create_ue(5556)
        attach_ue(ue, mme, ue_id, ue_port)
        
        mme_req = lte_pb2.ASN1()
        mme_req.s1ap.detach_req.id = ue_id 
        mme.send(mme_req.SerializeToString())
        
        message = ue.recv()
        ue_req_ = lte_pb2.ASN1()
        ue_req_.ParseFromString(message)
        assert ue_id == ue_req_.rrc.detach_req.id
        
        ue_resp = lte_pb2.ASN1()
        ue_resp.rrc.detach_resp.id = ue_id
        ue_resp.rrc.detach_resp.status = rrc_pb2.DetachResp.OK
        ue.send(ue_resp.SerializeToString())
        
        message = mme.recv()
        mme_resp_ = lte_pb2.ASN1()
        mme_resp_.ParseFromString(message)
        mme_resp = mme_resp_.s1ap.detach_resp
        
        assert ue_id == mme_resp.id
        assert s1ap_pb2.DetachResp.OK == mme_resp.status
        
    finally:
        ue.close()
        
def test_deatch_nok(create_eNB, create_mme):
    mme = create_mme  
    try:
        ue, ue_port, ue_id = create_ue(5556)
        attach_ue(ue, mme, ue_id, ue_port)
        
        mme_req = lte_pb2.ASN1()
        mme_req.s1ap.detach_req.id = ue_id 
        mme.send(mme_req.SerializeToString())
        
        message = ue.recv()
        ue_req_ = lte_pb2.ASN1()
        ue_req_.ParseFromString(message)
        assert ue_id == ue_req_.rrc.detach_req.id
        
        ue_resp = lte_pb2.ASN1()
        ue_resp.rrc.detach_resp.id = ue_id
        ue_resp.rrc.detach_resp.status = rrc_pb2.DetachResp.NOK
        ue.send(ue_resp.SerializeToString())
        
        message = mme.recv()
        mme_resp_ = lte_pb2.ASN1()
        mme_resp_.ParseFromString(message)
        mme_resp = mme_resp_.s1ap.detach_resp
        
        assert ue_id == mme_resp.id
        assert s1ap_pb2.DetachResp.NOK == mme_resp.status
        
    finally:
        ue.close()