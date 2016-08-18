var addon =  require('bindings')('node_zstd.node');

module.exports.compress = addon.compress;
module.exports.decompress = addon.decompress;
