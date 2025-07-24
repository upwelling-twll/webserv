import socket

def netcat(hostname, port, content=None, protocol='tcp'):
    print('')
    if protocol == 'tcp':
        s = socket.socket() # (socket.AF_INET, socket.SOCK_STREAM)
    if protocol == 'udp':
        s = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    if protocol != 'tcp' and protocol != 'udp':
        print("Error: Protocol must be 'tcp' or 'udp'")
    try:
        s.connect((hostname, port))
        print('Connection Success to ' + hostname + ':' + str(port) + '/' + protocol)
    except:
        print('Connection failed to ' + hostname + ':' + str(port) + '/' + protocol)
        return None
    if content != None:
        print('Starting to send content: ' + str(content))
        s.send(str.encode(content))
        s.send(str.encode('\n'))

        # s.sendall(content)
        hasHacievedAnyData = False
        while True:
            s.settimeout(10)
            try:
                data = s.recv(1024)
            except Exception:
                if hasHacievedAnyData:
                    print('Info: Timeout while expecting to receve more data')
                else:
                    print('Error: Timeout while expecting to receve data')
                break
            if len(data) == 0:
                break
            print('Received:' + str(repr(data)))
            hasHacievedAnyData = True
        s.shutdown(socket.SHUT_WR)
        s.close()
        # print('Connection closed.')

#Examples of usage
netcat('localhost', 8080, 'Hello there\n')
# netcat('localhost', 3478)
# netcat('localhost', 3478, protocol='udp')
# netcat('localhost', 16384, 'Hello', 'udp')