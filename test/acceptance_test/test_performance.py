import pytest
import zmq
import lte_pb2
import rrc_pb2
import s1ap_pb2
from fixtures import create_eNB, create_mme
from ue_functions import create_ue, attach_ue, dl_througput, detach_ue
from time import sleep
import sys
#http://stackoverflow.com/questions/880557/socket-accept-too-many-open-files
def test_dl_throughput(create_eNB, create_mme):  
    mme = create_mme
    ues = []
    try:
        print "Creating UEs"
        for i  in xrange(0, 100):
            ue, ue_port, ue_id = create_ue(5556 + i)
            ues.append([ue, ue_port, ue_id])
        
        print "Attaching UEs"
        for ue, ue_port, ue_id in ues:
            attach_ue(ue, mme, ue_id, ue_port)
        
        data = "x" * 100
        
        for i in xrange(0, 100):
            for ue, ue_port, ue_id in ues:
                dl_througput(ue, mme, ue_id, data)
        
    finally:
        for ue, ue_port, ue_id in ues:
            detach_ue(ue, mme, ue_id)
            ue.close()
