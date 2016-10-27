from subprocess import Popen
import pytest
import zmq
import lte_pb2
import rrc_pb2
import s1ap_pb2

mme_port = 5555;

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

def create_ue(port):
    context = zmq.Context()
    ue = context.socket(zmq.DEALER)
    ue.bind("tcp://*:%s" % port)
    ue.RCVTIMEO = 1000
    
    return ue, port, port

def test_dl_throughput_2_ues(create_eNB, create_mme):  
    try:
        mme = create_mme
        ue, ue_port, ue_id = create_ue(5556)    
        ue2, ue_port2, ue_id2 = create_ue(5557)
        
        data = "dummy"
        attach_ue(ue, mme, ue_id, ue_port)
        attach_ue(ue2, mme, ue_id2, ue_port2)
        
        nas_from_mme = lte_pb2.ASN1()
        nas_from_mme.nas.downlink_thr.id = ue_id
        nas_from_mme.nas.downlink_thr.data = data
        mme.send(nas_from_mme.SerializeToString())
        
        to_ue = ue.recv()
        nas_to_ue = lte_pb2.ASN1()
        nas_to_ue.ParseFromString(to_ue)
        
        assert data == nas_to_ue.nas.downlink_thr.data

    finally:
        ue.close()
        ue2.close()

def test_dl_throughput(create_eNB, create_mme):  
    try:
        mme = create_mme
        ue, ue_port, ue_id = create_ue(5556)
        
        data = "dummy"
        attach_ue(ue, mme, ue_id, ue_port)
        
        nas_from_mme = lte_pb2.ASN1()
        nas_from_mme.nas.downlink_thr.id = ue_id
        nas_from_mme.nas.downlink_thr.data = data
        mme.send(nas_from_mme.SerializeToString())
        
        to_ue = ue.recv()
        nas_to_ue = lte_pb2.ASN1()
        nas_to_ue.ParseFromString(to_ue)
        
        assert data == nas_to_ue.nas.downlink_thr.data
        
    finally:
        ue.close()
    
def attach_ue(ue, mme, id, ue_port):    
    mme_req = lte_pb2.ASN1()
    mme_req.s1ap.attach_req.id = id 
    mme_req.s1ap.attach_req.port = ue_port
    mme.send(mme_req.SerializeToString())
    
    message = ue.recv()
    ue_req_ = lte_pb2.ASN1()
    ue_req_.ParseFromString(message)
     
    ue_resp = lte_pb2.ASN1()
    ue_resp.rrc.attach_resp.id = id
    ue_resp.rrc.attach_resp.status = rrc_pb2.AttachResp.OK
    ue.send(ue_resp.SerializeToString())
    
    message = mme.recv()
    mme_resp_ = lte_pb2.ASN1()
    mme_resp_.ParseFromString(message)
    mme_resp = mme_resp_.s1ap.attach_resp
