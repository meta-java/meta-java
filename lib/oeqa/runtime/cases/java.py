import os

from oeqa.runtime.case import OERuntimeTestCase
from oeqa.core.decorator.depends import OETestDepends
from oeqa.core.decorator.oeid import OETestID
from oeqa.runtime.decorator.package import OEHasPackage

class JavaTest(OERuntimeTestCase):

    @classmethod
    def setUpClass(cls):
        myfilesdir = os.path.join(os.path.dirname(os.path.realpath(__file__)), '../../files/')
        src = os.path.join(myfilesdir, 'test.jar')
        dst = '/tmp/test.jar'
        cls.tc.target.copyTo(src, dst)

    @classmethod
    def tearDownClass(cls):
        dst = '/tmp/test.jar'
        cls.tc.target.run('rm %s' % dst)

    @OETestDepends(['ssh.SSHTest.test_ssh'])
    def test_java_exists(self):
        status, output = self.target.run('which java')
        msg = 'java binary not in PATH or not on target.'
        self.assertEqual(status, 0, msg=msg)

    @OETestDepends(['java.JavaTest.test_java_exists'])
    def test_java_version(self):
        status, output = self.target.run('java -version')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)
        # check java version (somehow...)

    @OETestDepends(['java.JavaTest.test_java_exists'])
    def test_java_jar_works(self):
        status, output = self.target.run('java -jar /tmp/test.jar')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)

        msg = 'Incorrect output: %s' % output
        self.assertEqual(output, "the answer is 42", msg=msg)

    @OETestDepends(['java.JavaTest.test_java_exists'])
    def test_java_jar_int_mode(self):
        status, output = self.target.run('java -showversion -Xint -jar /tmp/test.jar')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)

        msg = 'Incorrect mode: %s' % output
        self.assertIn(', interpreted mode)', output, msg=msg)

    @OETestDepends(['java.JavaTest.test_java_exists'])
    def test_java_jar_comp_mode(self):
        status, output = self.target.run('java -showversion -Xcomp -jar /tmp/test.jar')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)

        msg = 'Incorrect mode: %s' % output
        self.assertIn(', compiled mode)', output, msg=msg)
