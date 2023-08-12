FROM ghcr.io/qmk/qmk_cli

WORKDIR qmk_firmware

ARG URL=https://github.com/qmk/qmk_firmware.git
ARG BRANCH=master
ARG CLONE_DIR=.
ARG IGNORE_DIR='!/tests/* !/keyboards/* !/users/*'

RUN git clone --depth 1 --filter=tree:0 --no-checkout -b ${BRANCH} ${URL} ${CLONE_DIR} \
  && git checkout ${BRANCH} \
  && git submodule update --init --recursive --recommend-shallow --depth 1

CMD /bin/bash
