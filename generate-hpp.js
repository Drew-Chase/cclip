const fs = require('fs');
const path = require('path');

const outputFile = path.join(__dirname, 'cclip.hpp');
const includesDirectory = path.join(__dirname, 'includes');
const sourceDirectory = path.join(__dirname, 'src');

const includes = fs.readdirSync(includesDirectory).filter(file => file.endsWith('.h'))
const sources = fs.readdirSync(sourceDirectory).filter(file => file.endsWith('.cpp'));

const legalHeader = `/**
    This file is part of the CClip project, a simple and convenient library for handling command line arguments in C++ applications. 
    The primary purpose of CClip is to make the parsing of command-line options easier, providing a structured and consistent way to manage command-line inputs. 
    It enables developers to define specific command-line options and arguments that their applications can accept. Once these options are defined, CClip allows them to be easily parsed and retrieved when the application is run, reducing the complexity associated with command-line input handling. 
    The parsing functionality provided by CClip is intuitive and efficient, making it an ideal choice for any C++ application that requires command-line input functionality.
    For more information please visit our github page at https://github.com/Drew-Chase/cclip
*/`

const version= '0.0.8';

let content = '';
// Include the content of all header files
for (const include of includes) {
    const includeFileContent = fs.readFileSync(path.join(includesDirectory, include), 'utf8');
    content += removeLocalIncludes(includeFileContent);
}

// Include the content of all source files
for (const source of sources) {
    let sourceFileContent = fs.readFileSync(path.join(sourceDirectory, source), 'utf8');
    content += removeLocalIncludes(sourceFileContent);
}

function removeLocalIncludes(content) {
    const includesFound = content.match(/#include\s*".*"/g);

    if (includesFound) {
        for (const include of includesFound) {
            const includeFile = include.replace('#include "', '').replace('"', '');
            if (includes.includes(includeFile)) {
                content = content.replace(include, '');
            }
        }
    }

    return content;
}

content = content.replace(/#pragma once/g, '');
content = `${legalHeader}\n\n#pragma once\n#define CCLIP_VERSION "${version}"\n${content}`

fs.writeFileSync(outputFile, content);