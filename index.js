var addon =  require('bindings')('node_zstd.node');

module.exports.compressSync = addon.CompressSync;
module.exports.decompressSync = addon.DecompressSync;

module.exports.compressSyncUsingDict = addon.CompressSyncUsingDict;
module.exports.decompressSyncUsingDict = addon.DecompressSyncUsingDict;

module.exports.compressSyncUsingCDict = addon.CompressSyncUsingCDict;
module.exports.decompressSyncUsingCDict = addon.DecompressSyncUsingCDict;
