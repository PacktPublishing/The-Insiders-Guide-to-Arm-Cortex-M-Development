#!/bin/bash

VS_CODE_VER=v1.69.1

arch=$(uname -m)

# For M1 Mac uname reports arm64 so set to aarch64 instead to match Linux
if [ "$arch" == 'arm64' ]; then
  arch=aarch64
fi

opts+=(--build-arg "CMSIS_5=5.9.0")

# Gitpod image is x86 only
if [ "$arch" == 'x86_64' ]; then
  docker build "${opts[@]}" -t pico-dev:gitpod  -f Dockerfile.gitpod .
fi

# Basic image with Pico SDK
docker build "${opts[@]}" -t pico-dev:latest-$(arch) --target base -f Dockerfile .

# Second image which adds VS Code to the first image
opts+=(--build-arg "VSCODE_DL_PATH=openvscode-server-${VS_CODE_VER}")

if [ "$arch" == 'aarch64' ]; then
    opts+=(--build-arg "VSCODE=openvscode-server-${VS_CODE_VER}-linux-arm64.tar.gz")
    opts+=(--build-arg "VSCODE_SERVER_PATH=openvscode-server-${VS_CODE_VER}-linux-arm64")
else
    opts+=(--build-arg "VSCODE=openvscode-server-${VS_CODE_VER}-linux-x64.tar.gz")
    opts+=(--build-arg "VSCODE_SERVER_PATH=openvscode-server-${VS_CODE_VER}-linux-x64")
fi

docker build "${opts[@]}" -t pico-dev:vscode-$(arch) --target vscode -f Dockerfile .

