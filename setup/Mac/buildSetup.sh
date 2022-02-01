#!/bin/bash

if [[ -z $1 ]]; then
    echo "usage: buildSetup [Version]"
    exit 1
fi

version="$1"
mkdir -p bin/mac/packages

echo "Creating VST3 package... "
pkgbuild --version "$version" --component "bin/Mac/curtis.vst3" --identifier "com.radical-process.curtisVst3"  --install-location "/Library/Audio/Plug-Ins/VST3" bin/Mac/packages/curtisVst3.pkg

echo "Creating AU package... "
pkgbuild --version "$version" --component "bin/Mac/curtis.component" --identifier "com.radical-process.curtisAU" --install-location "/Library/Audio/Plug-Ins/Components" bin/Mac/packages/curtisAU.pkg

echo "Creating curtis installer... "
productBuild --distribution "setup/Mac/distribution.plist" --version "$version" --package-path bin/Mac/packages --resources "setup/Mac/resources" bin/Mac/curtis_unsigned.pkg

echo "Sign installer"
productsign --sign "Developer ID Installer: Chikashi Miyama (Q4Z8RY5999)"  bin/Mac/curtis_unsigned.pkg bin/Mac/curtis.pkg

rm -rf bin/mac/packages
