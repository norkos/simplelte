import zmq

def create_ue(port):
    context = zmq.Context()
    ue = context.socket(zmq.DEALER)
    ue.bind("tcp://*:%s" % port)
    ue.RCVTIMEO = 1000
    
    return ue, port, port