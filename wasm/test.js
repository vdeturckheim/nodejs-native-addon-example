'use strict';
const Assert = require('assert');
const Addon = require('./a.out');

setTimeout(() => {
    Assert(Addon.get_string_length('hello') === 5);
}, 200); // Ugly hack to wait for the module to be init
