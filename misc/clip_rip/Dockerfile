FROM alpine:latest
EXPOSE 1337

RUN apk update
RUN apk add bash build-base procps-dev gettext meson ninja gpg gpg-agent \
    gpgme-dev pinentry git msgpack-cxx-dev pass socat

RUN adduser -s /bin/bash -D chad -u 1337

RUN git clone https://github.com/Neargye/magic_enum.git $HOME/magic_enum
RUN cp $HOME/magic_enum/include/magic_enum.hpp /usr/include/magic_enum.hpp
RUN rm -r $HOME/magic_enum

USER chad
WORKDIR /home/chad
RUN mkdir /home/chad/chall

COPY assets/gpg_keygen_batch /home/chad/
RUN gpg --batch --generate-key $HOME/gpg_keygen_batch
RUN rm $HOME/gpg_keygen_batch

RUN pass init chad@foo.bar

RUN export flag="glacierctf{s1mps0n_1ntr0s_st1ll_h1t_h4rd}" && \
    echo -e "$flag\n$flag" | pass insert glacierctf/flag1
RUN export flag="glacierctf{4ll_th3_th1dr_p4rtys_f4ult_cry}" && \
    echo -e "$flag\n$flag" | pass insert glacierctf/flag2

COPY --chown=chad:chad wlclipmgr/ /home/chad/chall/wlclipmgr
WORKDIR /home/chad/chall/wlclipmgr
RUN meson setup build
RUN meson compile -C build
WORKDIR /home/chad

USER root
RUN apk del build-base meson ninja
RUN ln -s /home/chad/chall/wlclipmgr/build/wlclipmgr /usr/bin/wlclipmgr
USER chad

COPY assets/bart_chalkboard_gags.txt /home/chad/chall/
COPY scripts/create_chall_clipboard.sh /home/chad/chall/
RUN /home/chad/chall/create_chall_clipboard.sh

COPY scripts/connect.sh /home/chad/chall/
CMD socat -T 200 TCP-LISTEN:1337,nodelay,reuseaddr,fork \
    EXEC:"chall/connect.sh"
