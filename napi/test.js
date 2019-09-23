'use strict';
const Assert = require('assert');
const Addon = require('./build/Release/addon');

Assert(Addon.get_string_length('hello') === 5);
