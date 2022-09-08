'use strict';

Object.defineProperty(exports, '__esModule', { value: true });

var Module = require('module');
var path = require('path');

function _interopDefaultLegacy (e) { return e && typeof e === 'object' && 'default' in e ? e : { 'default': e }; }

var Module__default = /*#__PURE__*/_interopDefaultLegacy(Module);
var path__default = /*#__PURE__*/_interopDefaultLegacy(path);

function createRequire() {
    return Module__default["default"].createRequire(path__default["default"].dirname((typeof document === 'undefined' ? new (require('u' + 'rl').URL)('file:' + __filename).href : (document.currentScript && document.currentScript.src || new URL('index.js', document.baseURI).href))));
}

const _require = createRequire();
const binding = _require("./napi/Binding.node");
const Binding = binding;

exports.Binding = Binding;
exports["default"] = binding;
