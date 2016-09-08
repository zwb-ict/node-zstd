var zstd = require('./../'),
    assert = require('assert');

var buf = new Buffer('hello zstd');
var dbuf = zstd.decompress(zstd.compress(buf, 18));
assert(buf.toString() === dbuf.toString());

var dict = new Buffer('Nice to meet you!');
var ddbuf = zstd.decompressUsingDict(zstd.compressUsingDict(buf, dict, 18), dict);
assert(buf.toString() == ddbuf.toString());

var cddbuf = zstd.decompressUsingCDict(zstd.compressUsingCDict(buf, dict, 18), dict);
assert(buf.toString() == cddbuf.toString());
