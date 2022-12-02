FROM node:16
EXPOSE 1337

RUN export DEBIAN_FRONTEND=noninteractive && \
    apt-get -y update && \
    apt-get -y install socat coreutils

COPY chall/ /app
RUN echo 'glacierctf{JaVa$cR!pT_!S_a_Gr3At_Es0t3r!c_LaNgUaG3}' > /app/flag.txt

CMD socat -T 30 \
    TCP-LISTEN:1337,nodelay,reuseaddr,fork \
    EXEC:"node /app/app.js"
