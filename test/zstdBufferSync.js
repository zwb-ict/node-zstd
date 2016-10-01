'use strict';

var zstd = require('../');
var expect = require('chai').expect;
var fs = require('fs');
var path = require('path');

function testBufferSync(method, bufferFile, resultFile, params) {
  params = params || {};
  var buffer = fs.readFileSync(path.join(__dirname, '/fixtures/', bufferFile));
  var result = fs.readFileSync(path.join(__dirname, '/fixtures/', resultFile));
  var output = method(buffer, params);
  expect(output).to.deep.equal(result);
}

describe('ZSTD Buffer Sync', function() {
  describe('compress', function() {
    it('should compress binary data', function() {
      testBufferSync(zstd.compressSync, 'data10k.bin', 'data10k.bin.zst');
    });

    it('should compress text data', function() {
      testBufferSync(zstd.compressSync, 'data.txt', 'data.txt.zst');
    });

    it('should compress text data with level=3', function() {
      testBufferSync(zstd.compressSync, 'data.txt', 'data.txt.zst.03', {level: 3});
    });

    it('should compress text data with level=9', function() {
      testBufferSync(zstd.compressSync, 'data.txt', 'data.txt.zst.09', {level: 9});
    });

    it('should compress text data with dict=(new Buffer("hello zstd"))', function() {
      testBufferSync(zstd.compressSync, 'data.txt', 'data.txt.zst.09.dict', {level: 9, dict: new Buffer("hello zstd")});
    });

    it('should compress an empty buffer', function() {
      testBufferSync(zstd.compressSync, 'empty', 'empty.zst');
    });

    it('should compress a large buffer', function() {
      this.timeout(30000);
      testBufferSync(zstd.compressSync, 'large.txt', 'large.txt.zst');
    });
  });

  describe('decompress', function() {
    it('should decompress binary data', function() {
      testBufferSync(zstd.decompressSync, 'data10k.bin.zst', 'data10k.bin');
    });

    it('should decompress text data', function() {
      testBufferSync(zstd.decompressSync, 'data.txt.zst', 'data.txt');
    });

    it('should decompress text data with dict=(new Buffer("hello zstd"))', function() {
      testBufferSync(zstd.decompressSync, 'data.txt.zst.09.dict', 'data.txt', {level: 9, dict: new Buffer("hello zstd")});
    });

    it('should decompress to an empty buffer', function() {
      testBufferSync(zstd.decompressSync, 'empty.zst', 'empty');
    });

    it('should decompress to a large buffer', function() {
      testBufferSync(zstd.decompressSync, 'large.zst', 'large');
    });

    it('should decompress to another large buffer', function() {
      testBufferSync(zstd.decompressSync, 'large.txt.zst', 'large.txt');
    });
  });
});
