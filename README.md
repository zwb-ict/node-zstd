node-zstd [![version](https://img.shields.io/npm/v/node-zstd.svg)](https://www.npmjs.com/package/node-zstd) [![ZSTD/v1.0.0](https://img.shields.io/badge/ZSTD-v1.0.0-green.svg)](https://github.com/facebook/zstd/releases/tag/v1.0.0)
=====

[![Build Status][1]][2]

[1]: https://travis-ci.org/zwb-ict/node-zstd.svg?branch=master
[2]: https://travis-ci.org/zwb-ict/node-zstd

Zstd wrapper for Nodejs

## Installation

```bash
$ npm install node-zstd --save
```

## Usage

### Async

#### compress(buffer[, zstdCompressParams], callback)

```javascript
const compress = require('node-zstd').compress;

compress(input, function(err, output)) {
  // ...
};
```
#### decompress(buffer[, zstdDecompressParams], callback)

```javascript
const decompress = require('node-zstd').decompress;

decompress(input, function(err, output) {
  // ...
});
```

### Sync

#### compressSync(buffer[, zstdCompressParams])

```javascript
const compressSync = require('node-zstd').compressSync;

try {
  var output = compressSync(input);
} catch(err) {
  // ...
}
```

#### decompressSync(buffer[, zstdCompressParams])

```javascript
const decompressSync = require('node-zstd').decompressSync;

try {
  var output = decompressSync(input);
} catch(err) {
  // ...
}
```

### Stream

#### compressStream([zstdCompressParams])

```javascript
const compressStream = require('node-zstd').compressStream;
const fs = require('fs');

fs.createReadStream('path/to/input')
  .pipe(compressStream())
  .pipe(fs.createWriteStream('path/to/output'));
```

#### decompressStream([zstdCompressParams])

```javascript
const decompressStream = require('node-zstd').decompressStream;
const fs = require('fs');

fs.createReadStream('path/to/input')
  .pipe(decompressStream())
  .pipe(fs.createWriteStream('path/to/output'));
```

### ZSTD Params

The `compress`, `compressSync` and `compressStream` methods may accept an optional `zstdCompressParams` object to define compress level and/or dict.

```javascript
const zstdCompressParams = {
  level: 5, // default 1
  dict: new Buffer('hello zstd'), // if dict null, left level only.
  dictSize: dict.length  // if dict null, left level only.
};
```

The `decompress`, `decompressSync` and `decompressStream` methods may accept an optional `zstdDecompressParams` object to define dict.

```javascript
const zdtdDecompressParams = {
  dict: new Buffer('hello zstd'),
  dictSize: dict.length
};
```

## Tests

```sh
$ npm test
```

## License
MIT
