var addon =  require('bindings')('node_zstd.node');

module.exports.compress = addon.Compress;
module.exports.decompress = addon.Decompress;
module.exports.compressUsingDict = addon.CompressUsingDict;
module.exports.decompressUsingDict = addon.DecompressUsingDict;
