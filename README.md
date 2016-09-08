node-zstd
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

var compressed = zstd.compress(data, 18);  // 18 is compressionLevel, default 1 if none.

var decompressed = zstd.decompress(compressed);

console.log(decompressed.toString());  // should be 'hello zstd'
```

### with dict

#### Simple dictionary API

```js
var zstd = require('node-zstd');

var data = new Buffer('hello zstd');

var dict = new Buffer('Nice to meet you!');

var compressed = zstd.compressUsingDict(data, dict, 18);  // 18 is compressionLevel, default 1 if none.

var decompressed = zstd.decompressUsingDict(compressed, dict);

console.log(decompressed.toString());  // should be 'hello zstd'
```
#### Fast dictionary API

```js
var zstd = require('node-zstd');

var data = new Buffer('hello zstd');

var dict = new Buffer('Nice to meet you!');

var compressed = zstd.compressUsingCDict(data, dict, 18);  // 18 is compressionLevel, default 1 if none.

var decompressed = zstd.decompressUsingCDict(compressed, dict);

console.log(decompressed.toString());  // should be 'hello zstd'
```
`
## Tests

```sh
$ npm test
```

## License
MIT
