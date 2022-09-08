const gracefulFilesystem = require("graceful-fs");
const relativeFiles = require("scan-dir-recursive/relative");
const path = require("path");
const mkdirp = require("mkdirp");

if (gracefulFilesystem.existsSync("./build/Release")) { 
    mkdirp.sync("./napi");
    relativeFiles("./build/Release", function(_) {
        for (const file of _) {
            gracefulFilesystem.copyFileSync(path.join("./build/Release", file), path.join("./napi", file));
        } 
    }, [ "obj" ]);
}