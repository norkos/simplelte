import pytest
import zmq
import lte_pb2
import rrc_pb2
import s1ap_pb2
from fixtures import create_eNB, create_mme
from ue_functions import create_ue, attach_ue

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



