#!/bin/bash

HUBU=jasonrandrews

arch=$(uname -m)

docker tag pico-dev:vscode-$(arch)  $HUBU/pico-dev:vscode-$(arch)
docker tag pico-dev:latest-$(arch)  $HUBU/pico-dev:latest-$(arch)
docker push $HUBU/pico-dev:base-$(arch)
docker push $HUBU/pico-dev:latest-$(arch)

if [ "$arch" == 'x86_64' ]; then
  docker tag pico-dev:gitpod $HUBU/pico-dev:gitpod
  docker push $HUBU/pico-dev:gitpod
fi
