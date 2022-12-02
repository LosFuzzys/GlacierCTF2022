FROM python:3.10-slim

EXPOSE 1337

RUN export DEBIAN_FRONTEND=noninteractive && \
    apt-get -y update && \
    apt-get -y install socat coreutils

WORKDIR /usr/src/app

COPY challenge/. .

RUN python3 -m pip install -r requirements.txt

RUN echo "glacierctf{dummy_flag}" > flag.txt

CMD socat -T 30 \
    TCP-LISTEN:1337,nodelay,reuseaddr,fork \
    EXEC:"python store.py"
