#!/bin/bash

HUBU=jasonrandrews
IMG=pico-dev

# combine the manifests
docker manifest create $HUBU/$IMG:latest \
--amend $HUBU/$IMG:latest-aarch64 \
--amend $HUBU/$IMG:latest-x86_64
docker manifest push --purge $HUBU/$IMG:latest

docker manifest create $HUBU/$IMG:vscode \
--amend $HUBU/$IMG:vscode-aarch64 \
--amend $HUBU/$IMG:vscode-x86_64
docker manifest push --purge $HUBU/$IMG:vscode
