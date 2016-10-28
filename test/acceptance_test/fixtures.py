import pytest
import zmq
from subprocess import Popen

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
    port = 5555
    mme.connect("tcp://localhost:%s" % port)
    mme.RCVTIMEO = 1000
    
    def tear_down():
        mme.close()
    
    request.addfinalizer(tear_down)
    
    return mme