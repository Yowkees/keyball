#!/bin/bashS

docker build -t qmk-image:test-tag .
docker run -w /qmk_firmware -v ./.build:/qmk_firmware/.build -v $(pwd)/qmk_firmware/keyboards:/qmk_firmware/keyboards  --rm -it qmk-image:test-tag qmk compile -kb keyball/keyball61 -km default
