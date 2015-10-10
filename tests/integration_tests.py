import sys
import unittest
import subprocess
import random
import socket
import itertools
import time

_, exe = sys.argv


class TestCase(unittest.TestCase):

    def setUp(self):
        self.port = random.randint(1024, 65535)
        self.proc = subprocess.Popen([
            exe,
            '--port', str(self.port)])
        self.addCleanup(self.proc.terminate)
        for retry in itertools.count():
            if retry > 10:
                break

            try:
                socket.create_connection(('127.0.0.1', self.port), timeout=30)
                break
            except socket.error:
                time.sleep(0.25)

    def tearDown(self):
        pass

    def test_service_runs(self):
        # Here you usually want to check your service protocol.
        # Create a socket, send some request and expect a response.
        pass


if __name__ == '__main__':
    unittest.main(argv=[sys.argv[0]])
