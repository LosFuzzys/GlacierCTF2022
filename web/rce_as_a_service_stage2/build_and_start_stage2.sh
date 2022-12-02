#!/usr/bin/env bash

# Build the image.
podman build -t rceaas-stage2-image -f ./Dockerfile .
# Run the container in an interactive session and map
# the container port 8080 to the host port 8002.
podman run -it -p 8002:8080 --rm rceaas-stage2-image
