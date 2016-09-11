var zstd = require('./../'),
    assert = require('assert');

var buf = new Buffer('hello zstd');
var dbuf = zstd.decompressSync(zstd.compressSync(buf, 18));
assert(buf.toString() === dbuf.toString());

var dict = new Buffer('Nice to meet you!');
var ddbuf = zstd.decompressSyncUsingDict(zstd.compressSyncUsingDict(buf, dict, 18), dict);
assert(buf.toString() == ddbuf.toString());

var cddbuf = zstd.decompressSyncUsingCDict(zstd.compressSyncUsingCDict(buf, dict, 18), dict);
assert(buf.toString() == cddbuf.toString());
