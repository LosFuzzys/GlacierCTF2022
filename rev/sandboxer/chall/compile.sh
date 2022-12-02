#!/bin/bash
gcc sandbox.c base64.c -o sandbox -mavx -maes -s
