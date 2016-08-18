var addon =  require('bindings')('node_zstd.node');

module.exports.compress = addon.Compress;
module.exports.decompress = addon.Decompress;
module.exports.compressUsingCDict = addon.CompressUsingCDict;
module.exports.decompressUsingDDict = addon.DecompressDDict;
