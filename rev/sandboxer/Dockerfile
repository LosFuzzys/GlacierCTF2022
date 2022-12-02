FROM python:3.9.13

EXPOSE 1337

RUN export DEBIAN_FRONTEND=noninteractive && \
    apt-get -y update && \
    apt-get -y install socat coreutils

COPY chall/userlist.txt /
COPY chall/sandbox.c /
COPY chall/wrapper.py /
COPY chall/base64.c /
COPY chall/base64.h /

RUN gcc sandbox.c base64.c -o /sandbox -mavx -maes -s

RUN rm /sandbox.c /base64.c

RUN chmod 555 /wrapper.py && \
    chmod 555 /sandbox && \
    chmod 444 /userlist.txt

CMD socat -T 30 \
    TCP-LISTEN:1337,nodelay,reuseaddr,fork \
    EXEC:"stdbuf -i0 -o0 -e0 python /wrapper.py"
