import pytest
import zmq
import s1ap_pb2
import lte_pb2

from fixtures import create_eNB, create_mme
from ue_functions import create_ue, attach_ue

def test_attach(create_eNB, create_mme):  
    mme = create_mme
    try:
        ue, ue_port, ue_id = create_ue(5556)
        attach_ue(ue, mme, ue_id, ue_port)

    finally:
        ue.close