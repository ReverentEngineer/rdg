import unittest
from rdg import RDG

class TestRDG(unittest.TestCase):

    def test_range(self):
        generator = RDG("test[1-378]done")
        self.assertEqual(next(generator), b"test1done")
        self.assertEqual(next(generator), b"test2done")
        self.assertEqual(next(generator), b"test3done")
        self.assertEqual(next(generator), b"test7done")
        self.assertEqual(next(generator), b"test8done")
        self.assertRaises(StopIteration, next, generator)

    def test_group_or(self):
        generator = RDG("test([123]|[abc])")
        self.assertEqual(next(generator), b"test1")
        self.assertEqual(next(generator), b"test2")
        self.assertEqual(next(generator), b"test3")
        self.assertEqual(next(generator), b"testa")
        self.assertEqual(next(generator), b"testb")
        self.assertEqual(next(generator), b"testc")
        self.assertRaises(StopIteration, next, generator)

    def test_bytes(self):
        generator = RDG("\x00(\x01|\x02)\x03")
        self.assertEqual(next(generator), b"\x00\x01\x03")
        self.assertEqual(next(generator), b"\x00\x02\x03")
        self.assertRaises(StopIteration, next, generator)
