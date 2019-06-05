import os

from oeqa.runtime.case import OERuntimeTestCase
from oeqa.core.decorator.depends import OETestDepends
from oeqa.core.decorator.data import skipIfDataVar, skipIfInDataVar
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

    # As OpenJDK-7 doesn't support compiled mode (JIT) for all architectures yet
    # we skip these tests for now.
    @OEHasPackage(["openjdk-7-jre", "openjdk-7"])
    @OETestDepends(['java.JavaTest.test_java_exists'])
    @skipIfDataVar('ARCH', 'arm64', 'OpenJDK 7 compiled mode not yet supported for aarch64')
    @skipIfDataVar('ARCH', 'x86', 'OpenJDK 7 compiled mode not yet supported for x86')
    @skipIfDataVar('ARCH', 'x86-64', 'OpenJDK 7 compiled mode not yet supported for x86-64')
    @skipIfDataVar('ARCH', 'ppc', 'OpenJDK 7 compiled mode not yet supported for ppc')
    @skipIfDataVar('ARCH', 'powerpc', 'OpenJDK 7 compiled mode not yet supported for powerpc')
    def test_java7_jar_comp_mode(self):
        status, output = self.target.run('java -showversion -Xcomp -jar /tmp/test.jar')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)

        msg = 'Incorrect mode: %s' % output
        self.assertIn(', compiled mode)', output, msg=msg)

    # As OpenJDK-8 doesn't support compiled mode (JIT) for arm yet we skip this
    # test for now.
    @OEHasPackage(["openjre-8", "openjdk-8"])
    @OETestDepends(['java.JavaTest.test_java_exists'])
    @skipIfInDataVar('TUNE_FEATURES', 'armv4', 'OpenJDK 8 compiled mode not yet supported for armv4')
    @skipIfInDataVar('TUNE_FEATURES', 'armv5', 'OpenJDK 8 compiled mode not yet supported for armv5')
    @skipIfInDataVar('TUNE_FEATURES', 'armv6', 'OpenJDK 8 compiled mode not yet supported for armv6')
    def test_java8_jar_comp_mode(self):
        status, output = self.target.run('java -showversion -Xcomp -jar /tmp/test.jar')
        msg = 'Exit status was not 0. Output: %s' % output
        self.assertEqual(status, 0, msg=msg)

        msg = 'Incorrect mode: %s' % output
        self.assertIn(', compiled mode)', output, msg=msg)
