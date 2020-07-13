from rdg import RDG

# Test 1
generator = RDG("test[123]")
assert next(generator) == b"test1"
assert next(generator) == b"test2"
assert next(generator) == b"test3"
try:
    next(generator)
    assert False
except StopIteration:
    pass

# Test2
generator = RDG("test[123][abc]")
assert next(generator) == b"test1a"
assert next(generator) == b"test1b"
assert next(generator) == b"test1c"
assert next(generator) == b"test2a"
assert next(generator) == b"test2b"
assert next(generator) == b"test2c"
assert next(generator) == b"test3a"
assert next(generator) == b"test3b"
assert next(generator) == b"test3c"

try:
    next(generator)
    assert False
except StopIteration:
    pass

generator = RDG("\x00(\x01|\x02)\x03")
assert next(generator) == b"\x00\x01\x03"
assert next(generator) == b"\x00\x02\x03"

try:
    next(generator)
    assert False
except StopIteration:
    pass

generator = RDG("\x01\x02\x03")
assert next(generator) == b"\x01\x02\x03"

try:
    next(generator)
    assert False
except StopIteration:
    pass
