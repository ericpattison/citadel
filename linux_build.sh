#!/bin/bash

#compile
make -C projects/linux/build
#sync
rsync -av ./dist/ ../citadel-sample/citadel/
