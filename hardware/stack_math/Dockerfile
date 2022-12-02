FROM python:3.9.13

EXPOSE 1337

RUN export DEBIAN_FRONTEND=noninteractive && \
    apt-get -y update && \
    apt-get -y install socat coreutils verilator

RUN pip install pycryptodome sympy

RUN echo "glacierctf{Stup1d_s3xy_St4ckm4ch1n3s}" > /flag.txt

COPY chall/Stackmachine.v /
COPY chall/runner.cpp /
COPY chall/runner.py /
COPY chall/solver.py /

RUN verilator -cc Stackmachine.v runner.cpp --build --exe

RUN cp /obj_dir/VStackmachine /
RUN rm -rf /obj_dir /runner.cpp

RUN chmod 555 /runner.py && \
    chmod 555 /VStackmachine


CMD socat -T 30 \
    TCP-LISTEN:1337,nodelay,reuseaddr,fork \
    EXEC:"stdbuf -i0 -o0 -e0 python /runner.py"
