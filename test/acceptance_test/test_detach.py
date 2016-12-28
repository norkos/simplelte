import pytest
import zmq
from fixtures import create_eNB, create_mme
from ue_functions import create_ue, attach_ue, detach_ue

def test_deatch(create_eNB, create_mme):  
    mme = create_mme
    try:
        ue, ue_port, ue_id = create_ue(5556) 
        attach_ue(ue, mme, ue_id, ue_port)
        detach_ue(ue, mme, ue_id)
        
    finally:
        ue.close()