import socket
import sys
import time

good_request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n"
bad_request = "Hello there / HTTP/1.1\r\nHost: localhost\r\n"

def netcat(hostname, port, content=None, keep_alive=False, protocol='tcp'):
    print('')
    if protocol == 'tcp':
        s = socket.socket()
    elif protocol == 'udp':
        s = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    else:
        print("Error: Protocol must be 'tcp' or 'udp'")
        return

    try:
        s.connect((hostname, port))
        print(f'Connection Success to {hostname}:{port}/{protocol}')
    except Exception as e:
        print(f'Connection failed: {e}')
        return

    if content:
        num_requests = 2 if keep_alive else 1
        for i in range(num_requests):
            if i == 0:
                request = content
            else:
                request = good_request

            print(f'\n[Request #{i + 1}] Sending:')
            print(request)
            s.sendall(request.encode())

            has_received = False
            s.settimeout(100000)

            while True:
                try:
                    data = s.recv(1024)
                except socket.timeout:
                    if has_received:
                        print('[Info] Timeout: no more data, breaking.')
                    else:
                        print('[Error] Timeout: no data received.')
                    break
                if not data:
                    break
                print('Received:', repr(data))
                has_received = True

            if keep_alive and i == 0:
                print('[Keep-Alive] Waiting 1 second before next request...')
                time.sleep(1)

    if keep_alive:
        print('[Keep-Alive] Final wait for 10 seconds before closing...')
        time.sleep(10)

    try:
        s.shutdown(socket.SHUT_WR)
    except:
        pass
    s.close()
    print('[Connection Closed]')

if __name__ == "__main__":
    args = sys.argv[1:]
    keep_alive = "-kalive" in args
    if keep_alive:
        args.remove("-kalive")

    if "-ok" in args:
        http_request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n"
    elif "-bad" in args:
        http_request = "Hello there / HTTP/1.1\r\nHost: localhost\r\n\r\n"
    elif "-ko" in args:
        http_request = "Hello there\n"
    elif "-post" in args:
        http_request = "POST / HTTP/1.1\r\nHost: localhost\r\nContent-Length: 5\r\n\r\nHello"
    elif "-large" in args:
        http_request = "POST / HTTP/1.1\r\nHost: localhost\r\nContent-Length: 1940\r\n\r\n" + "0" * 1930 + "1" * 10
    else:
        http_request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n"

    netcat('localhost', 8080, http_request, keep_alive)
