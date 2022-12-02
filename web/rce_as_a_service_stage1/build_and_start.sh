#!/usr/bin/env bash

# Build the image.
podman build -t rceaas-stage1-image -f ./Dockerfile .
# Run the container in an interactive session and map
# the container port 8080 to the host port 8001.
podman run -it -p 8001:8080 --rm rceaas-stage1-image
