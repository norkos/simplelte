import pytest
import zmq
import lte_pb2
import rrc_pb2
import s1ap_pb2
from fixtures import create_eNB, create_mme
from ue_functions import create_ue, attach_ue

def test_attach_request(create_eNB, create_mme):  
    mme = create_mme
    try:
        ue, ue_port, ue_id = create_ue(5556)    
        
        mme_req = lte_pb2.ASN1()
        mme_req.s1ap.attach_req.id = ue_id 
        mme_req.s1ap.attach_req.port = ue_port
        mme.send(mme_req.SerializeToString())
        
        message = ue.recv()
        ue_req_ = lte_pb2.ASN1()
        ue_req_.ParseFromString(message)
        assert ue_id == ue_req_.rrc.attach_req.id
        
        ue_resp = lte_pb2.ASN1()
        ue_resp.rrc.attach_resp.id = ue_id
        ue_resp.rrc.attach_resp.status = rrc_pb2.AttachResp.OK
        ue.send(ue_resp.SerializeToString())
        
        message = mme.recv()
        mme_resp_ = lte_pb2.ASN1()
        mme_resp_.ParseFromString(message)
        mme_resp = mme_resp_.s1ap.attach_resp
        
        assert ue_id == mme_resp.id
        assert s1ap_pb2.AttachResp.OK == mme_resp.status

        shutdown_ind = lte_pb2.ASN1()
        shutdown_ind.s1ap.shutdown_ind.id = 1
        mme.send(shutdown_ind.SerializeToString())
        
    finally:
        ue.close()

    
def test_attach_request_nok(create_eNB, create_mme):  
    mme = create_mme
    try:
        ue, ue_port, ue_id = create_ue(5556)    
        
        mme_req = lte_pb2.ASN1()
        mme_req.s1ap.attach_req.id = ue_id 
        mme_req.s1ap.attach_req.port = ue_port
        mme.send(mme_req.SerializeToString())
        
        message = ue.recv()
        ue_req_ = lte_pb2.ASN1()
        ue_req_.ParseFromString(message)
        assert ue_id == ue_req_.rrc.attach_req.id
        
        ue_resp = lte_pb2.ASN1()
        ue_resp.rrc.attach_resp.id = ue_id
        ue_resp.rrc.attach_resp.status = rrc_pb2.AttachResp.NOK
        ue.send(ue_resp.SerializeToString())
        
        message = mme.recv()
        mme_resp_ = lte_pb2.ASN1()
        mme_resp_.ParseFromString(message)
        mme_resp = mme_resp_.s1ap.attach_resp
        
        assert ue_id == mme_resp.id
        assert s1ap_pb2.AttachResp.NOK == mme_resp.status
        
        shutdown_ind = lte_pb2.ASN1()
        shutdown_ind.s1ap.shutdown_ind.id = 1
        mme.send(shutdown_ind.SerializeToString())
        
    finally:
        ue.close()