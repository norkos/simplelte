import pytest
import zmq
import lte_pb2
import rrc_pb2
import s1ap_pb2
from fixtures import create_eNB, create_mme
from ue_functions import create_ue, attach_ue, dl_througput, detach_ue
from time import sleep
from subprocess import Popen
import sys
#http://stackoverflow.com/questions/880557/socket-accept-too-many-open-files

def test_multi_ues(create_mme):
    #proc = Popen(["./build/CP_eNB/src/hwserver"])
    mme = create_mme
    data = 'x' * 100
    ues = []
    try:
        ue, ue_port, ue_id = create_ue(5556)
        attach_ue(ue, mme, ue_id, ue_port)
        dl_througput(ue, mme, ue_id, data)
        detach_ue(ue, mme, ue_id)
        
        ue.close()
    finally:
        shutdown_ind = lte_pb2.ASN1()
        shutdown_ind.s1ap.shutdown_ind.id = 1
        mme.send(shutdown_ind.SerializeToString())