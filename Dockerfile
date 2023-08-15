FROM ghcr.io/qmk/qmk_cli

WORKDIR qmk_firmware

ARG URL=https://github.com/qmk/qmk_firmware.git
ARG TAG=0.21.6
ARG CLONE_DIR=.
ARG IGNORE_DIR='!/tests/* !/keyboards/* !/users/*'

RUN git clone --depth 1 --filter=tree:0 --no-checkout -b ${TAG} ${URL} ${CLONE_DIR} \
  && git checkout ${TAG} \
  && git submodule update --init --recursive --recommend-shallow --depth 1

CMD /bin/bash
