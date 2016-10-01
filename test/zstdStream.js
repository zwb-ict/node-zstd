'use strict';

var zstd = require('../');
var expect = require('chai').expect;
var Writable = require('stream').Writable;
var util = require('util');
var fs = require('fs');
var path = require('path');

function BufferWriter() {
  Writable.call(this);
  this.data = new Buffer(0);
}
util.inherits(BufferWriter, Writable);

BufferWriter.prototype._write = function(chunk, encoding, next) {
  this.data = Buffer.concat([this.data, chunk], this.data.length + chunk.length);
  next();
};

function testStream(method, bufferFile, resultFile, done, params) {
  var writeStream = new BufferWriter();

  fs.createReadStream(path.join(__dirname, '/fixtures/', bufferFile))
    .pipe(method(params))
    .pipe(writeStream);

  writeStream.on('finish', function() {
    var result = fs.readFileSync(path.join(__dirname, '/fixtures/', resultFile));
    expect(writeStream.data).to.deep.equal(result);
    done();
  });
}

describe('ZSTD Stream', function() {
  describe('compress', function() {
    it('should compress binary data', function(done) {
      testStream(zstd.compressStream, 'data10k.bin', 'data10k.bin.zst', done);
    });

    it('should compress text data', function(done) {
      testStream(zstd.compressStream, 'data.txt', 'data.txt.zst', done);
    });

    it('should compress text data with level=3', function(done) {
      testStream(zstd.compressStream, 'data.txt', 'data.txt.zst.03', done, {level: 3});
    });

    it('should compress text data with level=9', function(done) {
      testStream(zstd.compressStream, 'data.txt', 'data.txt.zst.09', done, {level: 9});
    });

    it('should compress text data with dict=(new Buffer("hello zstd"))', function(done) {
      testStream(zstd.compressStream, 'data.txt', 'data.txt.zst.09.dict', done, {level: 9, dict: new Buffer("hello zstd")});
    });

    it('should compress an empty buffer', function(done) {
      testStream(zstd.compressStream, 'empty', 'empty.zst', done);
    });

    it('should compress a large buffer', function(done) {
      this.timeout(30000);
      testStream(zstd.compressStream, 'large.txt', 'large.txt.zst', done);
    });
  });

  describe('decompress', function() {
    it('should decompress binary data', function(done) {
      testStream(zstd.decompressStream, 'data10k.bin.zst', 'data10k.bin', done);
    });

    it('should decompress text data', function(done) {
      testStream(zstd.decompressStream, 'data.txt.zst', 'data.txt', done);
    });

    it('should decompress text data with dict=(new Buffer("hello zstd"))', function() {
      testStream(zstd.decompressStream, 'data.txt.zst.09.dict', 'data.txt', {level: 9, dict: new Buffer("hello zstd")});
    });

    it('should decompress to an empty buffer', function(done) {
      testStream(zstd.decompressStream, 'empty.zst', 'empty', done);
    });

    it('should decompress to a large buffer', function(done) {
      testStream(zstd.decompressStream, 'large.zst', 'large', done);
    });

    it('should decompress to another large buffer', function(done) {
      testStream(zstd.decompressStream, 'large.txt.zst', 'large.txt', done);
    });
  });
});
