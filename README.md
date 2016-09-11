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

### sample use

```js
var zstd = require('node-zstd');

var data = new Buffer('hello zstd');

var compressed = zstd.compressSync(data, 18);  // 18 is compressionLevel, default 1 if none.

var decompressed = zstd.decompressSync(compressed);

console.log(decompressed.toString());  // should be 'hello zstd'
```

### with dict

#### Simple dictionary API

```js
var zstd = require('node-zstd');

var data = new Buffer('hello zstd');

var dict = new Buffer('Nice to meet you!');

var compressed = zstd.compressSyncUsingDict(data, dict, 18);  // 18 is compressionLevel, default 1 if none.

var decompressed = zstd.decompressSyncUsingDict(compressed, dict);

console.log(decompressed.toString());  // should be 'hello zstd'
```
#### Fast dictionary API

```js
var zstd = require('node-zstd');

var data = new Buffer('hello zstd');

var dict = new Buffer('Nice to meet you!');

var compressed = zstd.compressSyncUsingCDict(data, dict, 18);  // 18 is compressionLevel, default 1 if none.

var decompressed = zstd.decompressSyncUsingCDict(compressed, dict);

console.log(decompressed.toString());  // should be 'hello zstd'
```
`
## Tests

```sh
$ npm test
```

## License
MIT
