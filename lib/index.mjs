import Module from 'module';
import path from 'path';

function createRequire() {
    return Module.createRequire(path.dirname(import.meta.url));
}

const _require = createRequire();
const binding = _require("./napi/Binding.node");
const Binding = binding;

export { Binding, binding as default };
