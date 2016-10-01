'use strict';

var zstd = require('../');
var expect = require('chai').expect;
var fs = require('fs');
var path = require('path');

function testBufferAsync(method, bufferFile, resultFile, done, params) {
  params = params || {};
  var buffer = fs.readFileSync(path.join(__dirname, '/fixtures/', bufferFile));
  var result = fs.readFileSync(path.join(__dirname, '/fixtures/', resultFile));

  if (method.name === 'compress') {
    method(buffer, params, function(err, output) {
      expect(output).to.deep.equal(result);
      done();
    });
  }

  if (method.name === 'decompress') {
    method(buffer, function(err, output) {
      expect(output).to.deep.equal(result);
      done();
    });
  }
}

describe('ZSTD Buffer Async', function() {
  describe('compress', function() {
    it('should compress binary data', function(done) {
      testBufferAsync(zstd.compress, 'data10k.bin', 'data10k.bin.zst', done);
    });

    it('should compress text data', function(done) {
      testBufferAsync(zstd.compress, 'data.txt', 'data.txt.zst', done);
    });

    it('should compress text data with level=3', function(done) {
      testBufferAsync(zstd.compress, 'data.txt', 'data.txt.zst.03', done, {level: 3});
    });

    it('should compress text data with level=9', function(done) {
      testBufferAsync(zstd.compress, 'data.txt', 'data.txt.zst.09', done, {level: 9});
    });

    it('should compress text data with dict=(new Buffer("hello zstd"))', function(done) {
      testBufferAsync(zstd.compress, 'data.txt', 'data.txt.zst.09.dict', done, {level: 9, dict: new Buffer("hello zstd")});
    });

    it('should compress an empty buffer', function(done) {
      testBufferAsync(zstd.compress, 'empty', 'empty.zst', done);
    });

    it('should compress a large buffer', function(done) {
      this.timeout(30000);
      testBufferAsync(zstd.compress, 'large.txt', 'large.txt.zst', done);
    });
  });

  describe('decompress', function() {
    it('should decompress binary data', function(done) {
      testBufferAsync(zstd.decompress, 'data10k.bin.zst', 'data10k.bin', done);
    });

    it('should decompress text data', function(done) {
      testBufferAsync(zstd.decompress, 'data.txt.zst', 'data.txt', done);
    });

    it('should decompress text data with dict=(new Buffer("hello zstd"))', function() {
      testBufferAsync(zstd.decompress, 'data.txt.zst.09.dict', 'data.txt', {level: 9, dict: new Buffer("hello zstd")});
    });

    it('should decompress to an empty buffer', function(done) {
      testBufferAsync(zstd.decompress, 'empty.zst', 'empty', done);
    });

    it('should decompress to a large buffer', function(done) {
      testBufferAsync(zstd.decompress, 'large.zst', 'large', done);
    });

    it('should decompress to another large buffer', function(done) {
      testBufferAsync(zstd.decompress, 'large.txt.zst', 'large.txt', done);
    });
  });
});
