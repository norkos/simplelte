from subprocess import Popen
import pytest
import zmq
import lte_pb2
import rrc_pb2
import s1ap_pb2
from ue_functions import attach_ue, detach_ue

mme_port = 5555;
ue_port  = 5556;

@pytest.fixture(scope='function')
def create_eNB(request):
    proc = Popen('build/CP_eNB/src/hwserver')
    
    def tear_down():
        proc.kill()
    
    request.addfinalizer(tear_down)

@pytest.fixture(scope='function')
def create_mme(request):
    context = zmq.Context()
    mme = context.socket(zmq.DEALER)
    port = getattr(request.module, "mme_port")
    mme.connect("tcp://localhost:%s" % port)
    mme.RCVTIMEO = 1000
    
    def tear_down():
        mme.close()
    
    request.addfinalizer(tear_down)
    
    return mme

@pytest.fixture(scope='function')
def create_ue(request):
    context = zmq.Context()
    ue = context.socket(zmq.DEALER)
    port = getattr(request.module, "ue_port")
    ue.bind("tcp://*:%s" % port)
    ue.RCVTIMEO = 1000
    
    def tear_down():
        ue.close()
    
    request.addfinalizer(tear_down)
    
    return ue

def test_attach_request(create_eNB, create_mme, create_ue):  
    mme = create_mme
    ue = create_ue
    
    id = 1
    
    mme_req = lte_pb2.ASN1()
    mme_req.s1ap.attach_req.id = id 
    mme_req.s1ap.attach_req.port = ue_port
    mme.send(mme_req.SerializeToString())
    
    message = ue.recv()
    ue_req_ = lte_pb2.ASN1()
    ue_req_.ParseFromString(message)
    assert id == ue_req_.rrc.attach_req.id
     
    ue_resp = lte_pb2.ASN1()
    ue_resp.rrc.attach_resp.id = id
    ue_resp.rrc.attach_resp.status = rrc_pb2.AttachResp.OK
    ue.send(ue_resp.SerializeToString())
    
    message = mme.recv()
    mme_resp_ = lte_pb2.ASN1()
    mme_resp_.ParseFromString(message)
    mme_resp = mme_resp_.s1ap.attach_resp
    
    assert id == mme_resp.id
    assert s1ap_pb2.AttachResp.OK == mme_resp.status

    
def test_attach_request_nok(create_eNB, create_mme, create_ue):  
    mme = create_mme
    ue = create_ue
    
    id = 1
    
    mme_req = lte_pb2.ASN1()
    mme_req.s1ap.attach_req.id = id 
    mme_req.s1ap.attach_req.port = ue_port
    mme.send(mme_req.SerializeToString())
    
    message = ue.recv()
    ue_req_ = lte_pb2.ASN1()
    ue_req_.ParseFromString(message)
    assert id == ue_req_.rrc.attach_req.id
     
    ue_resp = lte_pb2.ASN1()
    ue_resp.rrc.attach_resp.id = id
    ue_resp.rrc.attach_resp.status = rrc_pb2.AttachResp.NOK
    ue.send(ue_resp.SerializeToString())
    
    message = mme.recv()
    mme_resp_ = lte_pb2.ASN1()
    mme_resp_.ParseFromString(message)
    mme_resp = mme_resp_.s1ap.attach_resp
    
    assert id == mme_resp.id
    assert s1ap_pb2.AttachResp.NOK == mme_resp.status
    
