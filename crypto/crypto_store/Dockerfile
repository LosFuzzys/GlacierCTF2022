FROM python:3.10-alpine

EXPOSE 1337

RUN apk update; \
    apk add socat build-base linux-headers

WORKDIR /usr/src/app

COPY files/challenge/. .

RUN python3 -m pip install -r requirements.txt; \
    echo "glacierctf{RsA_S1gnAtuRe_1ssu3}" > flag.txt;

CMD socat -T 60 \
    TCP-LISTEN:1337,nodelay,reuseaddr,fork \
    EXEC:"python store.py"
