import os

from oeqa.runtime.case import OERuntimeTestCase
from oeqa.core.decorator.depends import OETestDepends
from oeqa.runtime.decorator.package import OEHasPackage

class JavacTest(OERuntimeTestCase):

    @classmethod
    def setUpClass(cls):
        myfilesdir = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../../files/')
        src = os.path.join(myfilesdir, 'test.java')
        dst = '/tmp/test.java'
        cls.tc.target.copyTo(src, dst)

    @classmethod
    def tearDownClass(cls):
        dst = '/tmp/test.java /tmp/test.class'
        cls.tc.target.run('rm %s' % dst)

    @OETestDepends(['java.JavaTest.test_java_exists'])
    def test_javac_exists(self):
        status, output = self.target.run('which javac')
        msg = 'javac binary not in PATH or not on target.'
        self.assertEqual(status, 0, msg=msg)

    @OETestDepends(['javac.JavacTest.test_javac_exists'])
    def test_javac_works(self):
        status, output = self.target.run('javac /tmp/test.java')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)
